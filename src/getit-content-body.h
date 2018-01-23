/* getit-content-body.h
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
#include <gtksourceview/gtksource.h>
#include <libsoup/soup.h>
#include <string.h>
#include <json-glib/json-glib.h>

#include "getit-element-formdata.h"

G_BEGIN_DECLS

#define GETIT_TYPE_CONTENT_BODY (getit_content_body_get_type())

G_DECLARE_FINAL_TYPE (GetitContentBody, getit_content_body, GETIT, CONTENT_BODY, GtkViewport)

/* Data type stack information */
#define BODY_TYPE_FORMDATA "BODY_TYPE_FORMDATA"
#define BODY_TYPE_RAW "BODY_TYPE_RAW"

/* Public function signatures */
GetitContentBody *getit_content_body_new ();
void getit_content_body_clear (GetitContentBody *self);
const gchar *getit_content_body_get_uri (GetitContentBody *self);
const gchar *getit_content_body_get_method (GetitContentBody *self);
const gchar *getit_content_body_get_data_raw (GetitContentBody *self);
const gchar *getit_content_body_get_data_type (GetitContentBody *self);
void getit_content_body_set_raw_input (GetitContentBody *self,
                                       const gchar      *input);
void getit_content_body_add_to_request (GetitContentBody *self,
                                        SoupMessage      *soup_message);
void getit_content_body_add_to_json_object (GetitContentBody *self,
                                            JsonObject       *json_body_object,
                                            const gchar      *formdata_array_name,
                                            const gchar      *body_uri_key,
                                            const gchar      *body_method_key,
                                            const gchar      *body_data_type_key,
                                            const gchar      *raw_language_key,
                                            const gchar      *raw_string_key,
                                            const gchar      *enabled_key,
                                            const gchar      *key_key,
                                            const gchar      *value_key,
                                            const gchar      *file_key,
                                            const gchar      *type_key);
void getit_content_body_add_formdata_with_values (GetitContentBody *self,
                                                  const gboolean    enabled,
                                                  const gchar      *key,
                                                  const gchar      *value,
                                                  const gchar      *file,
                                                  const gint        type);
void getit_content_body_set_values (GetitContentBody *self,
                                    const gint        method,
                                    const gchar      *uri,
                                    const gchar      *data_type,
                                    const gint        raw_language,
                                    const gchar      *raw_input);

G_END_DECLS
