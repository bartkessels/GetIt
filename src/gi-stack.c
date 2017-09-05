/*
 * gi-stack.c
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

#include <glib-object.h>
#include <gtk/gtk.h>

#include "gi-content-body.h"
#include "gi-content-cookies.h"
#include "gi-content-headers.h"
#include "gi-content-response.h"
#include "gi-stack.h"

G_DEFINE_TYPE(GiStack, gi_stack, GTK_TYPE_STACK)
static void gi_stack_class_init(GiStackClass* class) {}

/**
 * gi_stack_init
 *
 * @self: Pointer to self
 *
 * Add all the content UI's to the stack
 *
 * Return value: void
 */
static void gi_stack_init(GiStack* self)
{
    // Self properties
    gtk_stack_set_transition_type(GTK_STACK(self), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);

    // Add stacks
    self->content_body = gi_content_body_new();
    self->content_cookies = gi_content_cookies_new();
    self->content_headers = gi_content_headers_new();
    self->content_response = gi_content_response_new();

    gtk_stack_add_titled(GTK_STACK(self), GTK_WIDGET(self->content_body), STACK_NAME_CONTENT_BODY, STACK_TITLE_CONTENT_BODY);
    gtk_stack_add_titled(GTK_STACK(self), GTK_WIDGET(self->content_cookies), STACK_NAME_CONTENT_COOKIES, STACK_TITLE_CONTENT_COOKIES);
    gtk_stack_add_titled(GTK_STACK(self), GTK_WIDGET(self->content_headers), STACK_NAME_CONTENT_HEADERS, STACK_TITLE_CONTENT_HEADERS);
    gtk_stack_add_titled(GTK_STACK(self), GTK_WIDGET(self->content_response), STACK_NAME_CONTENT_RESPONSE, STACK_TITLE_CONTENT_RESPONSE);
}

/**
 * gi_stack_new
 *
 * Create new instance of GiStack
 *
 * Return value: GiStack
 */
GiStack* gi_stack_new()
{
    return g_object_new(GI_TYPE_STACK, NULL);
}