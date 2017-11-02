/* getit-element-header.h
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

#define GETIT_TYPE_ELEMENT_HEADER (getit_element_header_get_type())

G_DECLARE_FINAL_TYPE (GetitElementHeader, getit_element_header, GETIT, ELEMENT_HEADER, GtkGrid)

/* Public function signatures */
GetitElementHeader *getit_element_header_new ();
GetitElementHeader *getit_element_header_new_with_values (const gboolean  enabled,
                                                          const gchar    *key,
                                                          const gchar    *value);
const gboolean getit_element_header_get_enabled (GetitElementHeader *self);
const gchar *getit_element_header_get_key (GetitElementHeader *self);
const gchar *getit_element_header_get_value (GetitElementHeader *self);

G_END_DECLS
