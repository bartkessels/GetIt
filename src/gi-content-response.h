/*
 * gi-content-response.h
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

#ifndef GI_CONTENT_RESPONSE_H
#define GI_CONTENT_RESPONSE_H

#include <glib-object.h>
#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>

#define RESPONSE_ERROR_MESSAGE "Something went wrong sending your request..."

G_BEGIN_DECLS

typedef struct _GiContentResponse GiContentResponse;

#define GI_TYPE_CONTENT_RESPONSE gi_content_response_get_type()
G_DECLARE_FINAL_TYPE(GiContentResponse, gi_content_response, GI, CONTENT_RESPONSE, GtkScrolledWindow)

struct _GiContentResponse {
    GtkScrolledWindow parent;

    /*
        Member Variables
    */
    GtkWidget* grd_main;
    GtkWidget* lbl_default_message;
    GtkWidget* grd_output;
    GtkWidget* grd_headers;
    GtkWidget* sv_output;
    GtkWidget* grd_sending;
    GtkWidget* grd_error;
    GtkWidget* lbl_error_message;
};

/*
    Methods
*/
GiContentResponse* gi_content_response_new();
void gi_content_response_show_default(GiContentResponse* self);
void gi_content_response_show_sending(GiContentResponse* self);
void gi_content_response_show_response(GiContentResponse* self, GtkSourceLanguage* language, SoupMessageHeaders* headers, const gchar* body, guint status_code, const gchar* status_message);
void gi_content_response_show_error(GiContentResponse* self, const gchar* error_message);

G_END_DECLS

#endif /* GI_CONTENT_RESPONSE_H */