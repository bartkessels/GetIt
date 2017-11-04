/* getit-element-formdata.c
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

#include "getit-element-formdata.h"

struct _GetitElementFormdata {
    GtkGrid parent_instance;

    /* Template widgets */
    GtkCheckButton *cbtn_enabled;
    GtkEntry *et_key;
    GtkEntry *et_value;
    GtkFileChooserButton *fcbtn_file;
    GtkComboBoxText *cb_type;
    GtkButton *btn_remove;
};

G_DEFINE_TYPE (GetitElementFormdata, getit_element_formdata, GTK_TYPE_GRID)

/*
 * =============================================================================
 * Signatures
 *
 */
static void getit_element_formdata_class_init (GetitElementFormdataClass *klass);
static void getit_element_formdata_init (GetitElementFormdata *self);

/* Callback signatures */
static void getit_element_formdata_cb_combobox_datatype_changed (GtkWidget *caller,
                                                                 gpointer   user_data);
static void getit_element_formdata_cb_btn_remove_clicked (GtkWidget *caller,
                                                          gpointer   user_data);

/*
 * =============================================================================
 * Public function implementations
 *
 */
GetitElementFormdata *
getit_element_formdata_new ()
{
    GetitElementFormdata *formdata;

    formdata = g_object_new (GETIT_TYPE_ELEMENT_FORMDATA, NULL);

    return formdata;
}

GetitElementFormdata *
getit_element_formdata_new_with_values (const gboolean  enabled,
                                        const gchar    *key,
                                        const gchar    *value,
                                        const gchar    *file,
                                        const gint      type)
{
    GetitElementFormdata *formdata;

    formdata = getit_element_formdata_new ();

    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (formdata->cbtn_enabled), enabled);
    gtk_entry_set_text (formdata->et_key, key);
    gtk_entry_set_text (formdata->et_value, value);
    gtk_combo_box_set_active (GTK_COMBO_BOX (formdata->cb_type), type);

    /* Only load the file into the filechooser button
     * if it's not null
     */
    if (file != NULL) {
        gtk_file_chooser_set_filename (GTK_FILE_CHOOSER (formdata->fcbtn_file), file);
    }

    return formdata;
}

gboolean getit_element_formdata_get_enabled (GetitElementFormdata *self)
{
    g_assert (GETIT_IS_ELEMENT_FORMDATA (self));

    gboolean is_enabled;

    is_enabled = (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (self->cbtn_enabled)) &&
                  gtk_entry_get_text_length (self->et_key) > 0);

    return is_enabled;
}

const gchar *getit_element_formdata_get_datatype (GetitElementFormdata *self)
{
    g_assert (GETIT_IS_ELEMENT_FORMDATA (self));

    const gchar *datatype;

    datatype = gtk_combo_box_get_active_id (GTK_COMBO_BOX (self->cb_type));

    return datatype;
}

gint
getit_element_formdata_get_datatype_int (GetitElementFormdata *self)
{
    g_assert (GETIT_IS_ELEMENT_FORMDATA (self));

    gint datatype_int;

    datatype_int = gtk_combo_box_get_active (GTK_COMBO_BOX (self->cb_type));

    return datatype_int;
}

const gchar *getit_element_formdata_get_key (GetitElementFormdata *self)
{
    g_assert (GETIT_IS_ELEMENT_FORMDATA (self));

    const gchar *key;

    key = gtk_entry_get_text (self->et_key);

    return key;
}

const gchar *getit_element_formdata_get_value (GetitElementFormdata *self)
{
    g_assert (GETIT_IS_ELEMENT_FORMDATA (self));

    const gchar *value;

    value = gtk_entry_get_text (self->et_value);

    return value;
}

const gchar *getit_element_formdata_get_filename (GetitElementFormdata *self)
{
    g_assert (GETIT_IS_ELEMENT_FORMDATA (self));

    const gchar *filename;

    filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (self->fcbtn_file));

    return filename;
}

/*
 * =============================================================================
 * Private function implementations
 *
 */
static void
getit_element_formdata_class_init (GetitElementFormdataClass *klass)
{
    GtkWidgetClass *widget_class;

    widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/net/bartkessels/getit/element-formdata.ui");
    gtk_widget_class_bind_template_child (widget_class, GetitElementFormdata, cbtn_enabled);
    gtk_widget_class_bind_template_child (widget_class, GetitElementFormdata, et_key);
    gtk_widget_class_bind_template_child (widget_class, GetitElementFormdata, et_value);
    gtk_widget_class_bind_template_child (widget_class, GetitElementFormdata, btn_remove);
    gtk_widget_class_bind_template_child (widget_class, GetitElementFormdata, fcbtn_file);
    gtk_widget_class_bind_template_child (widget_class, GetitElementFormdata, cb_type);
}

static void
getit_element_formdata_init (GetitElementFormdata *self)
{
    g_assert (GETIT_IS_ELEMENT_FORMDATA (self));
    g_assert (GTK_IS_WIDGET (self));

    gtk_widget_init_template (GTK_WIDGET (self));

    g_signal_connect (self->cb_type, "changed",
                      G_CALLBACK (getit_element_formdata_cb_combobox_datatype_changed), self);
    g_signal_connect (self->btn_remove, "clicked",
                      G_CALLBACK (getit_element_formdata_cb_btn_remove_clicked), self);
}

/*
 * =============================================================================
 * Private callback implementations
 *
 */
static void
getit_element_formdata_cb_combobox_datatype_changed (GtkWidget *caller,
                                            gpointer   user_data)
{
    g_assert (GTK_IS_COMBO_BOX_TEXT (caller));
    g_assert (GETIT_IS_ELEMENT_FORMDATA (user_data));

    GetitElementFormdata *self;
    const gchar *datatype;

    self = GETIT_ELEMENT_FORMDATA(user_data);
    datatype = gtk_combo_box_get_active_id (GTK_COMBO_BOX (self->cb_type));

    /* Show / hide widgets based on selection */
    if (g_str_equal (datatype, DATATYPE_STRING)) {
        gtk_widget_show (GTK_WIDGET (self->et_value));
        gtk_widget_hide (GTK_WIDGET (self->fcbtn_file));
    } else if (g_str_equal (datatype, DATATYPE_FILE)) {
        gtk_widget_hide (GTK_WIDGET (self->et_value));
        gtk_widget_show (GTK_WIDGET (self->fcbtn_file));
    }
}

static void
getit_element_formdata_cb_btn_remove_clicked (GtkWidget *caller,
                                              gpointer   user_data)
{
    g_assert (GTK_IS_BUTTON (caller));
    g_assert (G_IS_OBJECT (user_data));

    g_object_run_dispose (user_data);
}
