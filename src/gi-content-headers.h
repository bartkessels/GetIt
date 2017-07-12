/*
 * gi-content-headers.h
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

#ifndef GI_CONTENT_HEADERS_H
#define GI_CONTENT_HEADERS_H

#include <glib-object.h>
#include <gtk/gtk.h>
#include <libsoup/soup.h>

G_BEGIN_DECLS

typedef struct _GiContentHeaders GiContentHeaders;

#define GI_TYPE_CONTENT_HEADERS gi_content_headers_get_type()
G_DECLARE_FINAL_TYPE(GiContentHeaders, gi_content_headers, GI, CONTENT_HEADERS, GtkScrolledWindow)

struct _GiContentHeaders {
    GtkScrolledWindow parent;

    /*
        Member Variables
    */
    GtkWidget* grd_main;
    GtkWidget* btn_add;

    GSList* list_headers;
};

/*
    Methods
*/
GiContentHeaders* gi_content_headers_new();
void gi_content_headers_add_to_request(GiContentHeaders* self, SoupMessage* message);
void gi_content_headers_add_header_with_values(GiContentHeaders* self, const gboolean enabled, const gchar* key, const gchar* value);

G_END_DECLS

#endif /* GI_CONTENT_HEADERS_H */