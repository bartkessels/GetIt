/*
 * gi-stack.h
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

#ifndef GI_STACK_H
#define GI_STACK_H

#include <glib-object.h>
#include <gtk/gtk.h>

#include "gi-content-body.h"
#include "gi-content-cookies.h"
#include "gi-content-headers.h"
#include "gi-content-response.h"

#define STACK_NAME_CONTENT_BODY "content_body"
#define STACK_NAME_CONTENT_COOKIES "content_cookies"
#define STACK_NAME_CONTENT_HEADERS "content_headers"
#define STACK_NAME_CONTENT_RESPONSE "content_response"

#define STACK_TITLE_CONTENT_BODY "Body"
#define STACK_TITLE_CONTENT_COOKIES "Cookies"
#define STACK_TITLE_CONTENT_HEADERS "Headers"
#define STACK_TITLE_CONTENT_RESPONSE "Response"

G_BEGIN_DECLS

typedef struct _GiStack GiStack;

#define GI_TYPE_STACK gi_stack_get_type()
G_DECLARE_FINAL_TYPE(GiStack, gi_stack, GI, STACK, GtkStack)

struct _GiStack {
    GtkStack parent;

    /*
        Member Variables
    */
    GiContentBody* content_body;
    GiContentCookies* content_cookies;
    GiContentHeaders* content_headers;
    GiContentResponse* content_response;
};

/*
    Methods
*/
GiStack* gi_stack_new();

G_END_DECLS

#endif /* GI_STACK_H */