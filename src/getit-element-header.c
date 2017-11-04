/* getit-element-header.c
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

#include "getit-element-header.h"

struct _GetitElementHeader {
    GtkGrid parent_instance;

    /* Template widgets */
    GtkCheckButton *cbtn_enabled;
    GtkEntry *et_key;
    GtkEntry *et_value;
    GtkButton *btn_remove;
};

G_DEFINE_TYPE (GetitElementHeader, getit_element_header, GTK_TYPE_GRID)

/*
 * =============================================================================
 * Signatures
 *
 */
static void getit_element_header_class_init (GetitElementHeaderClass *klass);
static void getit_element_header_init (GetitElementHeader *self);

/* Callback functions */
static void getit_element_header_cb_btn_remove_clicked (GtkWidget *caller,
                                                        gpointer   user_data);

/*
 * =============================================================================
 * Public function implementations
 *
 */
GetitElementHeader *
getit_element_header_new ()
{
    GetitElementHeader *header;

    header = g_object_new (GETIT_TYPE_ELEMENT_HEADER, NULL);

    return header;
}

GetitElementHeader *
getit_element_header_new_with_values (const gboolean  enabled,
                                      const gchar    *key,
                                      const gchar    *value)
{
    GetitElementHeader *header;

    header = getit_element_header_new ();

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (header->cbtn_enabled), enabled);
    gtk_entry_set_text (header->et_key, key);
    gtk_entry_set_text (header->et_value, value);

    return header;
}

const gboolean
getit_element_header_get_enabled (GetitElementHeader *self)
{
    g_assert (GETIT_IS_ELEMENT_HEADER (self));

    gboolean is_enabled;

    is_enabled = (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (self->cbtn_enabled)) &&
                  gtk_entry_get_text_length (self->et_key) > 0);

    return is_enabled;
}

const gchar *
getit_element_header_get_key (GetitElementHeader *self)
{
    g_assert (GETIT_IS_ELEMENT_HEADER (self));

    const gchar *key;

    key = gtk_entry_get_text (self->et_key);

    return key;
}

const gchar *
getit_element_header_get_value (GetitElementHeader *self)
{
    g_assert (GETIT_IS_ELEMENT_HEADER (self));

    const gchar *value;

    value = gtk_entry_get_text (self->et_value);

    return value;
}

/*
 * =============================================================================
 * Private function implementations
 *
 */
static void
getit_element_header_class_init (GetitElementHeaderClass *klass)
{
    GtkWidgetClass *widget_class;

    widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/net/bartkessels/getit/element-header.ui");
    gtk_widget_class_bind_template_child (widget_class, GetitElementHeader, cbtn_enabled);
    gtk_widget_class_bind_template_child (widget_class, GetitElementHeader, et_key);
    gtk_widget_class_bind_template_child (widget_class, GetitElementHeader, et_value);
    gtk_widget_class_bind_template_child (widget_class, GetitElementHeader, btn_remove);
}

static void
getit_element_header_init (GetitElementHeader *self)
{
    g_assert (GETIT_IS_ELEMENT_HEADER (self));
    g_assert (GTK_IS_WIDGET (self));

    gtk_widget_init_template (GTK_WIDGET (self));

    g_signal_connect (self->btn_remove, "clicked",
                      G_CALLBACK (getit_element_header_cb_btn_remove_clicked), self);
}

/*
 * =============================================================================
 * Private callback implementations
 *
 */
static void
getit_element_header_cb_btn_remove_clicked (GtkWidget *caller,
                                            gpointer   user_data)
{
    g_assert (GTK_IS_BUTTON (caller));
    g_assert (G_IS_OBJECT (user_data));

    g_object_run_dispose (G_OBJECT (user_data));
}
