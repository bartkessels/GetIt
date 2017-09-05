/*
 * gi-window-main.c
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
#include <gtksourceview/gtksource.h>
#include <libnotify/notify.h>
#include <libsoup/soup.h>
#include <string.h>

#include "gi-application.h"
#include "gi-content-body.h"
#include "gi-content-cookies.h"
#include "gi-content-headers.h"
#include "gi-content-response.h"
#include "gi-element-header-bar.h"
#include "gi-stack.h"
#include "gi-window-main.h"

G_DEFINE_TYPE(GiWindowMain, gi_window_main, GTK_TYPE_APPLICATION_WINDOW)

static void gi_window_main_request_finished(SoupSession* session, SoupMessage* message, gpointer user_data)
{
    GiWindowMain* self = GI_WINDOW_MAIN(user_data);

    // Check if request is cancelled
    if (self->request_cancelled) {
        self->request_cancelled = FALSE;
        return;
    }

    // Check if message is NULL
    if (message == NULL || message->response_body->data == NULL) {
        gi_content_response_show_error(self->stack->content_response, NULL);
        gi_element_header_bar_stop_loading(self->header_bar);

        return;
    }

    // Get mimetype from response
    const gchar* mime_type = soup_message_headers_get_one(message->response_headers, "Content-Type");
    const gchar* response_language = NULL;

    if (mime_type != NULL) {
        // Split mimetype on ';' character
        const gchar** mime_type_split = g_strsplit(mime_type, ";", 2);

        if (g_strv_length(mime_type_split) > 1) {
            response_language = mime_type_split[0];
        }
    }

    // Let GtkSourceLanguageManager guess the language
    GtkSourceLanguageManager* language_manager = gtk_source_language_manager_new();
    GtkSourceLanguage* language = gtk_source_language_manager_guess_language(language_manager, NULL, response_language);

    // Get headers and body
    SoupMessageHeaders* headers = message->response_headers;
    const gchar* body = message->response_body->data;
    guint status_code = message->status_code;
    const gchar* status_message = message->reason_phrase;

    // Stop loading animations
    gi_element_header_bar_stop_loading(self->header_bar);
    gi_content_response_show_response(self->stack->content_response, language, headers, body, status_code, status_message);

    // Display notification
    GError** error;
    SoupURI* soup_uri = soup_message_get_uri(message);
    NotifyNotification* notification = notify_notification_new("Request finished", soup_uri_to_string(soup_uri, FALSE), "network-transmit");
    notify_notification_show(notification, error);
}

static void gi_window_main_request_cancel(GiWindowMain* self)
{
    self->request_cancelled = TRUE;

    // Check if session isn't null
    if (self->session != NULL) {
        soup_session_abort(self->session);
    }

    // Stop loading animations
    gi_element_header_bar_stop_loading(self->header_bar);
    gi_content_response_show_default(self->stack->content_response);

    // Clear subtitle
    gi_element_header_bar_set_subtitle(self->header_bar, NULL);
}

static void gi_window_main_request_send(GiWindowMain* self, const gchar* method, const gchar* uri)
{
    // Create new soup message
    self->session = soup_session_new();
    SoupURI* soup_uri = soup_uri_new(uri);
    SoupMessage* message = soup_message_new_from_uri(method, soup_uri);

    // Add data
    gi_content_body_add_to_request(self->stack->content_body, message);
    gi_content_cookies_add_to_request(self->stack->content_cookies, message, soup_uri);
    gi_content_headers_add_to_request(self->stack->content_headers, message);

    // Send request
    soup_session_queue_message(self->session, message, gi_window_main_request_finished, self);
}

static void gi_window_main_btn_send_callback(GtkWidget* caller, gpointer user_data)
{
    GiWindowMain* self = GI_WINDOW_MAIN(user_data);

    if (gtk_widget_is_visible(caller)) {
        // Get information from body
        const gchar* method = gtk_combo_box_get_active_id(GTK_COMBO_BOX(self->stack->content_body->cb_method));
        const gchar* uri = gtk_entry_get_text(GTK_ENTRY(self->stack->content_body->et_uri));
        SoupURI* soup_uri = soup_uri_new(uri);

        // Check if uri is valid
        if (!SOUP_URI_IS_VALID(soup_uri)) {
            GtkWidget* message_dialog = gtk_message_dialog_new(GTK_WINDOW(self), GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_CLOSE, "Please enter a valid URI...", NULL);
            gtk_dialog_run(GTK_DIALOG(message_dialog));
            gtk_widget_destroy(message_dialog);

            return;
        }

        // Display loading animations
        gi_element_header_bar_start_loading(self->header_bar);
        gi_content_response_show_sending(self->stack->content_response);

        // Display response stack
        gtk_stack_set_visible_child(GTK_STACK(self->stack), GTK_WIDGET(self->stack->content_response));

        // Set subtitle to current request URI
        const gchar* subtitle = g_strconcat(method, ": ", uri, NULL);
        gi_element_header_bar_set_subtitle(self->header_bar, subtitle);

        // Send the request
        gi_window_main_request_send(self, method, uri);
    }
}

static void gi_window_main_btn_cancel_callback(GtkWidget* caller, gpointer user_data)
{
    GiWindowMain* self = GI_WINDOW_MAIN(user_data);

    if (gtk_widget_is_visible(caller)) {
        gi_window_main_request_cancel(self);
    }
}

static void gi_window_main_init(GiWindowMain* self)
{
    // Setup self
    self->request_cancelled = FALSE;

    // Setup header bar
    self->header_bar = gi_element_header_bar_new();
    gi_element_header_bar_set_title(self->header_bar, APPLICATION_TITLE);

    g_signal_connect(self->header_bar->btn_send, "clicked", G_CALLBACK(gi_window_main_btn_send_callback), self);
    g_signal_connect(self->header_bar->btn_cancel, "clicked", G_CALLBACK(gi_window_main_btn_cancel_callback), self);

    // Setup stack
    self->stack = gi_stack_new();
    gi_element_header_bar_set_stack(self->header_bar, self->stack);

    // Setup label for file
    self->lbl_file = gtk_label_new("File: (null)");
    gtk_label_set_xalign(GTK_LABEL(self->lbl_file), 0);

    // Setup grid
    GtkWidget* grd_main = gtk_grid_new();
    gtk_container_set_border_width(GTK_CONTAINER(grd_main), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grd_main), 5);
    gtk_grid_attach(GTK_GRID(grd_main), GTK_WIDGET(self->stack), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grd_main), self->lbl_file, 0, 1, 1, 1);

    // Setup self
    gtk_window_set_titlebar(GTK_WINDOW(self), GTK_WIDGET(self->header_bar));
    gtk_window_set_default_size(GTK_WINDOW(self), 1000, 600);
    gtk_container_add(GTK_CONTAINER(self), grd_main);

    // Show widgets
    gtk_widget_show_all(GTK_WIDGET(self));
    gi_element_header_bar_stop_loading(self->header_bar);
    gi_content_response_show_default(self->stack->content_response);
}

static void gi_window_main_class_init(GiWindowMainClass* class)
{
    GtkApplicationWindowClass* parent_class = GTK_APPLICATION_WINDOW_CLASS(class);
}

GiWindowMain* gi_window_main_new(GiApplication* application)
{
    return g_object_new(GI_TYPE_WINDOW_MAIN, "application", application, NULL);
}