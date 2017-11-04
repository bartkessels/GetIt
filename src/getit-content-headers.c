/* getit-content-headers.c
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
 */

#include "getit-content-headers.h"

struct _GetitContentHeaders {
    GtkScrolledWindow parent_instance;

    /* Template widgets */
    GtkGrid *grd_main;
    GtkButton *btn_add;
};

G_DEFINE_TYPE (GetitContentHeaders, getit_content_headers, GTK_TYPE_SCROLLED_WINDOW)

/*
 * =============================================================================
 * Signatures
 *
 */
static void getit_content_headers_class_init (GetitContentHeadersClass *klass);
static void getit_content_headers_init (GetitContentHeaders *self);

/* Callback signatures */
static void getit_content_headers_cb_btn_add_header_clicked (GtkWidget *caller,
                                                             gpointer   user_data);

/*
 * =============================================================================
 * Public function implementations
 *
 */
GetitContentHeaders *
getit_content_headers_new ()
{
    GetitContentHeaders *content_headers;

    content_headers = g_object_new (GETIT_TYPE_CONTENT_HEADERS, NULL);

    return content_headers;
}

void
getit_content_headers_clear (GetitContentHeaders *self)
{
    g_assert (GETIT_IS_CONTENT_HEADERS (self));

    gint total_list_size;

    /* Clear cookies */
    total_list_size = g_list_length (gtk_container_get_children (GTK_CONTAINER (self->grd_main))) - 1;

    /*
     * Start iteration at 1 'cause the first element
     * in the grid is the 'Add' button
     */
    for (int list_iterator = 1; list_iterator <= total_list_size; list_iterator++) {
        GetitElementHeader *header;

        header = GETIT_ELEMENT_HEADER (gtk_grid_get_child_at (self->grd_main, 0, list_iterator));
        g_object_run_dispose (G_OBJECT (header));
    }
}

void
getit_content_headers_add_to_request (GetitContentHeaders *self,
                                      SoupMessage         *soup_message)
{
    g_assert (GETIT_IS_CONTENT_HEADERS (self));
    g_assert (SOUP_IS_MESSAGE (soup_message));

    gint total_headers;

    /*
     * Count the formdata elements in the grid
     * Minus 1 'cause the grid contains the 'Add' button
     */
    total_headers = g_list_length (gtk_container_get_children (GTK_CONTAINER (self->grd_main))) - 1;

    /*
     * Start iteration at 1 'cause the first element
     * in the grid is the 'Add' button
     */
    for (int list_iterator = 1; list_iterator <= total_headers; list_iterator++) {
        GetitElementHeader *header;

        GtkWidget *current_widget;
        gboolean is_enabled;
        const gchar *key;
        const gchar *value;

        /* Skip this iteration if it's not a header type */
        current_widget = gtk_grid_get_child_at (GTK_GRID (self->grd_main), 0, list_iterator);

        if (!GETIT_IS_ELEMENT_HEADER (current_widget)) {
            continue;
        }

        header = GETIT_ELEMENT_HEADER (current_widget);
        is_enabled = getit_element_header_get_enabled (header);
        key = getit_element_header_get_key (header);
        value = getit_element_header_get_value (header);

        /* Skip this iteration if it's not enabled */
        if (!is_enabled) {
            continue;
        }

        soup_message_headers_append (soup_message->request_headers, key, value);
    }
}

void
getit_content_headers_add_to_json_object (GetitContentHeaders *self,
                                          JsonObject          *json_headers_object,
                                          const gchar         *headers_array_name,
                                          const gchar         *enabled_key,
                                          const gchar         *key_key,
                                          const gchar         *value_key)
{
    g_assert (GETIT_IS_CONTENT_HEADERS (self));
    g_assert_nonnull (json_headers_object);

    JsonArray *json_array_headers;
    gint total_headers;

    json_array_headers = json_array_new ();

    /*
     * Count the cookie elements in the grid
     * Minus 1 'cause the grid contains the 'Add' button
     */
    total_headers = g_list_length (gtk_container_get_children (GTK_CONTAINER (self->grd_main))) - 1;

    /*
     * Start iteration at 1 'cause the first element
     * in the grid is the 'Add' button
     */
    for (int list_iterator = 1; list_iterator <= total_headers; list_iterator++) {
        GetitElementHeader *header;
        JsonObject *json_object_header;

        GtkWidget *current_widget;
        gboolean is_enabled;
        const gchar *key;
        const gchar *value;

        /* Skip this iteration if it's not a cookie type */
        current_widget = gtk_grid_get_child_at (GTK_GRID (self->grd_main), 0, list_iterator);

        if (!GETIT_IS_ELEMENT_HEADER (current_widget)) {
            continue;
        }

        header = GETIT_ELEMENT_HEADER (current_widget);
        json_object_header = json_object_new ();
        is_enabled = getit_element_header_get_enabled (header);
        key = getit_element_header_get_key (header);
        value = getit_element_header_get_value (header);

        /* Add values to formdata object */
        json_object_set_boolean_member (json_object_header, enabled_key, is_enabled);
        json_object_set_string_member (json_object_header, key_key, key);
        json_object_set_string_member (json_object_header, value_key, value);

        json_array_add_object_element (json_array_headers, json_object_header);
    }

    json_object_set_array_member (json_headers_object, headers_array_name, json_array_headers);
}

void
getit_content_headers_add_header_with_values (GetitContentHeaders *self,
                                              const gboolean       enabled,
                                              const gchar         *key,
                                              const gchar         *value)
{
    g_assert (GETIT_IS_CONTENT_HEADERS (self));

    gtk_container_add (GTK_CONTAINER (self->grd_main),
                       GTK_WIDGET (getit_element_header_new_with_values (enabled,
                                                                         key,
                                                                         value)));
}

 /*
 * =============================================================================
 * Private function implementations
 *
 */
static void
getit_content_headers_class_init (GetitContentHeadersClass *klass)
{
    GtkWidgetClass *widget_class;

    widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/net/bartkessels/getit/content-headers.ui");
    gtk_widget_class_bind_template_child (widget_class, GetitContentHeaders, grd_main);
    gtk_widget_class_bind_template_child (widget_class, GetitContentHeaders, btn_add);
}

static void
getit_content_headers_init (GetitContentHeaders *self)
{
    g_assert (GETIT_IS_CONTENT_HEADERS (self));
    g_assert (GTK_IS_WIDGET (self));

    gtk_widget_init_template (GTK_WIDGET (self));

    g_signal_connect (self->btn_add, "clicked", G_CALLBACK (getit_content_headers_cb_btn_add_header_clicked), self->grd_main);
}

 /*
 * =============================================================================
 * Private callback implementations
 *
 */
static void
getit_content_headers_cb_btn_add_header_clicked (GtkWidget *caller,
                                                 gpointer   user_data)
{
    g_assert (GTK_IS_BUTTON (caller));
    g_assert (GTK_IS_GRID (user_data));

    gtk_container_add (GTK_CONTAINER (user_data),
                       GTK_WIDGET (getit_element_header_new ()));
}
