/* getit-content-cookies.c
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

#include "getit-content-cookies.h"

struct _GetitContentCookies {
    GtkViewport parent_instance;

    /* Template widgets */
    GtkButton *btn_add;
    GtkGrid *grd_cookies;
};

G_DEFINE_TYPE (GetitContentCookies, getit_content_cookies, GTK_TYPE_VIEWPORT)

/*
 * =============================================================================
 * Signatures
 *
 */
static void getit_content_cookies_class_init (GetitContentCookiesClass *klass);
static void getit_content_cookies_init (GetitContentCookies *self);

/* Callback functions */
static void getit_content_cookies_cb_btn_add_cookie_clicked (GtkWidget *caller,
                                                             gpointer   user_data);

/*
 * =============================================================================
 * Public function implementations
 *
 */
GetitContentCookies *
getit_content_cookies_new ()
{
    GetitContentCookies *content_cookies;

    content_cookies = g_object_new (GETIT_TYPE_CONTENT_COOKIES, NULL);

    return content_cookies;
}

void
getit_content_cookies_clear (GetitContentCookies *self)
{
    g_assert (GETIT_IS_CONTENT_COOKIES (self));

    gint total_list_size;

    /* Clear cookies */
    total_list_size = g_list_length (gtk_container_get_children (GTK_CONTAINER (self->grd_cookies)));

    /*
     * Iterate through elements
     */
    for (int list_iterator = 0; list_iterator <= total_list_size; list_iterator++) {
        GetitElementCookie *cookie;

        cookie = GETIT_ELEMENT_COOKIE (gtk_grid_get_child_at (self->grd_cookies, 0, list_iterator));
        g_object_run_dispose (G_OBJECT (cookie));
    }
}

void
getit_content_cookies_add_to_request (GetitContentCookies *self,
                                      SoupMessage         *soup_message,
                                      SoupURI             *uri)
{
    g_assert (GETIT_IS_CONTENT_COOKIES (self));
    g_assert (SOUP_IS_MESSAGE (soup_message));

    g_return_if_fail (SOUP_URI_IS_VALID (uri));

    GSList *cookie_list;
    gint total_cookies;

    cookie_list = NULL;

    /*
     * Count the cookie elements in the grid
     */
    total_cookies = g_list_length (gtk_container_get_children (GTK_CONTAINER (self->grd_cookies)));

    /*
     * Iterate through all the cookies
     */
    for (int list_iterator = 0; list_iterator <= total_cookies; list_iterator++) {
        GetitElementCookie *cookie;
        SoupCookie *soup_cookie;

        GtkWidget *current_widget;
        gboolean is_enabled;
        const gchar *key;
        const gchar *value;

        /* Skip this iteration if it's not a cookie type */
        current_widget = gtk_grid_get_child_at (GTK_GRID (self->grd_cookies), 0, list_iterator);

        if (!GETIT_IS_ELEMENT_COOKIE (current_widget)) {
            continue;
        }

        cookie = GETIT_ELEMENT_COOKIE (current_widget);
        is_enabled = getit_element_cookie_get_enabled (cookie);
        key = getit_element_cookie_get_key (cookie);
        value = getit_element_cookie_get_value (cookie);

        /* Skip this iteration if it's not enabled */
        if (!is_enabled) {
            continue;
        }

        soup_cookie = soup_cookie_new (key, value, soup_uri_get_host (uri), NULL, -1);
        cookie_list = g_slist_append (cookie_list, soup_cookie);
    }

    soup_cookies_to_request (cookie_list, soup_message);
}

void
getit_content_cookies_add_to_json_object (GetitContentCookies *self,
                                          JsonObject          *json_cookies_object,
                                          const gchar         *cookies_array_name,
                                          const gchar         *enabled_key,
                                          const gchar         *key_key,
                                          const gchar         *value_key)
{
    g_assert (GETIT_IS_CONTENT_COOKIES (self));
    g_assert_nonnull (json_cookies_object);

    JsonArray *json_array_cookies;
    gint total_cookies;

    json_array_cookies = json_array_new ();

    /*
     * Count the cookie elements in the grid
     */
    total_cookies = g_list_length (gtk_container_get_children (GTK_CONTAINER (self->grd_cookies)));

    /*
     * Iterate through all the cookies
     */
    for (int list_iterator = 0; list_iterator <= total_cookies; list_iterator++) {
        GetitElementCookie *cookie;
        JsonObject *json_object_cookie;

        GtkWidget *current_widget;
        gboolean is_enabled;
        const gchar *key;
        const gchar *value;

        /* Skip this iteration if it's not a cookie type */
        current_widget = gtk_grid_get_child_at (GTK_GRID (self->grd_cookies), 0, list_iterator);

        if (!GETIT_IS_ELEMENT_COOKIE (current_widget)) {
            continue;
        }

        cookie = GETIT_ELEMENT_COOKIE (current_widget);
        json_object_cookie = json_object_new ();
        is_enabled = getit_element_cookie_get_enabled (cookie);
        key = getit_element_cookie_get_key (cookie);
        value = getit_element_cookie_get_value (cookie);

        /* Add values to formdata object */
        json_object_set_boolean_member (json_object_cookie, enabled_key, is_enabled);
        json_object_set_string_member (json_object_cookie, key_key, key);
        json_object_set_string_member (json_object_cookie, value_key, value);

        json_array_add_object_element (json_array_cookies, json_object_cookie);
    }

    json_object_set_array_member (json_cookies_object, cookies_array_name, json_array_cookies);
}

void
getit_content_cookies_add_cookie_with_values (GetitContentCookies *self,
                                              const gboolean       enabled,
                                              const gchar         *key,
                                              const gchar         *value)
{
    g_assert (GETIT_IS_CONTENT_COOKIES (self));

    gtk_container_add (GTK_CONTAINER (self->grd_cookies),
                       GTK_WIDGET (getit_element_cookie_new_with_values (enabled,
                                                                         key,
                                                                         value)));
}

 /*
 * =============================================================================
 * Private function implementations
 *
 */
static void
getit_content_cookies_class_init (GetitContentCookiesClass *klass)
{
    GtkWidgetClass *widget_class;

    widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/net/bartkessels/getit/content-cookies.ui");
    gtk_widget_class_bind_template_child (widget_class, GetitContentCookies, btn_add);
    gtk_widget_class_bind_template_child (widget_class, GetitContentCookies, grd_cookies);
}

static void
getit_content_cookies_init (GetitContentCookies *self)
{
    g_assert (GETIT_IS_CONTENT_COOKIES (self));
    g_assert (GTK_IS_WIDGET (self));

    gtk_widget_init_template (GTK_WIDGET (self));

    g_signal_connect (self->btn_add, "clicked", G_CALLBACK (getit_content_cookies_cb_btn_add_cookie_clicked), self->grd_cookies);
}

 /*
 * =============================================================================
 * Private callback implementations
 *
 */
static void
getit_content_cookies_cb_btn_add_cookie_clicked (GtkWidget *caller,
                                                 gpointer   user_data)
{
    g_assert (GTK_IS_BUTTON (caller));
    g_assert (GTK_IS_GRID (user_data));

    gtk_container_add (GTK_CONTAINER (user_data),
                       GTK_WIDGET (getit_element_cookie_new ()));
}
