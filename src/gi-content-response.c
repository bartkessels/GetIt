/*
 * gi-content-response.c
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

#include "gi-content-response.h"

G_DEFINE_TYPE(GiContentResponse, gi_content_response, GTK_TYPE_SCROLLED_WINDOW)

static void gi_content_response_init(GiContentResponse* self)
{
    // Load elements from resource
    GtkBuilder* builder = gtk_builder_new_from_resource("/net/bartkessels/getit/content-response.ui");

    self->grd_main = GTK_WIDGET(gtk_builder_get_object(builder, "grd_main"));
    self->lbl_default_message = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_default_message"));
    self->grd_output = GTK_WIDGET(gtk_builder_get_object(builder, "grd_output"));
    self->grd_headers = GTK_WIDGET(gtk_builder_get_object(builder, "grd_headers"));
    self->sv_output = GTK_WIDGET(gtk_builder_get_object(builder, "sv_output"));
    self->grd_sending = GTK_WIDGET(gtk_builder_get_object(builder, "grd_sending"));
    self->grd_error = GTK_WIDGET(gtk_builder_get_object(builder, "grd_error"));
    self->lbl_error_message = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_error_message"));

    // Show widgets
    gtk_container_add(GTK_CONTAINER(self), self->grd_main);

    g_object_unref(builder);
}

static void gi_content_response_class_init(GiContentResponseClass* class)
{
    GtkScrolledWindowClass* parent_class = GTK_SCROLLED_WINDOW_CLASS(class);
}

static void gi_content_response_add_header(const gchar* name, const gchar* value, gpointer user_data)
{
    GiContentResponse* self = GI_CONTENT_RESPONSE(user_data);
    gint row_index = g_list_length(gtk_container_get_children(GTK_CONTAINER(self->grd_headers))) / 3; // Divide by 3 because there are 3 widgets for each header

    // Initialize labels
    GtkWidget* lbl_header_key = gtk_label_new(name);
    GtkWidget* lbl_arrow = gtk_label_new(NULL);
    GtkWidget* lbl_header_value = gtk_label_new(value);

    // Label arrow
    gtk_label_set_markup(GTK_LABEL(lbl_arrow), "&#8594;");

    // Align labels
    gtk_label_set_xalign(GTK_LABEL(lbl_header_key), 0);
    gtk_label_set_xalign(GTK_LABEL(lbl_header_value), 0);

    // Allow labels to be selected
    gtk_label_set_selectable(GTK_LABEL(lbl_header_key), TRUE);
    gtk_label_set_selectable(GTK_LABEL(lbl_header_value), TRUE);

    // Add labels to grid
    gtk_grid_attach(GTK_GRID(self->grd_headers), lbl_header_key, 0, row_index, 1, 1);
    gtk_grid_attach(GTK_GRID(self->grd_headers), lbl_arrow, 1, row_index, 1, 1);
    gtk_grid_attach(GTK_GRID(self->grd_headers), lbl_header_value, 2, row_index, 1, 1);
}

GiContentResponse* gi_content_response_new()
{
    return g_object_new(GI_TYPE_CONTENT_RESPONSE, NULL);
}

void gi_content_response_show_default(GiContentResponse* self)
{
    gtk_widget_show(self->lbl_default_message);
    gtk_widget_hide(self->grd_output);
    gtk_widget_hide(self->grd_sending);
    gtk_widget_hide(self->grd_error);
}

void gi_content_response_show_sending(GiContentResponse* self)
{
    gtk_widget_hide(self->lbl_default_message);
    gtk_widget_hide(self->grd_output);
    gtk_widget_show(self->grd_sending);
    gtk_widget_hide(self->grd_error);
}

void gi_content_response_show_response(GiContentResponse* self, GtkSourceLanguage* language, SoupMessageHeaders* headers, const gchar* body, guint status_code, const gchar* status_message)
{
    gtk_widget_hide(self->lbl_default_message);
    gtk_widget_show(self->grd_output);
    gtk_widget_hide(self->grd_sending);
    gtk_widget_hide(self->grd_error);

    // Remove previous elements from headers
    GList *children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(self->grd_headers));
    for (iter = children; iter != NULL; iter = g_list_next(iter))
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    g_list_free(children);

    // Populate headers
    const gchar* status_string = g_strdup_printf("%i (%s)", status_code, status_message);

    GtkWidget* lbl_status_key = gtk_label_new("Status");
    GtkWidget* lbl_status_arrow = gtk_label_new(NULL);
    GtkWidget* lbl_status_value = gtk_label_new(status_string);

    gtk_label_set_markup_with_mnemonic(GTK_LABEL(lbl_status_arrow), "&#8594;");

    gtk_label_set_xalign(GTK_LABEL(lbl_status_key), 0);
    gtk_label_set_xalign(GTK_LABEL(lbl_status_value), 0);

    gtk_grid_attach(GTK_GRID(self->grd_headers), lbl_status_key, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(self->grd_headers), lbl_status_arrow, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(self->grd_headers), lbl_status_value, 2, 0, 1, 1);

    soup_message_headers_foreach(headers, gi_content_response_add_header, self);

    // Insert data into sourceview
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(self->sv_output));

    // Check if body isn't empty
    if (body != NULL) {
        gtk_source_buffer_set_language(GTK_SOURCE_BUFFER(buffer), language);
        gtk_text_buffer_set_text(buffer, body, strlen(body));
    }

    // Show all widgets
    gtk_widget_show_all(GTK_WIDGET(self->grd_output));
}

void gi_content_response_show_error(GiContentResponse* self, const gchar* error_message)
{
    gtk_widget_hide(self->lbl_default_message);
    gtk_widget_hide(self->grd_output);
    gtk_widget_hide(self->grd_sending);
    gtk_widget_show(self->grd_error);

    if (error_message == NULL || strlen(error_message) < 1) {
        error_message = RESPONSE_ERROR_MESSAGE;
    }

    gtk_label_set_text(GTK_LABEL(self->lbl_error_message), error_message);
}