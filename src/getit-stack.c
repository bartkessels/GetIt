/* getit-stack.c
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

#include "getit-stack.h"

typedef struct _GetitStackPrivate GetitStackPrivate;

struct _GetitStack {
    GtkStack parent_instance;

    /* Member variables */
    GetitContentBody *content_body;
    GetitContentCookies *content_cookies;
    GetitContentHeaders *content_headers;
    GetitContentResponse *content_response;
};

G_DEFINE_TYPE (GetitStack, getit_stack, GTK_TYPE_STACK)

/*
 * =============================================================================
 * Signatures
 *
 */
static void getit_stack_class_init (GetitStackClass *klass);
static void getit_stack_init (GetitStack *self);

/*
 * =============================================================================
 * Public function implementations
 *
 */
GetitStack *
getit_stack_new()
{
    GetitStack *getit_stack;

    getit_stack = g_object_new (GETIT_TYPE_STACK, NULL);

    return getit_stack;
}

GetitContentBody *
getit_stack_get_content_body (GetitStack *self)
{
    g_assert (GETIT_IS_STACK (self));
    g_assert_nonnull (self->content_body);

    return self->content_body;
}

GetitContentCookies *
getit_stack_get_content_cookies (GetitStack *self)
{
    g_assert (GETIT_IS_STACK (self));
    g_assert_nonnull (self->content_cookies);

    return self->content_cookies;
}

GetitContentHeaders *
getit_stack_get_content_headers (GetitStack *self)
{
    g_assert (GETIT_IS_STACK (self));
    g_assert_nonnull (self->content_headers);

    return self->content_headers;
}

GetitContentResponse *
getit_stack_get_content_response (GetitStack *self)
{
    g_assert (GETIT_IS_STACK (self));
    g_assert_nonnull (self->content_response);

    return self->content_response;
}

/*
 * =============================================================================
 * Private function implementations
 *
 */
static void
getit_stack_class_init (GetitStackClass *klass)
{

}

static void
getit_stack_init (GetitStack *self)
{
    g_assert (GETIT_IS_STACK (self));
    g_assert (GTK_IS_STACK (self));

    /* Get content stacks */
    self->content_body = getit_content_body_new ();
    self->content_cookies = getit_content_cookies_new ();
    self->content_headers = getit_content_headers_new ();
    self->content_response = getit_content_response_new ();

    /* Add titled stacks */
    gtk_stack_add_titled (GTK_STACK (self), GTK_WIDGET (self->content_body), STACK_NAME_CONTENT_BODY, STACK_TITLE_CONTENT_BODY);
    gtk_stack_add_titled (GTK_STACK (self), GTK_WIDGET (self->content_cookies), STACK_NAME_CONTENT_COOKIES, STACK_TITLE_CONTENT_COOKIES);
    gtk_stack_add_titled (GTK_STACK (self), GTK_WIDGET (self->content_headers), STACK_NAME_CONTENT_HEADERS, STACK_TITLE_CONTENT_HEADERS);
    gtk_stack_add_titled (GTK_STACK (self), GTK_WIDGET (self->content_response), STACK_NAME_CONTENT_RESPONSE, STACK_TITLE_CONTENT_RESPONSE);

    /* Set properties for stack */
    gtk_stack_set_transition_type (GTK_STACK(self), GTK_STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
}
