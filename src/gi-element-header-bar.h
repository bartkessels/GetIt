/*
 * gi-element-header-bar.h
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

#ifndef GI_ELEMENT_HEADER_BAR_H
#define GI_ELEMENT_HEADER_BAR_H

#include <glib-object.h>
#include <gtk/gtk.h>

#include "gi-stack.h"

G_BEGIN_DECLS

typedef struct _GiElementHeaderBar GiElementHeaderBar;

#define GI_TYPE_ELEMENT_HEADER_BAR gi_element_header_bar_get_type()
G_DECLARE_FINAL_TYPE(GiElementHeaderBar, gi_element_header_bar, GI, ELEMENT_HEADER_BAR, GtkHeaderBar)

struct _GiElementHeaderBar {
    GtkHeaderBar parent;

    /*
        Member Variables
    */
    GtkWidget* btn_send;
    GtkWidget* btn_cancel;
    GtkWidget* btn_menu;
    GtkWidget* mi_request_open;
    GtkWidget* mi_request_save_as;
    GtkWidget* mi_request_save;
    GtkWidget* mi_request_clear;
    GtkWidget* ss_main;
    GtkWidget* sp_loading;
    GtkWidget* menu;
};

/*
    Methods
*/
GiElementHeaderBar* gi_element_header_bar_new();
void gi_element_header_bar_set_save_sensitive(GiElementHeaderBar* self, gboolean sensitive);
void gi_element_header_bar_set_stack(GiElementHeaderBar* self, GiStack* stack);
void gi_element_header_bar_set_title(GiElementHeaderBar* self, const gchar* title);
void gi_element_header_bar_set_subtitle(GiElementHeaderBar* self, const gchar* subtitle);
void gi_element_header_bar_start_loading(GiElementHeaderBar* self);
void gi_element_header_bar_stop_loading(GiElementHeaderBar* self);

G_END_DECLS

#endif /* GI_ELEMENT_HEADER_BAR_H */