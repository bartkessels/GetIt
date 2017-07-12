/*
 * gi-content-cookies.h
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

#ifndef GI_CONTENT_COOKIES_H
#define GI_CONTENT_COOKIES_H

#include <glib-object.h>
#include <gtk/gtk.h>
#include <libsoup/soup.h>

G_BEGIN_DECLS

typedef struct _GiContentCookies GiContentCookies;

#define GI_TYPE_CONTENT_COOKIES gi_content_cookies_get_type()
G_DECLARE_FINAL_TYPE(GiContentCookies, gi_content_cookies, GI, CONTENT_COOKIES, GtkScrolledWindow)

struct _GiContentCookies {
    GtkScrolledWindow parent;

    /*
        Member Variables
    */
    GtkWidget* grd_main;
    GtkWidget* btn_add;

    GSList* list_cookies;
    GSList* list_soup_cookies;
};

/*
    Methods
*/
GiContentCookies* gi_content_cookies_new();
void gi_content_cookies_add_to_request(GiContentCookies* self, SoupMessage* message, SoupURI* uri);
void gi_content_cookies_add_cookie_with_values(GiContentCookies* self, const gboolean enabled, const gchar* key, const gchar* value);

G_END_DECLS

#endif /* GI_CONTENT_COOKIES_H */