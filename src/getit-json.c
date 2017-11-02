/* getit-json.c
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

#include "getit-json.h"

gboolean
getit_json_save_file (GetitContentBody    *content_body,
                      GetitContentCookies *content_cookies,
                      GetitContentHeaders *content_headers,
                      const gchar         *file_name)
{
    g_assert (GETIT_IS_CONTENT_BODY (content_body));
    g_assert (GETIT_IS_CONTENT_COOKIES (content_cookies));
    g_assert (GETIT_IS_CONTENT_HEADERS (content_headers));
    g_assert_nonnull (file_name);

    JsonObject *json_object_root;
    JsonObject *json_object_body;
    JsonNode * json_node_root;

    GError *error_writing;
    JsonGenerator *json_generator;

    json_object_root = json_object_new ();
    json_object_body = json_object_new ();
    json_node_root = json_node_new (JSON_NODE_OBJECT);

    /* Add data to json objects */
    getit_content_body_add_to_json_object (content_body, json_object_body,
                                           JSON_FORMDATA_NAME,
                                           JSON_BODY_URI_KEY,
                                           JSON_BODY_METHOD_KEY,
                                           JSON_BODY_DATA_TYPE_KEY,
                                           JSON_BODY_RAW_LANGUAGE_KEY,
                                           JSON_BODY_RAW_INPUT_KEY,
                                           JSON_FORMDATA_ENABLED_KEY,
                                           JSON_FORMDATA_KEY_KEY,
                                           JSON_FORMDATA_VALUE_KEY,
                                           JSON_FORMDATA_FILE_KEY,
                                           JSON_FORMDATA_TYPE_KEY);
    getit_content_cookies_add_to_json_object (content_cookies, json_object_root,
                                              JSON_COOKIES_NAME,
                                              JSON_COOKIES_ENABLED_KEY,
                                              JSON_COOKIES_KEY_KEY,
                                              JSON_COOKIES_VALUE_KEY);
    getit_content_headers_add_to_json_object (content_headers, json_object_root,
                                              JSON_HEADERS_NAME,
                                              JSON_HEADERS_ENABLED_KEY,
                                              JSON_HEADERS_KEY_KEY,
                                              JSON_HEADERS_VALUE_KEY);

    json_object_set_object_member (json_object_root, JSON_BODY_NAME, json_object_body);

    json_node_set_object (json_node_root, json_object_root);

    /* Save the file */
    error_writing = NULL;
    json_generator = json_generator_new ();

    json_generator_set_root (json_generator, json_node_root);
    json_generator_set_pretty (json_generator, TRUE);
    json_generator_to_file (json_generator, file_name, &error_writing);

    /* Check if an error occured writing the file */
    if (error_writing != NULL) {
        g_print ("Error saving file...\n%s\n", error_writing->message);

        g_error_free (error_writing);

        return FALSE;
    }

    return TRUE;
}

gboolean
getit_json_open_file (GetitContentBody    *content_body,
                      GetitContentCookies *content_cookies,
                      GetitContentHeaders *content_headers,
                      const gchar         *file_name)
{
    return TRUE;
}
