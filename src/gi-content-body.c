/*
 * gi-content-body.c
 *
 * Copyright (C) 2017 Bart Kessels <bartkessels@bk-mail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <glib-object.h>
#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>
#include <libsoup/soup.h>
#include <string.h>

#include "gi-content-body.h"
#include "gi-element-formdata.h"

G_DEFINE_TYPE(GiContentBody, gi_content_body, GTK_TYPE_SCROLLED_WINDOW)
static void gi_content_body_class_init(GiContentBodyClass* class) {}

static GiContentBody* gi_content_body;

/**
 * gi_content_body_data_formdata_btn_remove_clicked
 * 
 * @caller: The GtkWidget which is calling this function
 * @user_data: Pointer to GiElementFormdata object
 *
 * Remove the given GiElementFormdata object from the UI and from
 * the formdata list
 *
 * Return value: void
 */
static void gi_content_body_data_formdata_btn_remove_clicked(GtkWidget* caller, gpointer user_data)
{
    GiContentBody* self = gi_content_body;
    GiElementFormdata* formdata = GI_ELEMENT_FORMDATA(user_data);

    self->list_formdata = g_slist_remove(self->list_formdata, formdata);
    gtk_widget_destroy(GTK_WIDGET(formdata));
}

/**
 * gi_content_body_btn_data_formdata_add_clicked
 *
 * @caller: The GtkWidget which is calling this function
 * @user_data: Pointer to self
 *
 * Add a new GiElementFormdata object to the UI and to the list
 *
 * Return value: void
 */
static void gi_content_body_btn_data_formdata_add_clicked(GtkWidget* caller, gpointer user_data)
{
    GiContentBody* self = GI_CONTENT_BODY(user_data);

    GiElementFormdata* formdata = gi_element_formdata_new();
    g_signal_connect(formdata->btn_remove, "clicked", G_CALLBACK(gi_content_body_data_formdata_btn_remove_clicked), formdata);
    self->list_formdata = g_slist_append(self->list_formdata, formdata);
    gtk_container_add(GTK_CONTAINER(self->grd_data_formdata), GTK_WIDGET(formdata));
}

/**
 * gi_content_body_cb_data_raw_syntax_changed
 *
 * @caller: The GtkWidget which is calling this function
 * @user_data: Pointer to self
 *
 * Change the syntax highlighting on the SourceView input
 * to the selected language
 *
 * Return value: void
 */
static void gi_content_body_cb_data_raw_syntax_changed(GtkWidget* caller, gpointer user_data)
{
    GiContentBody* self = GI_CONTENT_BODY(user_data);
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(self->sv_data_raw_input));

    // Get language
    const gchar* language = gtk_combo_box_get_active_id(GTK_COMBO_BOX(caller));
    GtkSourceLanguageManager* source_language_manager = gtk_source_language_manager_new();
    GtkSourceLanguage* source_language = gtk_source_language_manager_get_language(source_language_manager, language);

    // Change language on buffer
    gtk_source_buffer_set_language(GTK_SOURCE_BUFFER(buffer), source_language);
}

/**
 * gi_content_body_init
 *
 * @self: Pointer to self
 *
 * Build the UI from the .ui file in the resources
 *
 * Return value: void
 */
static void gi_content_body_init(GiContentBody* self)
{
    // Load elements from resource
    GtkBuilder* builder = gtk_builder_new_from_resource("/net/bartkessels/getit/content-body.ui");

    self->grd_main = GTK_WIDGET(gtk_builder_get_object(builder, "grd_main"));
    self->cb_method = GTK_WIDGET(gtk_builder_get_object(builder, "cb_method"));
    self->et_uri = GTK_WIDGET(gtk_builder_get_object(builder, "et_uri"));
    self->sw_data = GTK_WIDGET(gtk_builder_get_object(builder, "sw_data"));
    self->grd_data_formdata = GTK_WIDGET(gtk_builder_get_object(builder, "grd_data_formdata"));
    self->btn_data_formdata_add = GTK_WIDGET(gtk_builder_get_object(builder, "btn_data_formdata_add"));
    self->cb_data_raw_syntax = GTK_WIDGET(gtk_builder_get_object(builder, "cb_data_raw_syntax"));
    self->sv_data_raw_input = GTK_WIDGET(gtk_builder_get_object(builder, "sv_data_raw_input"));

    self->stack_data = GTK_STACK(gtk_builder_get_object(builder, "stack_data"));

    // Connect signals
    g_signal_connect(self->btn_data_formdata_add, "clicked", G_CALLBACK(gi_content_body_btn_data_formdata_add_clicked), self);
    g_signal_connect(self->cb_data_raw_syntax, "changed", G_CALLBACK(gi_content_body_cb_data_raw_syntax_changed), self);

    // Show widgets
    gtk_container_add(GTK_CONTAINER(self), self->grd_main);

    g_object_unref(builder);
}

/**
 * gi_content_body_add_formdata_items_to_request
 *
 * @data: Pointer to GiElementFormdata object
 * @user_data: Pointer to self
 *
 * Add a GiElementFormdata to a Soup request.
 *
 * Check wheter to add a string formdata item or
 * a file to the request
 *
 * Return value: void
 */
static void gi_content_body_add_formdata_items_to_request(gpointer data, gpointer user_data)
{
    GiElementFormdata* formdata = GI_ELEMENT_FORMDATA(data);
    SoupMultipart* multipart = (SoupMultipart*)user_data;

    // Check if formdata element is enabled
    if (!gi_element_formdata_get_enabled(formdata)) {
        return;
    }

    const gchar* data_type = gi_element_formdata_get_data_type(formdata);
    const gchar* key = gtk_entry_get_text(GTK_ENTRY(formdata->et_key));

    // Check what datatype formdata is
    if (g_str_equal(data_type, DATA_TYPE_STRING)) {
        const gchar* value = gtk_entry_get_text(GTK_ENTRY(formdata->et_value));

        // Add key value pair to request
        soup_multipart_append_form_string(multipart, key, value);
    } else if (g_str_equal(data_type, DATA_TYPE_FILE)) {
        // Get information from file chooser
        const gchar* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(formdata->fcbtn_file));

        // Get file
        GError* error;
        GMappedFile* file = g_mapped_file_new(filename, FALSE, &error);
        gsize filelength = g_mapped_file_get_length(file);
        const gchar* filecontents = g_mapped_file_get_contents(file);

        SoupBuffer* soup_buffer = soup_buffer_new(SOUP_MEMORY_STATIC, filecontents, filelength);

        // Add file to request
        soup_multipart_append_form_file(multipart, key, filename, NULL, soup_buffer);
    }
}

/**
 * gi_content_body_new
 *
 * Create new instance of GiContentBody
 *
 * Return value: GiContentBody
 */
GiContentBody* gi_content_body_new()
{
    GiContentBody* content_body = g_object_new(GI_TYPE_CONTENT_BODY, NULL);
    gi_content_body = content_body;

    return content_body;
}

/**
 * gi_content_body_add_to_request
 *
 * @self: Pointer to self
 * @message: Pointer to SoupMessage
 *
 * All all elements of self to the SoupMessage request
 *
 * Return value: void
 */
void gi_content_body_add_to_request(GiContentBody* self, SoupMessage* message)
{
    // Check wheter to add formdata or raw to the request
    const gchar* body_type = gtk_stack_get_visible_child_name(self->stack_data);

    if (g_str_equal(body_type, BODY_TYPE_FORMDATA)) {
        // Create new multipart
        self->multipart = soup_multipart_new(SOUP_FORM_MIME_TYPE_MULTIPART);

        // Loop over formdata elements
        g_slist_foreach(self->list_formdata, gi_content_body_add_formdata_items_to_request, self->multipart);

        // Add multipart to message
        soup_multipart_to_message(self->multipart, message->request_headers, message->request_body);
    } else if (g_str_equal(body_type, BODY_TYPE_RAW)) {
        // Get mimetype from selected syntax
        const gchar* language = gtk_combo_box_get_active_id(GTK_COMBO_BOX(self->cb_data_raw_syntax));
        gchar* prefix = "application/";

        if (g_str_equal(language, "plain")) {
            prefix = "text/";
        }

        const gchar* mime_type = g_strconcat(prefix, language, NULL);
        const gchar* data = gi_content_body_get_data_raw(self);

        // Add data to message
        soup_message_set_request(message, mime_type, SOUP_MEMORY_COPY, data, strlen(data));
    }
}

/**
 * gi_content_body_get_data_raw
 *
 * @self: Pointer to self
 *
 * Get the content of the raw SourceView
 *
 * Return value: void
 */
const gchar* gi_content_body_get_data_raw(GiContentBody* self)
{
    // Read input from sourceview
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(self->sv_data_raw_input));
    GtkTextIter iter_start;
    GtkTextIter iter_end;

    gtk_text_buffer_get_bounds(buffer, &iter_start, &iter_end);

    return gtk_text_buffer_get_text(buffer, &iter_start, &iter_end, FALSE);
}

/**
 * gi_content_body_set_data_raw
 *
 * @self: Pointer to self
 * @data: String to be put into SourceView
 *
 * Insert the given string into the raw SourceView
 *
 * Return value: void
 */
void gi_content_body_set_data_raw(GiContentBody* self, const gchar* data)
{
    if (data == NULL) {
        return;
    }

    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(self->sv_data_raw_input));
    gtk_text_buffer_set_text(buffer, data, strlen(data));
}

/**
 * gi_content_body_add_formdata_with_values
 *
 * @self: Pointer to self
 * @enabled: Wheter or not the GiElementFormdata object is enabled
 * @key: Key of the pair
 * @value: String value of the pair
 * @file: String of the file
 * @type: Type of the GiElementFormdata object
 *
 * Add a new GiElementFormdata element with the given elements
 * filled in
 *
 * Return value: void
 */
void gi_content_body_add_formdata_with_values(GiContentBody* self, const gboolean enabled, const gchar* key, const gchar* value, const gchar* file, const gint type)
{
    GiElementFormdata* formdata = gi_element_formdata_new();
    g_signal_connect(formdata->btn_remove, "clicked", G_CALLBACK(gi_content_body_data_formdata_btn_remove_clicked), formdata);

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(formdata->cbtn_enabled), enabled);
    gtk_entry_set_text(GTK_ENTRY(formdata->et_key), key);
    gtk_entry_set_text(GTK_ENTRY(formdata->et_value), value);
    gtk_combo_box_set_active(GTK_COMBO_BOX(formdata->cb_type), type);

    if (file != NULL) {
        gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(formdata->fcbtn_file), file);
    }

    self->list_formdata = g_slist_append(self->list_formdata, formdata);
    gtk_container_add(GTK_CONTAINER(self->grd_data_formdata), GTK_WIDGET(formdata));
}