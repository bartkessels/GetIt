/*
 * gi-element-cookie.c
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
#include <string.h>

#include "gi-element-cookie.h"

G_DEFINE_TYPE(GiElementCookie, gi_element_cookie, GTK_TYPE_GRID)
static void gi_element_cookie_class_init(GiElementCookieClass* class) {}

/**
 * gi_element_cookie_init
 *
 * @self: Pointer to self
 *
 * Build the UI from the .ui file in the resources
 *
 * Return value: void
 */
static void gi_element_cookie_init(GiElementCookie* self)
{
    // Load elements from resource
    GtkBuilder* builder = gtk_builder_new_from_resource("/net/bartkessels/getit/element-cookie.ui");

    self->grd_main = GTK_WIDGET(gtk_builder_get_object(builder, "grd_main"));
    self->cbtn_enabled = GTK_WIDGET(gtk_builder_get_object(builder, "cbtn_enabled"));
    self->et_key = GTK_WIDGET(gtk_builder_get_object(builder, "et_key"));
    self->et_value = GTK_WIDGET(gtk_builder_get_object(builder, "et_value"));
    self->btn_remove = GTK_WIDGET(gtk_builder_get_object(builder, "btn_remove"));

    // Show widgets
    gtk_container_add(GTK_CONTAINER(self), self->grd_main);
    gtk_widget_show_all(GTK_WIDGET(self));

    g_object_unref(builder);
}

/**
 * gi_element_cookie_new
 *
 * Create new instance of GiElementCookie
 *
 * Return value: GiElementCookie
 */
GiElementCookie* gi_element_cookie_new()
{
    return g_object_new(GI_TYPE_ELEMENT_COOKIE, NULL);
}

/**
 * gi_element_get_enabled
 *
 * @self: Pointer to self
 *
 * Check if the cbtn_enabled toggle button is toggled or not
 *
 * Return value: gboolean
 */
gboolean gi_element_cookie_get_enabled(GiElementCookie* self)
{
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(self->cbtn_enabled)) && strlen(gtk_entry_get_text(GTK_ENTRY(self->et_key))) > 0;
}