/*
 * gi-application.c
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

#include <gdk/gdk.h>
#include <glib-object.h>
#include <gtk/gtk.h>
#include <json-glib/json-glib.h>

#include "gi-application.h"
#include "gi-content-body.h"
#include "gi-element-cookie.h"
#include "gi-element-formdata.h"
#include "gi-element-header.h"
#include "gi-window-main.h"

struct _GiApplication {
    GtkApplication parent;

    /*
        Member Variables
    */
    GiWindowMain* window_main;
    const gchar* filename;
};

G_DEFINE_TYPE(GiApplication, gi_application, GTK_TYPE_APPLICATION)

static void gi_application_save_request(GiApplication* self, const gchar* filename)
{
    // Get request data
    GSList* formdata_list = self->window_main->stack->content_body->list_formdata;
    GSList* cookies_list = self->window_main->stack->content_cookies->list_cookies;
    GSList* headers_list = self->window_main->stack->content_headers->list_headers;

    const gint method = gtk_combo_box_get_active(GTK_COMBO_BOX(self->window_main->stack->content_body->cb_method));
    const gchar* uri = gtk_entry_get_text(GTK_ENTRY(self->window_main->stack->content_body->et_uri));
    const gchar* data_type = gtk_stack_get_visible_child_name(self->window_main->stack->content_body->stack_data);
    const gint raw_language = gtk_combo_box_get_active(GTK_COMBO_BOX(self->window_main->stack->content_body->cb_data_raw_syntax));
    const gchar* raw_input = gi_content_body_get_data_raw(self->window_main->stack->content_body);

    // Body
    JsonArray* body_formdata_array = json_array_new();
    JsonObject* body_object = json_object_new();

    json_object_set_int_member(body_object, JSON_BODY_METHOD_KEY, method);
    json_object_set_string_member(body_object, JSON_BODY_URI_KEY, uri);
    json_object_set_string_member(body_object, JSON_BODY_DATA_TYPE_KEY, data_type);
    json_object_set_int_member(body_object, JSON_BODY_RAW_LANGUAGE_KEY, raw_language);
    json_object_set_string_member(body_object, JSON_BODY_RAW_INPUT_KEY, raw_input);

    for (gint formdata_list_index = 0; formdata_list_index < g_slist_length(formdata_list); formdata_list_index++) {
        GiElementFormdata* formdata = GI_ELEMENT_FORMDATA(g_slist_nth_data(formdata_list, formdata_list_index));

        const gboolean enabled = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(formdata->cbtn_enabled));
        const gchar* key = gtk_entry_get_text(GTK_ENTRY(formdata->et_key));
        const gchar* value = gtk_entry_get_text(GTK_ENTRY(formdata->et_value));
        const gchar* file = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(formdata->fcbtn_file));
        const gint type = gtk_combo_box_get_active(GTK_COMBO_BOX(formdata->cb_type));

        JsonObject* formdata_object = json_object_new();

        json_object_set_boolean_member(formdata_object, JSON_FORMDATA_ENABLED_KEY, enabled);
        json_object_set_string_member(formdata_object, JSON_FORMDATA_KEY_KEY, key);
        json_object_set_string_member(formdata_object, JSON_FORMDATA_VALUE_KEY, value);
        json_object_set_string_member(formdata_object, JSON_FORMDATA_FILE_KEY, file);
        json_object_set_int_member(formdata_object, JSON_FORMDATA_TYPE_KEY, type);

        json_array_add_object_element(body_formdata_array, formdata_object);
    }

    json_object_set_array_member(body_object, JSON_FORMDATA_NAME, body_formdata_array);

    // Cookies
    JsonArray* cookies_array_cookies = json_array_new();

    for (gint cookies_list_index = 0; cookies_list_index < g_slist_length(cookies_list); cookies_list_index++) {
        GiElementCookie* cookie = GI_ELEMENT_COOKIE(g_slist_nth_data(cookies_list, cookies_list_index));

        const gboolean enabled = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(cookie->cbtn_enabled));
        const gchar* key = gtk_entry_get_text(GTK_ENTRY(cookie->et_key));
        const gchar* value = gtk_entry_get_text(GTK_ENTRY(cookie->et_value));

        JsonObject* cookie_object = json_object_new();

        json_object_set_boolean_member(cookie_object, JSON_COOKIE_ENABLED_KEY, enabled);
        json_object_set_string_member(cookie_object, JSON_COOKIE_KEY_KEY, key);
        json_object_set_string_member(cookie_object, JSON_COOKIE_VALUE_KEY, value);

        json_array_add_object_element(cookies_array_cookies, cookie_object);
    }

    // Headers
    JsonArray* headers_array_headers = json_array_new();

    for (gint headers_list_index = 0; headers_list_index < g_slist_length(headers_list); headers_list_index++) {
        GiElementHeader* header = GI_ELEMENT_HEADER(g_slist_nth_data(headers_list, headers_list_index));

        const gboolean enabled = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(header->cbtn_enabled));
        const gchar* key = gtk_entry_get_text(GTK_ENTRY(header->et_key));
        const gchar* value = gtk_entry_get_text(GTK_ENTRY(header->et_value));

        JsonObject* header_object = json_object_new();

        json_object_set_boolean_member(header_object, JSON_HEADER_ENABLED_KEY, enabled);
        json_object_set_string_member(header_object, JSON_HEADER_KEY_KEY, key);
        json_object_set_string_member(header_object, JSON_HEADER_VALUE_KEY, value);

        json_array_add_object_element(headers_array_headers, header_object);
    }

    // Put JsonBody's inside the root_object
    JsonObject* root_object = json_object_new();
    JsonNode* root_node = json_node_new(JSON_NODE_OBJECT);

    json_object_set_object_member(root_object, JSON_BODY_NAME, body_object);
    json_object_set_array_member(root_object, JSON_COOKIES_NAME, cookies_array_cookies);
    json_object_set_array_member(root_object, JSON_HEADERS_NAME, headers_array_headers);

    json_node_set_object(root_node, root_object);

    // Save the file
    GError** write_error;
    JsonGenerator* generator = json_generator_new();
    json_generator_set_root(generator, root_node);
    json_generator_set_pretty(generator, TRUE);
    json_generator_to_file(generator, filename, write_error);
}

static GtkFileFilter* gi_application_get_file_filter()
{
    GtkFileFilter* filter = gtk_file_filter_new();
    gtk_file_filter_add_mime_type(filter, "text/plain");
    gtk_file_filter_add_pattern(filter, "*.getit");
    gtk_file_filter_set_name(filter, "GetIt Request File");

    return filter;
}

static void gi_application_mi_save_as_activated(GtkWidget* caller, gpointer user_data)
{
    GiApplication* self = GI_APPLICATION(user_data);

    // Display save file dialog
    GtkWidget* file_chooser = gtk_file_chooser_dialog_new("Save request", GTK_WINDOW(self->window_main), GTK_FILE_CHOOSER_ACTION_SAVE, "Cancel", GTK_RESPONSE_CANCEL, "Save", GTK_RESPONSE_ACCEPT, NULL);
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(file_chooser), gi_application_get_file_filter());
    gint result = gtk_dialog_run(GTK_DIALOG(file_chooser));

    if (result != GTK_RESPONSE_ACCEPT) {
        gtk_widget_destroy(file_chooser);

        return;
    }

    self->filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser));
    gtk_widget_destroy(file_chooser);
    gi_element_header_bar_set_save_sensitive(self->window_main->header_bar, TRUE);

    // Check if extension is added
    if (!g_str_has_suffix(self->filename, FILE_EXTENSION)) {
        self->filename = g_strconcat(self->filename, FILE_EXTENSION, NULL);
    }

    gi_application_save_request(self, self->filename);

    const gchar* file_label = g_strconcat("File: ", self->filename, NULL);
    gtk_label_set_text(GTK_LABEL(self->window_main->lbl_file), file_label);
}

static void gi_application_mi_save_activated(GtkWidget* caller, gpointer user_data)
{
    GiApplication* self = GI_APPLICATION(user_data);

    if (self->filename == NULL) {
        gi_application_mi_save_as_activated(caller, user_data);

        return;
    }

    gi_application_save_request(self, self->filename);
}

static void gi_application_mi_open_activated(GtkWidget* caller, gpointer user_data)
{
    GiApplication* self = GI_APPLICATION(user_data);

    // Display open file dialog
    GtkWidget* file_chooser = gtk_file_chooser_dialog_new("Open Request", GTK_WINDOW(self->window_main), GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(file_chooser), gi_application_get_file_filter());
    gint result = gtk_dialog_run(GTK_DIALOG(file_chooser));

    if (result != GTK_RESPONSE_ACCEPT) {
        gtk_widget_destroy(file_chooser);

        return;
    }

    self->filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser));
    gtk_widget_destroy(file_chooser);
    gi_element_header_bar_set_save_sensitive(self->window_main->header_bar, TRUE);

    const gchar* file_label = g_strconcat("File: ", self->filename, NULL);
    gtk_label_set_text(GTK_LABEL(self->window_main->lbl_file), file_label);

    JsonParser* parser = json_parser_new();
    GError** error;
    json_parser_load_from_file(parser, self->filename, error);
    JsonNode* root_node = json_parser_get_root(parser);
    JsonObject* root_object = json_node_get_object(root_node);

    // Check if file has been succesfully loaded
    if (error != NULL) {
        GtkWidget* message_dialog = gtk_message_dialog_new(GTK_WINDOW(self->window_main), GTK_DIALOG_MODAL, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "Something went wrong opening the file", NULL);
        gtk_dialog_run(GTK_DIALOG(message_dialog));
        gtk_widget_destroy(message_dialog);

        return;
    }

    // Body
    JsonObject* body_object = json_object_get_object_member(root_object, JSON_BODY_NAME);
    JsonArray* body_array_formdata = json_object_get_array_member(body_object, JSON_FORMDATA_NAME);

    const gint method = json_object_get_int_member(body_object, JSON_BODY_METHOD_KEY);
    const gchar* uri = json_object_get_string_member(body_object, JSON_BODY_URI_KEY);
    const gchar* data_type = json_object_get_string_member(body_object, JSON_BODY_DATA_TYPE_KEY);
    const gint raw_language = json_object_get_int_member(body_object, JSON_BODY_RAW_LANGUAGE_KEY);
    const gchar* raw_input = json_object_get_string_member(body_object, JSON_BODY_RAW_INPUT_KEY);

    gtk_combo_box_set_active(GTK_COMBO_BOX(self->window_main->stack->content_body->cb_method), method);
    gtk_entry_set_text(GTK_ENTRY(self->window_main->stack->content_body->et_uri), uri);
    gtk_stack_set_visible_child_name(GTK_STACK(self->window_main->stack->content_body->stack_data), data_type);
    gi_content_body_set_data_raw(self->window_main->stack->content_body, raw_input);
    gtk_combo_box_set_active(GTK_COMBO_BOX(self->window_main->stack->content_body->cb_data_raw_syntax), raw_language);

    for (gint body_array_formdata_index = 0; body_array_formdata_index < json_array_get_length(body_array_formdata); body_array_formdata_index++) {
        JsonObject* formdata_object = json_array_get_object_element(body_array_formdata, body_array_formdata_index);

        const gboolean enabled = json_object_get_boolean_member(formdata_object, JSON_FORMDATA_ENABLED_KEY);
        const gchar* key = json_object_get_string_member(formdata_object, JSON_FORMDATA_KEY_KEY);
        const gchar* value = json_object_get_string_member(formdata_object, JSON_FORMDATA_VALUE_KEY);
        const gchar* file = json_object_get_string_member(formdata_object, JSON_FORMDATA_FILE_KEY);
        const gint type = json_object_get_int_member(formdata_object, JSON_FORMDATA_TYPE_KEY);

        gi_content_body_add_formdata_with_values(self->window_main->stack->content_body, enabled, key, value, file, type);
    }

    // Cookies
    JsonArray* cookies_array_cookies = json_object_get_array_member(root_object, JSON_COOKIES_NAME);

    for (gint cookies_array_cookies_index = 0; cookies_array_cookies_index < json_array_get_length(cookies_array_cookies); cookies_array_cookies_index++) {
        JsonObject* cookie_object = json_array_get_object_element(cookies_array_cookies, cookies_array_cookies_index);

        const gboolean enabled = json_object_get_boolean_member(cookie_object, JSON_COOKIE_ENABLED_KEY);
        const gchar* key = json_object_get_string_member(cookie_object, JSON_COOKIE_KEY_KEY);
        const gchar* value = json_object_get_string_member(cookie_object, JSON_COOKIE_VALUE_KEY);

        gi_content_cookies_add_cookie_with_values(self->window_main->stack->content_cookies, enabled, key, value);
    }

    // Headers
    JsonArray* headers_array_headers = json_object_get_array_member(root_object, JSON_HEADERS_NAME);

    for (gint headers_array_headers_index = 0; headers_array_headers_index < json_array_get_length(headers_array_headers); headers_array_headers_index++) {
        JsonObject* header_object = json_array_get_object_element(headers_array_headers, headers_array_headers_index);

        const gboolean enabled = json_object_get_boolean_member(header_object, JSON_HEADER_ENABLED_KEY);
        const gchar* key = json_object_get_string_member(header_object, JSON_HEADER_KEY_KEY);
        const gchar* value = json_object_get_string_member(header_object, JSON_HEADER_VALUE_KEY);

        gi_content_headers_add_header_with_values(self->window_main->stack->content_headers, enabled, key, value);
    }
}

static void gi_application_mi_clear_activated(GtkWidget* caller, gpointer user_data)
{
    GiApplication* self = GI_APPLICATION(user_data);

    // Body
    gtk_combo_box_set_active(GTK_COMBO_BOX(self->window_main->stack->content_body->cb_method), 0);
    gtk_entry_set_text(GTK_ENTRY(self->window_main->stack->content_body->et_uri), "");
    gtk_stack_set_visible_child_name(self->window_main->stack->content_body->stack_data, BODY_TYPE_FORMDATA);
    gtk_combo_box_set_active(GTK_COMBO_BOX(self->window_main->stack->content_body->cb_data_raw_syntax), 0);
    gi_content_body_set_data_raw(self->window_main->stack->content_body, "");

    while (g_slist_length(self->window_main->stack->content_body->list_formdata) > 0) {
        GiElementFormdata* formdata = GI_ELEMENT_FORMDATA(g_slist_nth_data(self->window_main->stack->content_body->list_formdata, 0));
        gtk_button_clicked(GTK_BUTTON(formdata->btn_remove));
    }

    // Cookies
    while (g_slist_length(self->window_main->stack->content_cookies->list_cookies) > 0) {
        GiElementCookie* cookie = GI_ELEMENT_COOKIE(g_slist_nth_data(self->window_main->stack->content_cookies->list_cookies, 0));
        gtk_button_clicked(GTK_BUTTON(cookie->btn_remove));
    }

    // Headers
    while (g_slist_length(self->window_main->stack->content_headers->list_headers) > 0) {
        GiElementHeader* header = GI_ELEMENT_HEADER(g_slist_nth_data(self->window_main->stack->content_headers->list_headers, 0));
        gtk_button_clicked(GTK_BUTTON(header->btn_remove));
    }

    // Response
    gi_content_response_show_default(self->window_main->stack->content_response);

    // Other
    gtk_stack_set_visible_child(GTK_STACK(self->window_main->stack), GTK_WIDGET(self->window_main->stack->content_body));
    gi_element_header_bar_set_subtitle(self->window_main->header_bar, NULL);
    gi_element_header_bar_set_save_sensitive(self->window_main->header_bar, FALSE);
    self->filename = NULL;
    gtk_label_set_text(GTK_LABEL(self->window_main->lbl_file), "File: (null)");
}

static gboolean gi_application_key_pressed(GtkWidget* caller, GdkEventKey* event, gpointer user_data)
{
    GiApplication* self = GI_APPLICATION(user_data);

    switch (event->keyval) {
    case GDK_KEY_s:
        if (event->state & GDK_MOD1_MASK && event->state & GDK_CONTROL_MASK) { // CTRL + ALT + S (save as menu item)
            gi_application_mi_save_as_activated(caller, user_data);
        } else if (event->state & GDK_CONTROL_MASK) { // CTRL + S (save menu item)
            gi_application_mi_save_activated(caller, user_data);
        }
        break;
    case GDK_KEY_o: // CTRL + O (open menu item)
        if (event->state & GDK_CONTROL_MASK) {
            gi_application_mi_open_activated(caller, user_data);
        }
        break;
    case GDK_KEY_Return:
        if (event->state & GDK_CONTROL_MASK) { // CTRL + Return (send the request)
            gtk_button_clicked(GTK_BUTTON(self->window_main->header_bar->btn_send));
        }
        break;
    case GDK_KEY_Escape: // ESC (cancel the request)
        gtk_button_clicked(GTK_BUTTON(self->window_main->header_bar->btn_cancel));
        break;
    }

    return FALSE;
}

static void gi_application_activate(GApplication* application)
{
    GiApplication* self = GI_APPLICATION(application);

    self->window_main = gi_window_main_new(self);
    gtk_window_present(GTK_WINDOW(self->window_main));

    // Connect signals
    g_signal_connect(self->window_main, "key_press_event", G_CALLBACK(gi_application_key_pressed), self);
    g_signal_connect(self->window_main->header_bar->mi_request_open, "activate", G_CALLBACK(gi_application_mi_open_activated), self);
    g_signal_connect(self->window_main->header_bar->mi_request_save_as, "activate", G_CALLBACK(gi_application_mi_save_as_activated), self);
    g_signal_connect(self->window_main->header_bar->mi_request_save, "activate", G_CALLBACK(gi_application_mi_save_activated), self);
    g_signal_connect(self->window_main->header_bar->mi_request_clear, "activate", G_CALLBACK(gi_application_mi_clear_activated), self);
}

static void gi_application_init(GiApplication* self) {}

static void gi_application_class_init(GiApplicationClass* class)
{
    GApplicationClass* parent_class = G_APPLICATION_CLASS(class);

    parent_class->activate = gi_application_activate;
}

GiApplication* gi_application_new()
{
    return g_object_new(GI_TYPE_APPLICATION,
        "application-id", APPLICATION_ID,
        "flags", G_APPLICATION_FLAGS_NONE,
        NULL);
}