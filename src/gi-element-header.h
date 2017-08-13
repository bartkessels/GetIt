/*
 * gi-element-header.h
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

#ifndef GI_ELEMENT_HEADER_H
#define GI_ELEMENT_HEADER_H

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _GiElementHeader GiElementHeader;

#define GI_TYPE_ELEMENT_HEADER gi_element_header_get_type()
G_DECLARE_FINAL_TYPE(GiElementHeader, gi_element_header, GI, ELEMENT_HEADER, GtkGrid)

struct _GiElementHeader {
    GtkGrid parent;

    /*
        Member Variables
    */
    GtkWidget* grd_main;
    GtkWidget* cbtn_enabled;
    GtkWidget* et_key;
    GtkWidget* et_value;
    GtkWidget* btn_remove;
};

/*
    Methods
*/
GiElementHeader* gi_element_header_new();
gboolean gi_element_header_get_enabled(GiElementHeader* self);

G_END_DECLS

#endif /* GI_ELEMENT_HEADER_H */