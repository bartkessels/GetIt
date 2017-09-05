/*
 * gi-element-formdata.c
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

#include "gi-element-formdata.h"

G_DEFINE_TYPE(GiElementFormdata, gi_element_formdata, GTK_TYPE_GRID)
static void gi_element_formdata_class_init(GiElementFormdataClass* class) {}

/**
 * gi_element_formdata_cb_type_changed
 *
 * @caller: The GtkWidget which is calling this function
 * @user_data: Pointer to self
 *
 * Change current UI based on the selected type.
 * If the selected type is String then show a
 * EditText else if the selected type is a file
 * then show the FileChooserButton
 *
 * Return value: void
 */
static void gi_element_formdata_cb_type_changed(GtkWidget* caller, gpointer user_data)
{
    GiElementFormdata* self = GI_ELEMENT_FORMDATA(user_data);
    const gchar* data_type = gi_element_formdata_get_data_type(self);

    // Check which widgets should be shown
    if (g_str_equal(data_type, DATA_TYPE_STRING)) {
        gtk_widget_show(self->et_value);
        gtk_widget_hide(self->fcbtn_file);
    } else if (g_str_equal(data_type, DATA_TYPE_FILE)) {
        gtk_widget_hide(self->et_value);
        gtk_widget_show(self->fcbtn_file);
    }
}

/**
 * gi_element_formdata_init
 *
 * @self: Pointer to self
 *
 * Build the UI from the .ui file in the resources
 *
 * Return value: void
 */
static void gi_element_formdata_init(GiElementFormdata* self)
{
    // Load elements from resource
    GtkBuilder* builder = gtk_builder_new_from_resource("/net/bartkessels/getit/element-formdata.ui");

    self->grd_main = GTK_WIDGET(gtk_builder_get_object(builder, "grd_main"));
    self->cbtn_enabled = GTK_WIDGET(gtk_builder_get_object(builder, "cbtn_enabled"));
    self->et_key = GTK_WIDGET(gtk_builder_get_object(builder, "et_key"));
    self->et_value = GTK_WIDGET(gtk_builder_get_object(builder, "et_value"));
    self->fcbtn_file = GTK_WIDGET(gtk_builder_get_object(builder, "fcbtn_file"));
    self->cb_type = GTK_WIDGET(gtk_builder_get_object(builder, "cb_type"));
    self->btn_remove = GTK_WIDGET(gtk_builder_get_object(builder, "btn_remove"));

    // Connect signals
    g_signal_connect(self->cb_type, "changed", G_CALLBACK(gi_element_formdata_cb_type_changed), self);

    // Show widgets
    gtk_container_add(GTK_CONTAINER(self), self->grd_main);
    gtk_widget_show_all(GTK_WIDGET(self));
    gi_element_formdata_cb_type_changed(self->cb_type, self);

    g_object_unref(builder);
}

/**
 * gi_element_formdata_new
 *
 * Create new instance of GiElementFormdata
 *
 * Return value: GiElementFormdata
 */
GiElementFormdata* gi_element_formdata_new()
{
    return g_object_new(GI_TYPE_ELEMENT_FORMDATA, NULL);
}

/**
 * gi_element_formdata_get_enabled
 *
 * @self: Pointer to self
 *
 * Check if the cbtn_enabled toggle button is toggled or not
 *
 * Return value: gboolean
 */
gboolean gi_element_formdata_get_enabled(GiElementFormdata* self)
{
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(self->cbtn_enabled)) && strlen(gtk_entry_get_text(GTK_ENTRY(self->et_key))) > 0;
}

/**
 * gi_element_formdata_get_data_type
 *
 * @self: Pointer to self
 *
 * Get the selected data type (String or File)
 *
 * Return value: const gchar
 */
const gchar* gi_element_formdata_get_data_type(GiElementFormdata* self)
{
    return gtk_combo_box_get_active_id(GTK_COMBO_BOX(self->cb_type));
}