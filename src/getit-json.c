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
                                           JSON_BODY_VALIDATE_X509,
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
getit_json_open_file (GetitContentBody     *content_body,
                      GetitContentCookies  *content_cookies,
                      GetitContentHeaders  *content_headers,
                      GetitContentResponse *content_response,
                      const gchar          *file_name)
{
    g_assert (GETIT_IS_CONTENT_BODY (content_body));
    g_assert (GETIT_IS_CONTENT_COOKIES (content_cookies));
    g_assert (GETIT_IS_CONTENT_HEADERS (content_headers));
    g_assert_nonnull (file_name);

    JsonParser *json_parser;
    GError *error_reading = NULL;
    JsonNode *json_node_root;
    JsonObject *json_object_root;

    JsonObject *json_object_body;
    JsonArray *json_array_body_formdata;
    gint body_method;
    gboolean body_validate_x509;
    const gchar *body_uri;
    const gchar *body_data_type;
    gint body_raw_language;
    const gchar *body_raw_input;

    JsonArray *json_array_cookies;
    JsonArray *json_array_headers;

    json_parser = json_parser_new ();
    json_parser_load_from_file (json_parser, file_name, &error_reading);
    json_node_root = json_parser_get_root (json_parser);
    json_object_root = json_node_get_object (json_node_root);

    if (error_reading != NULL) {
        g_print ("Error reading file...\n%s\n", error_reading->message);

        g_error_free (error_reading);

        return FALSE;
    }

    /* Clear current request */
    getit_content_body_clear (content_body);
    getit_content_cookies_clear (content_cookies);
    getit_content_headers_clear (content_headers);
    getit_content_response_show_default (content_response);

    /* Body */
    json_object_body = json_object_get_object_member (json_object_root, JSON_BODY_NAME);
    json_array_body_formdata = json_object_get_array_member (json_object_body, JSON_FORMDATA_NAME);

    body_method = json_object_get_int_member (json_object_body, JSON_BODY_METHOD_KEY);
    body_validate_x509 = json_object_get_boolean_member (json_object_body, JSON_BODY_VALIDATE_X509);
    body_uri = json_object_get_string_member (json_object_body, JSON_BODY_URI_KEY);
    body_data_type = json_object_get_string_member (json_object_body, JSON_BODY_DATA_TYPE_KEY);
    body_raw_language = json_object_get_int_member (json_object_body, JSON_BODY_RAW_LANGUAGE_KEY);
    body_raw_input = json_object_get_string_member (json_object_body, JSON_BODY_RAW_INPUT_KEY);

    getit_content_body_set_values (content_body,
                                   body_method,
                                   body_validate_x509,
                                   body_uri,
                                   body_data_type,
                                   body_raw_language,
                                   body_raw_input);

    for (gint json_array_body_formdata_index = 0; json_array_body_formdata_index < json_array_get_length (json_array_body_formdata); json_array_body_formdata_index++) {
        JsonObject *json_object_formdata;

        gboolean enabled;
        const gchar *key;
        const gchar *value;
        const gchar *file;
        gint type;

        json_object_formdata = json_array_get_object_element (json_array_body_formdata, json_array_body_formdata_index);
        enabled = json_object_get_boolean_member (json_object_formdata, JSON_FORMDATA_ENABLED_KEY);
        key = json_object_get_string_member (json_object_formdata, JSON_FORMDATA_KEY_KEY);
        value = json_object_get_string_member (json_object_formdata, JSON_FORMDATA_VALUE_KEY);
        file = json_object_get_string_member (json_object_formdata, JSON_FORMDATA_FILE_KEY);
        type = json_object_get_int_member (json_object_formdata, JSON_FORMDATA_TYPE_KEY);

        getit_content_body_add_formdata_with_values (content_body,
                                                     enabled,
                                                     key,
                                                     value,
                                                     file,
                                                     type);
    }

    /* Cookies */
    json_array_cookies = json_object_get_array_member (json_object_root, JSON_COOKIES_NAME);

    for (gint json_array_cookies_index = 0; json_array_cookies_index < json_array_get_length (json_array_cookies); json_array_cookies_index++) {
        JsonObject *json_object_cookie;

        gboolean enabled;
        const gchar *key;
        const gchar *value;

        json_object_cookie = json_array_get_object_element (json_array_cookies, json_array_cookies_index);
        enabled = json_object_get_boolean_member (json_object_cookie, JSON_COOKIES_ENABLED_KEY);
        key = json_object_get_string_member (json_object_cookie, JSON_COOKIES_KEY_KEY);
        value = json_object_get_string_member (json_object_cookie, JSON_COOKIES_VALUE_KEY);

        getit_content_cookies_add_cookie_with_values (content_cookies,
                                                      enabled,
                                                      key,
                                                      value);
    }

    /* Headers */
    json_array_headers = json_object_get_array_member (json_object_root, JSON_HEADERS_NAME);

    for (gint json_array_headers_index = 0; json_array_headers_index < json_array_get_length (json_array_headers); json_array_headers_index++) {
        JsonObject *json_object_header;

        gboolean enabled;
        const gchar *key;
        const gchar *value;

        json_object_header = json_array_get_object_element (json_array_headers, json_array_headers_index);
        enabled = json_object_get_boolean_member (json_object_header, JSON_HEADERS_ENABLED_KEY);
        key = json_object_get_string_member (json_object_header, JSON_HEADERS_KEY_KEY);
        value = json_object_get_string_member (json_object_header, JSON_HEADERS_VALUE_KEY);

        getit_content_headers_add_header_with_values (content_headers,
                                                      enabled,
                                                      key,
                                                      value);
    }

    return TRUE;
}
