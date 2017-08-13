/*
 * gi-application.c
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

#include <gdk/gdk.h>
#include <glib-object.h>
#include <gtk/gtk.h>

#include "gi-application.h"
#include "gi-content-body.h"
#include "gi-element-cookie.h"
#include "gi-element-formdata.h"
#include "gi-element-header.h"
#include "gi-json.h"
#include "gi-window-main.h"

struct _GiApplication {
    GtkApplication parent;

    /*
        Member Variables
    */
    GiWindowMain* window_main;
    const GFile* file;
};

G_DEFINE_TYPE(GiApplication, gi_application, GTK_TYPE_APPLICATION)

static void gi_application_mi_clear_activated(GtkWidget* caller, gpointer user_data);

static GtkFileFilter* gi_application_get_file_filter()
{
    GtkFileFilter* filter = gtk_file_filter_new();
    gtk_file_filter_add_mime_type(filter, "text/plain");
    gtk_file_filter_add_pattern(filter, "*.getit");
    gtk_file_filter_set_name(filter, "GetIt Request File");

    return filter;
}

static void gi_application_mi_save_as_activated(GtkWidget* caller, gpointer user_data)
{
    GiApplication* self = GI_APPLICATION(user_data);

    // Display save file dialog
    GtkWidget* file_chooser = gtk_file_chooser_dialog_new("Save request", GTK_WINDOW(self->window_main), GTK_FILE_CHOOSER_ACTION_SAVE, "Cancel", GTK_RESPONSE_CANCEL, "Save", GTK_RESPONSE_ACCEPT, NULL);
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(file_chooser), gi_application_get_file_filter());

    // Set file chooser dialog to current file if there is one
    if (self->file != NULL) {
        const gchar* filename = g_file_get_path(self->file);
        gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(file_chooser), filename);
    }

    gint result = gtk_dialog_run(GTK_DIALOG(file_chooser));

    if (result != GTK_RESPONSE_ACCEPT) {
        gtk_widget_destroy(file_chooser);

        return;
    }

    const gchar* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser));
    gtk_widget_destroy(file_chooser);
    gi_element_header_bar_set_save_sensitive(self->window_main->header_bar, TRUE);

    // Check if extension is added
    if (!g_str_has_suffix(filename, FILE_EXTENSION)) {
        filename = g_strconcat(filename, FILE_EXTENSION, NULL);
    }

    if (gi_json_save_file(self->window_main, filename)) {
        const gchar* file_label = g_strconcat("File: ", filename, NULL);
        gtk_label_set_text(GTK_LABEL(self->window_main->lbl_file), file_label);

        self->file = g_file_new_for_uri(filename);
    }
}

static void gi_application_mi_save_activated(GtkWidget* caller, gpointer user_data)
{
    GiApplication* self = GI_APPLICATION(user_data);

    if (self->file == NULL) {
        gi_application_mi_save_as_activated(caller, user_data);

        return;
    }

    const gchar* filename = g_file_get_path(self->file);
    gi_json_save_file(self, filename);
}

static void gi_application_mi_open_activated(GtkWidget* caller, gpointer user_data)
{
    GiApplication* self = GI_APPLICATION(user_data);

    // Display open file dialog
    GtkWidget* file_chooser = gtk_file_chooser_dialog_new("Open Request", GTK_WINDOW(self->window_main), GTK_FILE_CHOOSER_ACTION_OPEN, "Cancel", GTK_RESPONSE_CANCEL, "Open", GTK_RESPONSE_ACCEPT, NULL);
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(file_chooser), gi_application_get_file_filter());

    // Set file chooser dialog to current file if there is one
    if (self->file != NULL) {
        const gchar* filename = g_file_get_path(self->file);
        gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(file_chooser), filename);
    }

    // Check if user didn't press cancel
    gint result = gtk_dialog_run(GTK_DIALOG(file_chooser));
    if (result != GTK_RESPONSE_ACCEPT) {
        gtk_widget_destroy(file_chooser);

        return;
    }


    // Clear current request
    gi_application_mi_clear_activated(caller, user_data);

    const gchar* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser));
    gtk_widget_destroy(file_chooser);

    if (gi_json_open_file(self->window_main, filename)) {
        gi_element_header_bar_set_save_sensitive(self->window_main->header_bar, TRUE);

        // Change file_label
        const gchar* file_label = g_strconcat("File: ", filename, NULL);
        gtk_label_set_text(GTK_LABEL(self->window_main->lbl_file), file_label);

        self->file = g_file_new_for_path(filename);
    }
}

static void gi_application_mi_clear_activated(GtkWidget* caller, gpointer user_data)
{
    GiApplication* self = GI_APPLICATION(user_data);

    // Body
    gtk_combo_box_set_active(GTK_COMBO_BOX(self->window_main->stack->content_body->cb_method), 0);
    gtk_entry_set_text(GTK_ENTRY(self->window_main->stack->content_body->et_uri), "");
    gtk_stack_set_visible_child_name(self->window_main->stack->content_body->stack_data, BODY_TYPE_FORMDATA);
    gtk_combo_box_set_active(GTK_COMBO_BOX(self->window_main->stack->content_body->cb_data_raw_syntax), 0);
    gi_content_body_set_data_raw(self->window_main->stack->content_body, "");

    while (g_slist_length(self->window_main->stack->content_body->list_formdata) > 0) {
        GiElementFormdata* formdata = GI_ELEMENT_FORMDATA(g_slist_nth_data(self->window_main->stack->content_body->list_formdata, 0));
        gtk_button_clicked(GTK_BUTTON(formdata->btn_remove));
    }

    // Cookies
    while (g_slist_length(self->window_main->stack->content_cookies->list_cookies) > 0) {
        GiElementCookie* cookie = GI_ELEMENT_COOKIE(g_slist_nth_data(self->window_main->stack->content_cookies->list_cookies, 0));
        gtk_button_clicked(GTK_BUTTON(cookie->btn_remove));
    }

    // Headers
    while (g_slist_length(self->window_main->stack->content_headers->list_headers) > 0) {
        GiElementHeader* header = GI_ELEMENT_HEADER(g_slist_nth_data(self->window_main->stack->content_headers->list_headers, 0));
        gtk_button_clicked(GTK_BUTTON(header->btn_remove));
    }

    // Response
    gi_content_response_show_default(self->window_main->stack->content_response);

    // Other
    gtk_stack_set_visible_child(GTK_STACK(self->window_main->stack), GTK_WIDGET(self->window_main->stack->content_body));
    gi_element_header_bar_set_subtitle(self->window_main->header_bar, NULL);
    gi_element_header_bar_set_save_sensitive(self->window_main->header_bar, FALSE);
    self->file = NULL;
    gtk_label_set_text(GTK_LABEL(self->window_main->lbl_file), "File: (null)");
}

static gboolean gi_application_key_pressed(GtkWidget* caller, GdkEventKey* event, gpointer user_data)
{
    GiApplication* self = GI_APPLICATION(user_data);

    switch (event->keyval) {
    case GDK_KEY_s:
        if (event->state & GDK_MOD1_MASK && event->state & GDK_CONTROL_MASK) { // CTRL + ALT + S (save as menu item)
            gi_application_mi_save_as_activated(caller, user_data);
        } else if (event->state & GDK_CONTROL_MASK) { // CTRL + S (save menu item)
            gi_application_mi_save_activated(caller, user_data);
        }
        break;
    case GDK_KEY_o: // CTRL + O (open menu item)
        if (event->state & GDK_CONTROL_MASK) {
            gi_application_mi_open_activated(caller, user_data);
        }
        break;
    case GDK_KEY_Return:
        if (event->state & GDK_CONTROL_MASK) { // CTRL + Return (send the request)
            gtk_button_clicked(GTK_BUTTON(self->window_main->header_bar->btn_send));
        }
        break;
    case GDK_KEY_Escape: // ESC (cancel the request)
        gtk_button_clicked(GTK_BUTTON(self->window_main->header_bar->btn_cancel));
        break;
    }

    return FALSE;
}

static void gi_application_startup(GApplication* application, gpointer user_data)
{
    GiApplication* self = GI_APPLICATION(application);

    self->window_main = gi_window_main_new(self);
    gtk_window_present(GTK_WINDOW(self->window_main));

    // Connect signals
    g_signal_connect(self->window_main, "key_press_event", G_CALLBACK(gi_application_key_pressed), self);
    g_signal_connect(self->window_main->header_bar->mi_request_open, "activate", G_CALLBACK(gi_application_mi_open_activated), self);
    g_signal_connect(self->window_main->header_bar->mi_request_save_as, "activate", G_CALLBACK(gi_application_mi_save_as_activated), self);
    g_signal_connect(self->window_main->header_bar->mi_request_save, "activate", G_CALLBACK(gi_application_mi_save_activated), self);
    g_signal_connect(self->window_main->header_bar->mi_request_clear, "activate", G_CALLBACK(gi_application_mi_clear_activated), self);
}

static void gi_application_open(GApplication* application, GFile** files, gint n_files, const gchar* hint)
{
    GiApplication* self = GI_APPLICATION(application);
    GFile* file = NULL;

    if (n_files > 0) {
        file = files[0];
        const gchar* filename = g_file_get_path(file);

        if (gi_json_open_file(self->window_main, filename)) {
            self->file = file;
        }
    }
}

static void gi_application_activate(GApplication* application, gpointer user_data) {}

static void gi_application_init(GiApplication* self) {}

static void gi_application_class_init(GiApplicationClass* class)
{
    GApplicationClass* parent_class = G_APPLICATION_CLASS(class);
}

GiApplication* gi_application_new(int argc, char** argv)
{
    GiApplication* application = g_object_new(GI_TYPE_APPLICATION,
        "application-id", APPLICATION_ID,
        "flags", G_APPLICATION_HANDLES_OPEN,
        NULL);

    // Connect signals
    g_signal_connect(application, "activate", G_CALLBACK(gi_application_activate), NULL);
    g_signal_connect(application, "startup", G_CALLBACK(gi_application_startup), NULL);
    g_signal_connect(application, "open", G_CALLBACK(gi_application_open), NULL);

    return application;
}