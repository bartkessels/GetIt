/*
 * gi-content-cookies.c
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

#include "gi-content-cookies.h"
#include "gi-element-cookie.h"

G_DEFINE_TYPE(GiContentCookies, gi_content_cookies, GTK_TYPE_SCROLLED_WINDOW)
static void gi_content_cookies_class_init(GiContentCookiesClass* class) {}

static GiContentCookies* gi_content_cookies;

/**
 * gi_content_cookies_cookie_btn_remove_clicked
 *
 * @caller: The GtkWidget which is calling this function
 * @user_data: Pointer to GiElementCookie object
 *
 * Remove the given GiElementCookie object from the UI and from
 * the cookies list
 *
 * Return value: void
 */
static void gi_content_cookies_cookie_btn_remove_clicked(GtkWidget* caller, gpointer user_data)
{
    GiContentCookies* self = gi_content_cookies;
    GiElementCookie* cookie = GI_ELEMENT_COOKIE(user_data);

    self->list_cookies = g_slist_remove(self->list_cookies, cookie);
    gtk_widget_destroy(GTK_WIDGET(cookie));
}

/**
 * gi_content_cookies_btn_add_clicked
 *
 * @caller: The GtkWidget which is calling this function
 * @user_data: Pointer to self
 *
 * Add a new GiElementCookie object to the UI and to the list
 *
 * Return value: void
 */
static void gi_content_cookies_btn_add_clicked(GtkWidget* caller, gpointer user_data)
{
    GiContentCookies* self = GI_CONTENT_COOKIES(user_data);

    GiElementCookie* cookie = gi_element_cookie_new();
    g_signal_connect(cookie->btn_remove, "clicked", G_CALLBACK(gi_content_cookies_cookie_btn_remove_clicked), cookie);
    self->list_cookies = g_slist_append(self->list_cookies, cookie);
    gtk_container_add(GTK_CONTAINER(self->grd_main), GTK_WIDGET(cookie));
}

/**
 * gi_content_cookies_init
 *
 * @self: Pointer to self
 *
 * Build the UI from the .ui file in the resources
 *
 * Return value: void
 */
static void gi_content_cookies_init(GiContentCookies* self)
{
    // Load elements from resource
    GtkBuilder* builder = gtk_builder_new_from_resource("/net/bartkessels/getit/content-cookies.ui");

    self->grd_main = GTK_WIDGET(gtk_builder_get_object(builder, "grd_main"));
    self->btn_add = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add"));

    // Connect signals
    g_signal_connect(self->btn_add, "clicked", G_CALLBACK(gi_content_cookies_btn_add_clicked), self);

    // Show widgets
    gtk_container_add(GTK_CONTAINER(self), self->grd_main);

    g_object_unref(builder);
}

/**
 * gi_content_cookies_new
 *
 * Create new instance of GiContentCookies
 *
 * Return value: GiContentCookies
 */
GiContentCookies* gi_content_cookies_new()
{
    GiContentCookies* content_cookies = g_object_new(GI_TYPE_CONTENT_COOKIES, NULL);
    gi_content_cookies = content_cookies;

    return content_cookies;
}

/**
 * gi_content_cookies_add_to_request
 *
 * @self: Pointer to self
 * @message: Pointer to SoupMessage
 * @uri: Pointer to the used SoupURI
 *
 * All all elements of self to the SoupMessage request
 *
 * Return value: void
 */
void gi_content_cookies_add_to_request(GiContentCookies* self, SoupMessage* message, SoupURI* uri)
{
    // Empty list_soup_cookies
    for (gint list_soup_cookies_index = 0; list_soup_cookies_index < g_slist_length(self->list_soup_cookies); list_soup_cookies_index++) {
        gpointer data = g_slist_nth_data(self->list_soup_cookies, list_soup_cookies_index);
        self->list_soup_cookies = g_slist_remove(self->list_soup_cookies, data);
    }

    // Add cookies to list_cookies
    for (gint list_cookies_index = 0; list_cookies_index < g_slist_length(self->list_cookies); list_cookies_index++) {
        GiElementCookie* cookie = GI_ELEMENT_COOKIE(g_slist_nth_data(self->list_cookies, list_cookies_index));

        // Check if cookie element is enabled
        if (!gi_element_cookie_get_enabled(cookie)) {
            return;
        }

        const gchar* key = gtk_entry_get_text(GTK_ENTRY(cookie->et_key));
        const gchar* value = gtk_entry_get_text(GTK_ENTRY(cookie->et_value));

        SoupCookie* soup_cookie = soup_cookie_new(key, value, soup_uri_get_host(uri), NULL, -1);
        self->list_soup_cookies = g_slist_append(self->list_soup_cookies, soup_cookie);
    }

    soup_cookies_to_request(self->list_soup_cookies, message);
}

/**
 * gi_content_cookies_add_cookie_with_values
 *
 * @self: Pointer to self
 * @enabled: Wheter or not the GiElementCookie object is enabled
 * @key: Key of the pair
 * @value: Value of the pair
 *
 * Add a new GiElementCookie to the UI and list with
 * values filled in
 *
 * Return value: void
 */
void gi_content_cookies_add_cookie_with_values(GiContentCookies* self, const gboolean enabled, const gchar* key, const gchar* value)
{
    GiElementCookie* cookie = gi_element_cookie_new();
    g_signal_connect(cookie->btn_remove, "clicked", G_CALLBACK(gi_content_cookies_cookie_btn_remove_clicked), cookie);

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(cookie->cbtn_enabled), enabled);
    gtk_entry_set_text(GTK_ENTRY(cookie->et_key), key);
    gtk_entry_set_text(GTK_ENTRY(cookie->et_value), value);

    self->list_cookies = g_slist_append(self->list_cookies, cookie);
    gtk_container_add(GTK_CONTAINER(self->grd_main), GTK_WIDGET(cookie));
}