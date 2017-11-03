/* getit-content-cookies.h
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

#include "getit-element-cookie.h"

G_BEGIN_DECLS

#define GETIT_TYPE_CONTENT_COOKIES (getit_content_cookies_get_type())

G_DECLARE_FINAL_TYPE (GetitContentCookies, getit_content_cookies, GETIT, CONTENT_COOKIES, GtkScrolledWindow)

/* Public function signatures */
GetitContentCookies *getit_content_cookies_new ();
void getit_content_cookies_clear (GetitContentCookies *self);
void getit_content_cookies_add_to_request (GetitContentCookies *self,
                                           SoupMessage         *soup_message,
                                           SoupURI             *uri);
void getit_content_cookies_add_to_json_object (GetitContentCookies *self,
                                               JsonObject          *json_cookies_object,
                                               const gchar         *cookies_array_name,
                                               const gchar         *enabled_key,
                                               const gchar         *key_key,
                                               const gchar         *value_key);
void getit_content_cookies_add_cookie_with_values (GetitContentCookies *self,
                                                   const gboolean       enabled,
                                                   const gchar         *key,
                                                   const gchar         *value);

G_END_DECLS
