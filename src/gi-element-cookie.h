/*
 * gi-element-cookie.h
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

#ifndef GI_ELEMENT_COOKIE_H
#define GI_ELEMENT_COOKIE_H

#include <glib-object.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef struct _GiElementCookie GiElementCookie;

#define GI_TYPE_ELEMENT_COOKIE gi_element_cookie_get_type()
G_DECLARE_FINAL_TYPE(GiElementCookie, gi_element_cookie, GI, ELEMENT_COOKIE, GtkGrid)

struct _GiElementCookie {
    GtkGrid parent;

    /*
        Member Variables
    */
    GtkWidget* grd_main;
    GtkWidget* cbtn_enabled;
    GtkWidget* et_key;
    GtkWidget* et_value;
    GtkWidget* btn_remove;
};

/*
    Methods
*/
GiElementCookie* gi_element_cookie_new();
gboolean gi_element_cookie_get_enabled(GiElementCookie* self);
void gi_element_cookie_destroy(GiElementCookie* self);

G_END_DECLS

#endif /* GI_ELEMENT_COOKIE_H */