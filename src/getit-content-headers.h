/* getit-content-headers.h
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
#include <libsoup/soup.h>
#include <json-glib/json-glib.h>

#include "getit-element-header.h"

G_BEGIN_DECLS

#define GETIT_TYPE_CONTENT_HEADERS (getit_content_headers_get_type())

G_DECLARE_FINAL_TYPE (GetitContentHeaders, getit_content_headers, GETIT, CONTENT_HEADERS, GtkScrolledWindow)

/* Public function signatures */
GetitContentHeaders *getit_content_headers_new ();
void getit_content_headers_clear (GetitContentHeaders *self);
void getit_content_headers_add_to_request (GetitContentHeaders *self,
                                           SoupMessage         *soup_message);
void getit_content_headers_add_to_json_object (GetitContentHeaders *self,
                                               JsonObject          *json_headers_object,
                                               const gchar         *headers_array_name,
                                               const gchar         *enabled_key,
                                               const gchar         *key_key,
                                               const gchar         *value_key);
void getit_content_headers_add_header_with_values (GetitContentHeaders *self,
                                                   const gboolean       enabled,
                                                   const gchar         *key,
                                                   const gchar         *value);

G_END_DECLS
