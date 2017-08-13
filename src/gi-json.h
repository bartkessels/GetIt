/*
 * gi-json.h
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

#ifndef GI_JSON_H
#define GI_JSON_H

#include <glib.h>

#include "gi-window-main.h"

#define FILE_EXTENSION ".getit"

#define JSON_BODY_NAME "body"
#define JSON_BODY_METHOD_KEY "method"
#define JSON_BODY_URI_KEY "uri"
#define JSON_BODY_DATA_TYPE_KEY "data_type"
#define JSON_BODY_RAW_LANGUAGE_KEY "raw_language"
#define JSON_BODY_RAW_INPUT_KEY "raw"

#define JSON_FORMDATA_NAME "form"
#define JSON_FORMDATA_ENABLED_KEY "enabled"
#define JSON_FORMDATA_KEY_KEY "key"
#define JSON_FORMDATA_VALUE_KEY "value"
#define JSON_FORMDATA_FILE_KEY "file"
#define JSON_FORMDATA_TYPE_KEY "type"

#define JSON_COOKIES_NAME "cookies"

#define JSON_COOKIE_ENABLED_KEY "enabled"
#define JSON_COOKIE_KEY_KEY "key"
#define JSON_COOKIE_VALUE_KEY "value"

#define JSON_HEADERS_NAME "headers"

#define JSON_HEADER_ENABLED_KEY "enabled"
#define JSON_HEADER_KEY_KEY "key"
#define JSON_HEADER_VALUE_KEY "value"

gboolean gi_json_save_file(GiWindowMain* window_main, const gchar* filename);
gboolean gi_json_open_file(GiWindowMain* window_main, const gchar* filename);

#endif /* GI_JSON_H */