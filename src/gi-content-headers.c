/*
 * gi-content-headers.c
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
#include <libsoup/soup.h>

#include "gi-content-headers.h"
#include "gi-element-header.h"

G_DEFINE_TYPE(GiContentHeaders, gi_content_headers, GTK_TYPE_SCROLLED_WINDOW)
static void gi_content_headers_class_init(GiContentHeadersClass* class) {}

static GiContentHeaders* gi_content_headers;

/**
 * gi_content_headers_header_btn_remove_clicked
 *
 * @caller: The GtkWidget which is calling this function
 * @user_data: Pointer to GiElementHeader object
 *
 * Remove the given GiElementHeader object from the UI and from
 * the cookies list
 *
 * Return value: void
 */
static void gi_content_headers_header_btn_remove_clicked(GtkWidget* caller, gpointer user_data)
{
    GiContentHeaders* self = gi_content_headers;
    GiElementHeader* header = GI_ELEMENT_HEADER(user_data);

    self->list_headers = g_slist_remove(self->list_headers, header);
    gtk_widget_destroy(GTK_WIDGET(header));
}

/**
 * gi_content_headers_btn_add_clicked
 *
 * @caller: The GtkWidget which is calling this function
 * @user_data: Pointer to self
 *
 * Add a new GiElementHeader object to the UI and to the list
 *
 * Return value: void
 */
static void gi_content_headers_btn_add_clicked(GtkWidget* caller, gpointer user_data)
{
    GiContentHeaders* self = GI_CONTENT_HEADERS(user_data);

    GiElementHeader* header = gi_element_header_new();
    g_signal_connect(header->btn_remove, "clicked", G_CALLBACK(gi_content_headers_header_btn_remove_clicked), header);
    self->list_headers = g_slist_append(self->list_headers, header);
    gtk_container_add(GTK_CONTAINER(self->grd_main), GTK_WIDGET(header));
}

/**
 * gi_content_headers_init
 *
 * @self: Pointer to self
 *
 * Build the UI from the .ui file in the resources
 *
 * Return value: void
 */
static void gi_content_headers_init(GiContentHeaders* self)
{
    // Load elements from resources
    GtkBuilder* builder = gtk_builder_new_from_resource("/net/bartkessels/getit/content-headers.ui");

    self->grd_main = GTK_WIDGET(gtk_builder_get_object(builder, "grd_main"));
    self->btn_add = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add"));

    // Connect signals
    g_signal_connect(self->btn_add, "clicked", G_CALLBACK(gi_content_headers_btn_add_clicked), self);

    // Show widgets
    gtk_container_add(GTK_CONTAINER(self), self->grd_main);

    g_object_unref(builder);
}

/**
 * gi_content_headers_new
 *
 * Create new instance of GiContentCookies
 *
 * Return value: GiContentHeaders
 */
GiContentHeaders* gi_content_headers_new()
{
    GiContentHeaders* content_headers = g_object_new(GI_TYPE_CONTENT_HEADERS, NULL);
    gi_content_headers = content_headers;

    return content_headers;
}

/**
 * gi_content_headers_add_to_request
 *
 * @self: Pointer to self
 * @message: Pointer to SoupMessage
 *
 * All all elements of self to the SoupMessage request
 *
 * Return value: void
 */
void gi_content_headers_add_to_request(GiContentHeaders* self, SoupMessage* message)
{
    // Add headers to request
    for (gint list_headers_index = 0; list_headers_index < g_slist_length(self->list_headers); list_headers_index++) {
        GiElementHeader* header = GI_ELEMENT_HEADER(g_slist_nth_data(self->list_headers, list_headers_index));

        // Check if header element is enabled
        if (!gi_element_header_get_enabled(header)) {
            return;
        }

        const gchar* key = gtk_entry_get_text(GTK_ENTRY(header->et_key));
        const gchar* value = gtk_entry_get_text(GTK_ENTRY(header->et_value));

        // Add header to message
        soup_message_headers_append(message->request_headers, key, value);
    }
}

/**
 * gi_content_headers_add_header_with_values
 *
 * @self: Pointer to self
 * @enabled: Wheter or not the GiElementHeader object is enabled
 * @key: Key of the pair
 * @value: Value of the pair
 *
 * Add a new GiElementHeader to the UI and list with
 * values filled in
 *
 * Return value: void
 */
void gi_content_headers_add_header_with_values(GiContentHeaders* self, const gboolean enabled, const gchar* key, const gchar* value)
{
    GiElementHeader* header = gi_element_header_new();
    g_signal_connect(header->btn_remove, "clicked", G_CALLBACK(gi_content_headers_header_btn_remove_clicked), header);

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(header->cbtn_enabled), enabled);
    gtk_entry_set_text(GTK_ENTRY(header->et_key), key);
    gtk_entry_set_text(GTK_ENTRY(header->et_value), value);

    self->list_headers = g_slist_append(self->list_headers, header);
    gtk_container_add(GTK_CONTAINER(self->grd_main), GTK_WIDGET(header));
}