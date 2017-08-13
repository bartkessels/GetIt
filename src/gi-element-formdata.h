/*
 * gi-element-formdata.h
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

#ifndef G_ELEMENT_FORMDATA_H
#define G_ELEMENT_FORMDATA_H

#include <glib-object.h>
#include <gtk/gtk.h>

#define DATA_TYPE_STRING "data_type_string"
#define DATA_TYPE_FILE "data_type_file"

G_BEGIN_DECLS

typedef struct _GiElementFormdata GiElementFormdata;

#define GI_TYPE_ELEMENT_FORMDATA gi_element_formdata_get_type()
G_DECLARE_FINAL_TYPE(GiElementFormdata, gi_element_formdata, GI, ELEMENT_FORMDATA, GtkGrid)

struct _GiElementFormdata {
    GtkGrid parent;

    /*
        Member Variables
    */
    GtkWidget* grd_main;
    GtkWidget* cbtn_enabled;
    GtkWidget* et_key;
    GtkWidget* et_value;
    GtkWidget* fcbtn_file;
    GtkWidget* cb_type;
    GtkWidget* btn_remove;
};

/*
    Methods
*/
GiElementFormdata* gi_element_formdata_new();
gboolean gi_element_formdata_get_enabled(GiElementFormdata* self);
const gchar* gi_element_formdata_get_data_type(GiElementFormdata* self);

G_END_DECLS

#endif /* G_ELEMENT_FORMDATA_H */