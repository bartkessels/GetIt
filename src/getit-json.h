/* getit-json.h
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

#include <json-glib/json-glib.h>

#include "getit-content-body.h"
#include "getit-content-cookies.h"
#include "getit-content-headers.h"
#include "getit-content-response.h"

#define FILE_EXTENSION ".getit"

/* JSON variables */
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
#define JSON_COOKIES_ENABLED_KEY "enabled"
#define JSON_COOKIES_KEY_KEY "key"
#define JSON_COOKIES_VALUE_KEY "value"

#define JSON_HEADERS_NAME "headers"
#define JSON_HEADERS_ENABLED_KEY "enabled"
#define JSON_HEADERS_KEY_KEY "key"
#define JSON_HEADERS_VALUE_KEY "value"

/* Public function signatures */
gboolean getit_json_save_file (GetitContentBody    *content_body,
                               GetitContentCookies *content_cookies,
                               GetitContentHeaders *content_headers,
                               const gchar         *file_name);
gboolean getit_json_open_file (GetitContentBody     *content_body,
                               GetitContentCookies  *content_cookies,
                               GetitContentHeaders  *content_headers,
                               GetitContentResponse *content_response,
                               const gchar          *file_name);
