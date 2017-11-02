/* getit-element-formdata.h
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

#pragma once

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GETIT_TYPE_ELEMENT_FORMDATA (getit_element_formdata_get_type())

G_DECLARE_FINAL_TYPE (GetitElementFormdata, getit_element_formdata, GETIT, ELEMENT_FORMDATA, GtkGrid)

/* Datatype information */
#define DATATYPE_STRING "data_type_string"
#define DATATYPE_FILE "data_type_file"

/* Public function signatures */
GetitElementFormdata *getit_element_formdata_new ();
GetitElementFormdata *getit_element_formdata_new_with_values (const gboolean    enabled,
                                                              const gchar      *key,
                                                              const gchar      *value,
                                                              const gchar      *file,
                                                              const gint        type);
gboolean getit_element_formdata_get_enabled (GetitElementFormdata *self);
const gchar *getit_element_formdata_get_datatype (GetitElementFormdata *self);
gint getit_element_formdata_get_datatype_int (GetitElementFormdata *self);
const gchar *getit_element_formdata_get_key (GetitElementFormdata *self);
const gchar *getit_element_formdata_get_value (GetitElementFormdata *self);
const gchar *getit_element_formdata_get_filename (GetitElementFormdata *self);

G_END_DECLS
