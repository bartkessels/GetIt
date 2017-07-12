/*
 * gi-element-header-bar.c
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

#include "gi-element-header-bar.h"
#include "gi-stack.h"

G_DEFINE_TYPE(GiElementHeaderBar, gi_element_header_bar, GTK_TYPE_HEADER_BAR)

static void gi_element_header_bar_init(GiElementHeaderBar* self)
{
    // Initialize widgets
    self->ss_main = gtk_stack_switcher_new();
    self->btn_send = gtk_button_new_with_label("Send");
    self->btn_cancel = gtk_button_new_with_label("Cancel");
    self->sp_loading = gtk_spinner_new();
    self->menu = gtk_menu_new();
    self->btn_menu = gtk_menu_button_new();

    // Create menu entries
    self->mi_request_open = gtk_menu_item_new_with_label("Open");
    self->mi_request_save_as = gtk_menu_item_new_with_label("Save As");
    self->mi_request_save = gtk_menu_item_new_with_label("Save");
    self->mi_request_clear = gtk_menu_item_new_with_label("Clear");

    GtkWidget* separator = gtk_separator_menu_item_new();

    // Add menu entries to menu
    gtk_menu_shell_append(GTK_MENU_SHELL(self->menu), self->mi_request_open);
    gtk_menu_shell_append(GTK_MENU_SHELL(self->menu), self->mi_request_save_as);
    gtk_menu_shell_append(GTK_MENU_SHELL(self->menu), self->mi_request_save);
    gtk_menu_shell_append(GTK_MENU_SHELL(self->menu), separator);
    gtk_menu_shell_append(GTK_MENU_SHELL(self->menu), self->mi_request_clear);

    // Add shortcuts to menu
    GtkWidget* bin_mi_request_open = gtk_bin_get_child(GTK_BIN(self->mi_request_open));
    GtkWidget* bin_mi_request_save_as = gtk_bin_get_child(GTK_BIN(self->mi_request_save_as));
    GtkWidget* bin_mi_request_save = gtk_bin_get_child(GTK_BIN(self->mi_request_save));

    gtk_accel_label_set_accel(GTK_ACCEL_LABEL(bin_mi_request_open), GDK_KEY_o, GDK_CONTROL_MASK);
    gtk_accel_label_set_accel(GTK_ACCEL_LABEL(bin_mi_request_save_as), GDK_KEY_s, GDK_MOD1_MASK | GDK_CONTROL_MASK);
    gtk_accel_label_set_accel(GTK_ACCEL_LABEL(bin_mi_request_save), GDK_KEY_s, GDK_CONTROL_MASK);

    // Menu item save properties
    gtk_widget_set_sensitive(self->mi_request_save, FALSE);

    // Button send properties
    GtkStyleContext* btn_send_style_context = gtk_widget_get_style_context(self->btn_send);
    gtk_widget_set_tooltip_text(GTK_WIDGET(self->btn_send), "Send Request (ctrl + enter)");
    gtk_style_context_add_class(btn_send_style_context, "suggested-action");

    // Button cancel properties
    GtkStyleContext* btn_cancel_style_context = gtk_widget_get_style_context(self->btn_cancel);
    gtk_widget_set_tooltip_text(GTK_WIDGET(self->btn_cancel), "Cancel Sending Request (esc)");
    gtk_style_context_add_class(btn_cancel_style_context, "destructive-action");

    // Button menu
    gtk_menu_button_set_popup(GTK_MENU_BUTTON(self->btn_menu), self->menu);
    gtk_menu_button_set_direction(GTK_MENU_BUTTON(self->btn_menu), GTK_ARROW_NONE);

    // Add widgets to self
    gtk_header_bar_pack_start(GTK_HEADER_BAR(self), self->ss_main);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(self), self->btn_menu);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(self), self->btn_send);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(self), self->btn_cancel);
    gtk_header_bar_pack_end(GTK_HEADER_BAR(self), self->sp_loading);

    // Headerbar properties
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(self), TRUE);

    // Show widgets
    gtk_widget_show_all(self->menu);
}

static void gi_element_header_bar_class_init(GiElementHeaderBarClass* class)
{
    GtkHeaderBarClass* parent_class = GTK_HEADER_BAR_CLASS(class);
}

GiElementHeaderBar* gi_element_header_bar_new()
{
    return g_object_new(GI_TYPE_ELEMENT_HEADER_BAR, NULL);
}

void gi_element_header_bar_set_save_sensitive(GiElementHeaderBar* self, gboolean sensitive)
{
    gtk_widget_set_sensitive(self->mi_request_save, sensitive);
}

void gi_element_header_bar_set_stack(GiElementHeaderBar* self, GiStack* stack)
{
    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(self->ss_main), GTK_STACK(stack));
}

void gi_element_header_bar_set_title(GiElementHeaderBar* self, const gchar* title)
{
    gtk_header_bar_set_title(GTK_HEADER_BAR(self), title);
}

void gi_element_header_bar_set_subtitle(GiElementHeaderBar* self, const gchar* subtitle)
{
    gtk_header_bar_set_subtitle(GTK_HEADER_BAR(self), subtitle);
}

void gi_element_header_bar_start_loading(GiElementHeaderBar* self)
{
    gtk_spinner_start(GTK_SPINNER(self->sp_loading));
    gtk_widget_hide(self->btn_send);
    gtk_widget_show(self->btn_cancel);
}

void gi_element_header_bar_stop_loading(GiElementHeaderBar* self)
{
    gtk_spinner_stop(GTK_SPINNER(self->sp_loading));
    gtk_widget_show(self->btn_send);
    gtk_widget_hide(self->btn_cancel);
}