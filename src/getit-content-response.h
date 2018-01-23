/* getit-content-response.h
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

#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>
#include <libsoup/soup.h>
#include <string.h>
#include <webkit2/webkit2.h>
#include <json-glib/json-glib.h>

#include "getit-messages.h"

G_BEGIN_DECLS

#define GETIT_TYPE_CONTENT_RESPONSE (getit_content_response_get_type())

G_DECLARE_FINAL_TYPE (GetitContentResponse, getit_content_response, GETIT, CONTENT_RESPONSE, GtkScrolledWindow)

/* Public function signatures */
GetitContentResponse *getit_content_response_new ();
void getit_content_response_show_default (GetitContentResponse *self);
void getit_content_response_show_sending (GetitContentResponse *self);
void getit_content_response_show_response (GetitContentResponse *self,
                                           GtkSourceLanguage    *language,
                                           SoupMessageHeaders   *headers,
                                           const gchar          *body,
                                           guint                 status_code,
                                           const gchar          *status_message,
                                           const gchar          *uri);
void getit_content_response_show_error (GetitContentResponse *self,
                                        const gchar          *error_message);
void getit_content_response_show_timeout (GetitContentResponse *self);

G_END_DECLS
