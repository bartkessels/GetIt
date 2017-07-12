/*
 * gi-content-body.h
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

#ifndef GI_CONTENT_BODY_H
#define GI_CONTENT_BODY_H

#include <glib-object.h>
#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>
#include <libsoup/soup.h>

#define BODY_TYPE_FORMDATA "BODY_TYPE_FORMDATA"
#define BODY_TYPE_RAW "BODY_TYPE_RAW"

G_BEGIN_DECLS

typedef struct _GiContentBody GiContentBody;

#define GI_TYPE_CONTENT_BODY gi_content_body_get_type()
G_DECLARE_FINAL_TYPE(GiContentBody, gi_content_body, GI, CONTENT_BODY, GtkScrolledWindow)

struct _GiContentBody {
    GtkScrolledWindow parent;

    /*
        Member Variables
    */
    GtkStack* stack_data;

    GtkWidget* grd_main;
    GtkWidget* cb_method;
    GtkWidget* et_uri;
    GtkWidget* sw_data;
    GtkWidget* grd_data_formdata;
    GtkWidget* grd_data_raw;
    GtkWidget* btn_data_formdata_add;
    GtkWidget* cb_data_raw_syntax;
    GtkWidget* sv_data_raw_input;

    GSList* list_formdata;
    SoupMultipart* multipart;
};

/*
    Methods
*/
GiContentBody* gi_content_body_new();
void gi_content_body_add_to_request(GiContentBody* self, SoupMessage* message);
const gchar* gi_content_body_get_data_raw(GiContentBody* self);
void gi_content_body_set_data_raw(GiContentBody* self, const gchar* data);
void gi_content_body_add_formdata_with_values(GiContentBody* self, const gboolean enabled, const gchar* key, const gchar* value, const gchar* file, const gint type);

G_END_DECLS

#endif /* GI_CONTENT_BODY_H */