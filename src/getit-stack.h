/* getit-stack.h
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

#include "getit-content-body.h"
#include "getit-content-cookies.h"
#include "getit-content-headers.h"
#include "getit-content-response.h"

G_BEGIN_DECLS

#define GETIT_TYPE_STACK (getit_stack_get_type())

G_DECLARE_FINAL_TYPE (GetitStack, getit_stack, GETIT, STACK, GtkStack)

/* Stack information */
#define STACK_NAME_CONTENT_BODY "content_body"
#define STACK_NAME_CONTENT_COOKIES "content_cookies"
#define STACK_NAME_CONTENT_HEADERS "content_headers"
#define STACK_NAME_CONTENT_RESPONSE "content_response"

#define STACK_TITLE_CONTENT_BODY "Body"
#define STACK_TITLE_CONTENT_COOKIES "Cookies"
#define STACK_TITLE_CONTENT_HEADERS "Headers"
#define STACK_TITLE_CONTENT_RESPONSE "Response"

/* Public function signatures */
GetitStack *getit_stack_new ();
GetitContentBody *getit_stack_get_content_body (GetitStack *self);
GetitContentCookies *getit_stack_get_content_cookies (GetitStack *self);
GetitContentHeaders *getit_stack_get_content_headers (GetitStack *self);
GetitContentResponse *getit_stack_get_content_response (GetitStack *self);

G_END_DECLS
