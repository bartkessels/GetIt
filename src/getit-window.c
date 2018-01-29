/* getit-window.c
 *
 * Copyright (C) 2017 Bart Kessels
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

#include "getit-config.h"
#include "getit-window.h"

struct _GetitWindow
{
    GtkApplicationWindow  parent_instance;

    /* Template widgets */
    GtkHeaderBar *header_bar;
    GtkStackSwitcher *stack_switcher;
    GtkMenuButton *mbtn_menu;
    GtkButton *btn_send;
    GtkButton *btn_cancel;
    GtkSpinner *sp_loading;
    GtkGrid *grd_main;
    GtkLabel *lbl_file;

    GtkModelButton *mi_open;
    GtkModelButton *mi_save_as;
    GtkModelButton *mi_save;
    GtkModelButton *mi_clear;

    /* Member variables */
    GetitStack *stack;
    gboolean request_canceled;
    SoupSession *soup_session;
    GFile *file;
};

G_DEFINE_TYPE (GetitWindow, getit_window, GTK_TYPE_APPLICATION_WINDOW)

/*
 * =============================================================================
 * Signatures
 *
 */
static void getit_window_class_init (GetitWindowClass *klass);
static void getit_window_init (GetitWindow *self);
static void getit_window_request_finished (SoupSession *session,
                                           SoupMessage *message,
                                           gpointer     user_data);
static void getit_window_request_cancel (GetitWindow *self);
static void getit_window_request_send (GetitWindow *self);
static void getit_window_set_loading (GetitWindow *self,
                                      gboolean     loading);

/* Callback functions */
static gboolean getit_window_register_shortcuts (GtkWidget   *caller,
                                                 GdkEventKey *event,
                                                 gpointer     user_data);
static void getit_window_cb_btn_send_clicked (GtkWidget *caller,
                                              gpointer   user_data);
static void getit_window_cb_btn_cancel_clicked (GtkWidget *caller,
                                                gpointer   user_data);
static void getit_window_cb_mi_open_clicked (GtkWidget *caller,
                                             gpointer   user_data);
static void getit_window_cb_mi_save_as_clicked (GtkWidget *caller,
                                                gpointer   user_data);
static void getit_window_cb_mi_save_clicked (GtkWidget *caller,
                                             gpointer   user_data);
static void getit_window_cb_mi_clear_clicked (GtkWidget *caller,
                                              gpointer   user_data);

/*
 * =============================================================================
 * Public function implementations
 *
 */
GetitWindow *
getit_window_new (GApplication *app)
{
    g_assert (G_IS_APPLICATION (app));

    GetitWindow *window;

    window = g_object_new (GETIT_TYPE_WINDOW,
                           "application", app,
                           "default-width", WINDOW_WIDTH,
                           "default-height", WINDOW_HEIGHT,
                           NULL);

    return window;
}

void
getit_window_clear (GetitWindow *self)
{
    g_assert (GETIT_IS_WINDOW (self));

    GetitContentBody *content_body;
    GetitContentCookies *content_cookies;
    GetitContentHeaders *content_headers;
    GetitContentResponse *content_response;

    content_body = getit_stack_get_content_body (self->stack);
    content_cookies = getit_stack_get_content_cookies (self->stack);
    content_headers = getit_stack_get_content_headers (self->stack);
    content_response = getit_stack_get_content_response (self->stack);

    getit_content_body_clear (content_body);
    getit_content_cookies_clear (content_cookies);
    getit_content_headers_clear (content_headers);
    getit_content_response_show_default (content_response);

    getit_window_set_subtitle (self, "");

    self->file = NULL;
    gtk_label_set_text (self->lbl_file, _("File: (null)"));
}

void
getit_window_set_title (GetitWindow *self,
                        const gchar *title)
{
    g_assert (GETIT_IS_WINDOW (self));

    gtk_header_bar_set_title (self->header_bar, title);
}

void
getit_window_set_subtitle (GetitWindow *self,
                           const gchar *subtitle)
{
    g_assert (GETIT_IS_WINDOW (self));

    gtk_header_bar_set_subtitle (self->header_bar, subtitle);
}

void
getit_window_save_file (GetitWindow *self,
                        const gchar *file_name)
{
    g_assert (GETIT_IS_WINDOW (self));
    g_assert_nonnull (file_name);

    GetitContentBody *content_body;
    GetitContentCookies *content_cookies;
    GetitContentHeaders *content_headers;
    GtkWidget *dialog_error;
    const gchar *file_label;
    gboolean file_saved;

    content_body = getit_stack_get_content_body (self->stack);
    content_cookies = getit_stack_get_content_cookies (self->stack);
    content_headers = getit_stack_get_content_headers (self->stack);

    file_saved = getit_json_save_file (content_body,
                                       content_cookies,
                                       content_headers,
                                       file_name);

    if (!file_saved) {
        dialog_error = gtk_message_dialog_new_with_markup (GTK_WINDOW (self),
                                                           GTK_DIALOG_MODAL,
                                                           GTK_MESSAGE_ERROR,
                                                           GTK_BUTTONS_CLOSE,
                                                           MSG_ERROR_SAVING);
        gtk_dialog_run (GTK_DIALOG (dialog_error));
        gtk_widget_destroy (dialog_error);

        return;
    }

    self->file = g_file_new_for_uri (file_name);
    file_label = g_strconcat (_("File: "), file_name, NULL);

    gtk_label_set_text (self->lbl_file, file_label);
}

void
getit_window_open_file (GetitWindow *self,
                        const gchar *file_name)
{
    g_assert (GETIT_IS_WINDOW (self));
    g_assert_nonnull (file_name);

    GetitContentBody *content_body;
    GetitContentCookies *content_cookies;
    GetitContentHeaders *content_headers;
    GetitContentResponse *content_response;
    gboolean file_opened;
    GtkWidget *dialog_error;
    const gchar *file_label;

    content_body = getit_stack_get_content_body (self->stack);
    content_cookies = getit_stack_get_content_cookies (self->stack);
    content_headers = getit_stack_get_content_headers (self->stack);
    content_response = getit_stack_get_content_response (self->stack);

    file_opened = getit_json_open_file (content_body,
                                        content_cookies,
                                        content_headers,
                                        content_response,
                                        file_name);

    if (!file_opened) {
        dialog_error = gtk_message_dialog_new_with_markup (GTK_WINDOW (self),
                                                           GTK_DIALOG_MODAL,
                                                           GTK_MESSAGE_ERROR,
                                                           GTK_BUTTONS_CLOSE,
                                                           MSG_ERROR_OPENING);
        gtk_dialog_run (GTK_DIALOG (dialog_error));
        gtk_widget_destroy (dialog_error);

        return;
    }

    self->file = g_file_new_for_uri (file_name);
    file_label = g_strconcat (_("File: "), file_name, NULL);
    gtk_label_set_text (self->lbl_file, file_label);
    getit_window_set_subtitle (self, "");
}

/*
 * =============================================================================
 * Private function implementations
 *
 */
static void
getit_window_class_init (GetitWindowClass *klass)
{
    GtkWidgetClass *widget_class;

    widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/net/bartkessels/getit/window-main.ui");

    gtk_widget_class_bind_template_child (widget_class, GetitWindow, header_bar);
    gtk_widget_class_bind_template_child (widget_class, GetitWindow, stack_switcher);
    gtk_widget_class_bind_template_child (widget_class, GetitWindow, mbtn_menu);
    gtk_widget_class_bind_template_child (widget_class, GetitWindow, btn_send);
    gtk_widget_class_bind_template_child (widget_class, GetitWindow, btn_cancel);
    gtk_widget_class_bind_template_child (widget_class, GetitWindow, sp_loading);
    gtk_widget_class_bind_template_child (widget_class, GetitWindow, grd_main);
    gtk_widget_class_bind_template_child (widget_class, GetitWindow, lbl_file);
    gtk_widget_class_bind_template_child (widget_class, GetitWindow, mi_open);
    gtk_widget_class_bind_template_child (widget_class, GetitWindow, mi_save_as);
    gtk_widget_class_bind_template_child (widget_class, GetitWindow, mi_save);
    gtk_widget_class_bind_template_child (widget_class, GetitWindow, mi_clear);
}

static void
getit_window_init (GetitWindow *self)
{
    g_assert (GETIT_IS_WINDOW (self));
    g_assert (GTK_IS_WINDOW (self));
    g_assert (GTK_IS_WIDGET (self));

    gtk_widget_init_template (GTK_WIDGET (self));

    /* Create stack */
    self->stack = getit_stack_new ();

    gtk_stack_switcher_set_stack (GTK_STACK_SWITCHER (self->stack_switcher), GTK_STACK (self->stack));
    gtk_grid_attach (self->grd_main, GTK_WIDGET (self->stack), 0, 0, 1, 1);

    /* Connect signals */
    g_signal_connect (self->btn_send, "clicked",
                      G_CALLBACK (getit_window_cb_btn_send_clicked), self);
    g_signal_connect (self->btn_cancel, "clicked",
                      G_CALLBACK (getit_window_cb_btn_cancel_clicked), self);
    g_signal_connect (self->mi_open, "clicked",
                      G_CALLBACK (getit_window_cb_mi_open_clicked), self);
    g_signal_connect (self->mi_save_as, "clicked",
                      G_CALLBACK (getit_window_cb_mi_save_as_clicked), self);
    g_signal_connect (self->mi_save, "clicked",
                      G_CALLBACK (getit_window_cb_mi_save_clicked), self);
    g_signal_connect (self->mi_clear, "clicked",
                      G_CALLBACK (getit_window_cb_mi_clear_clicked), self);
    g_signal_connect (self, "key_press_event",
                      G_CALLBACK (getit_window_register_shortcuts), self);

    /* Show widgets */
    gtk_widget_show (GTK_WIDGET (self->stack));
}

static void
getit_window_request_finished (SoupSession *session,
                               SoupMessage *message,
                               gpointer     user_data)
{
    g_assert (SOUP_IS_SESSION (session));
    g_assert (SOUP_IS_MESSAGE (message));
    g_assert (GETIT_IS_WINDOW (user_data));

    GetitWindow *self;
    GetitContentResponse *content_response;

    const gchar *mime_type;
    const gchar *response_language;
    gchar **mime_type_split;
    SoupURI *soup_uri;
    const gchar *uri;

    GtkSourceLanguageManager *language_manager;
    GtkSourceLanguage *language;

    self = GETIT_WINDOW (user_data);
    content_response = getit_stack_get_content_response (self->stack);

    /* Check if connection was timed out */
    if (message->status_code == 7) {
        /* Abort session */
        soup_session_abort (self->soup_session);

        getit_notification_display (_("Request timed out"),
                                    soup_uri_to_string (soup_message_get_uri (message), FALSE),
                                    "network-transmit");
        getit_content_response_show_timeout (content_response);
        getit_window_set_loading (self, FALSE);

        return;
    }

    /* Other checks */
    g_return_if_fail (!self->request_canceled);
    g_return_if_fail (message != NULL);

    /* Guess the language based on the mime type */
    mime_type = soup_message_headers_get_one (message->response_headers, "Content-Type");
    response_language = "text/plain";

    if (mime_type != NULL) {
        mime_type_split = g_strsplit (mime_type, ";", 2);

        if (g_strv_length (mime_type_split) >= 1) {
            response_language = mime_type_split [0];
        }
    }

    language_manager = gtk_source_language_manager_new ();
    language = gtk_source_language_manager_guess_language (language_manager, NULL, response_language);

    soup_uri = soup_message_get_uri (message);
    uri = soup_uri_to_string (soup_uri, FALSE);

    /* Update UI */
    getit_content_response_show_response (content_response,
                                          language,
                                          message->response_headers,
                                          message->response_body->data,
                                          message->status_code,
                                          message->reason_phrase,
                                          uri);
    getit_window_set_loading (self, FALSE);

    getit_notification_display (_("Request sent"),
                                    soup_uri_to_string (soup_message_get_uri (message), FALSE),
                                    "network-transmit");
}

static void
getit_window_request_cancel (GetitWindow *self)
{
    g_assert (GETIT_IS_WINDOW (self));

    GetitContentResponse *content_response;

    g_return_if_fail (self->soup_session != NULL);
    g_return_if_fail (gtk_widget_get_visible (GTK_WIDGET (self->btn_cancel)));

    content_response = getit_stack_get_content_response (self->stack);

    /* Update UI */
    getit_content_response_show_default (content_response);

    getit_window_set_loading (self, FALSE);
    getit_window_set_subtitle (self, NULL);

    soup_session_abort (self->soup_session);
}

static void
getit_window_request_send (GetitWindow *self)
{
    g_assert (GETIT_IS_WINDOW (self));

    g_return_if_fail (!gtk_widget_is_visible (GTK_WIDGET (self->sp_loading)));

    const gchar *method;
    const gchar *uri;

    SoupURI *soup_uri;
    SoupMessage *soup_message;

    GetitContentBody *content_body;
    GetitContentCookies *content_cookies;
    GetitContentHeaders *content_headers;
    GetitContentResponse *content_response;

    content_body = getit_stack_get_content_body (self->stack);
    content_cookies = getit_stack_get_content_cookies (self->stack);
    content_headers = getit_stack_get_content_headers (self->stack);
    content_response = getit_stack_get_content_response (self->stack);

    method = getit_content_body_get_method (content_body);
    uri = getit_content_body_get_uri (content_body);

    soup_uri = soup_uri_new (uri);

    g_return_if_fail (SOUP_URI_IS_VALID (soup_uri));

    /* Update UI */
    getit_content_response_show_sending (content_response);
    getit_window_set_loading (self, TRUE);

    getit_window_set_subtitle (self, g_strconcat (method, ": ", uri, NULL));
    gtk_stack_set_visible_child (GTK_STACK (self->stack), GTK_WIDGET (content_response));

    /* Send the request */
    self->soup_session = soup_session_new_with_options ("timeout", getit_settings_get_timeout (),
                                                        "user-agent", getit_settings_get_user_agent (),
                                                        NULL);
    soup_message = soup_message_new_from_uri (method, soup_uri);

    getit_content_body_add_to_request (content_body, soup_message);
    getit_content_cookies_add_to_request (content_cookies, soup_message, soup_uri);
    getit_content_headers_add_to_request (content_headers, soup_message);

    soup_session_queue_message (self->soup_session, soup_message,
                                getit_window_request_finished, self);
}

static void
getit_window_set_loading (GetitWindow *self,
                          gboolean     loading)
{
    g_assert (GETIT_IS_WINDOW (self));

    gtk_widget_set_visible (GTK_WIDGET (self->btn_send), !loading);
    gtk_widget_set_visible (GTK_WIDGET (self->btn_cancel), loading);
    gtk_widget_set_visible (GTK_WIDGET (self->sp_loading), loading);
}

/*
 * =============================================================================
 * Private callback implementations
 *
 */

static gboolean
getit_window_register_shortcuts (GtkWidget   *caller,
                                 GdkEventKey *event,
                                 gpointer     user_data)
{
    g_assert (GETIT_IS_WINDOW (user_data));

    GetitWindow *self;

    self = GETIT_WINDOW (user_data);

    switch (event->keyval) {

    case GDK_KEY_s:
        if (event->state & GDK_MOD1_MASK &&
            event->state & GDK_CONTROL_MASK) { // CTRL + ALT + S
                getit_window_cb_mi_save_as_clicked (GTK_WIDGET (self->mi_save_as),
                                                    self);
            } else if (event->state & GDK_CONTROL_MASK) { // CTRL + S
                getit_window_cb_mi_save_clicked (GTK_WIDGET (self->mi_save),
                                                 self);
            }
       break;

    case GDK_KEY_o:
        if (event->state & GDK_CONTROL_MASK) { // CTRL + O
            getit_window_cb_mi_open_clicked (GTK_WIDGET (self->mi_open),
                                             self);
        }
        break;

    case GDK_KEY_Return:
        if (event->state & GDK_CONTROL_MASK) { // CTRL + Return
            getit_window_cb_btn_send_clicked (GTK_WIDGET (self->btn_send),
                                              self);
        }
        break;

    case GDK_KEY_Escape:
        getit_window_cb_btn_cancel_clicked (GTK_WIDGET (self->btn_cancel), self);
        break;

    };

    return FALSE;
}

static void
getit_window_cb_btn_send_clicked (GtkWidget *caller,
                                  gpointer   user_data)
{
    g_assert (GTK_IS_BUTTON (caller));
    g_assert (GETIT_IS_WINDOW (user_data));

    GetitWindow *self;

    self = GETIT_WINDOW (user_data);

    self->request_canceled = FALSE;
    getit_window_request_send (self);
}

static void
getit_window_cb_btn_cancel_clicked (GtkWidget *caller,
                                    gpointer   user_data)
{
    g_assert (GTK_IS_BUTTON (caller));
    g_assert (GETIT_IS_WINDOW (user_data));

    GetitWindow *self;

    self = GETIT_WINDOW (user_data);

    self->request_canceled = TRUE;
    getit_window_request_cancel (self);
}

static void
getit_window_cb_mi_open_clicked (GtkWidget *caller,
                                 gpointer   user_data)
{
    g_assert (GTK_IS_MODEL_BUTTON (caller));
    g_assert (GETIT_IS_WINDOW (user_data));

    GetitWindow *self;
    GtkFileFilter *file_filter;
    GtkFileChooserNative *file_chooser;
    gint file_chooser_result;
    const gchar *file_name;

    self = GETIT_WINDOW (user_data);
    file_filter = gtk_file_filter_new ();
    file_chooser = gtk_file_chooser_native_new (_("Open Request"),
                                                GTK_WINDOW (self),
                                                GTK_FILE_CHOOSER_ACTION_OPEN,
                                                _("Cancel"),
                                                _("Open"));

    gtk_file_filter_add_pattern (file_filter, "*.getit");
    gtk_file_chooser_set_filter (GTK_FILE_CHOOSER (file_chooser), file_filter);

    file_chooser_result = gtk_native_dialog_run (GTK_NATIVE_DIALOG (file_chooser));
    file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (file_chooser));
    g_object_unref (file_chooser);

    /* User canceled open action */
    if (file_chooser_result != GTK_RESPONSE_ACCEPT) {
        return;
    }

    getit_window_open_file (self,
                            file_name);
}

static void
getit_window_cb_mi_save_as_clicked (GtkWidget *caller,
                                    gpointer   user_data)
{
    g_assert (GTK_IS_MODEL_BUTTON (caller));
    g_assert (GETIT_IS_WINDOW (user_data));

    GetitWindow *self;
    GtkFileFilter *file_filter;
    GtkFileChooserNative *file_chooser;
    gint file_chooser_result;
    const gchar *file_name;

    self = GETIT_WINDOW (user_data);
    file_filter = gtk_file_filter_new ();
    file_chooser = gtk_file_chooser_native_new (_("Save Request"),
                                                GTK_WINDOW (self),
                                                GTK_FILE_CHOOSER_ACTION_SAVE,
                                                _("Cancel"),
                                                _("Save"));

    gtk_file_filter_add_pattern (file_filter, "*.getit");
    gtk_file_chooser_set_filter (GTK_FILE_CHOOSER (file_chooser), file_filter);
    gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (file_chooser), TRUE);

    file_chooser_result = gtk_native_dialog_run (GTK_NATIVE_DIALOG (file_chooser));
    file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (file_chooser));
    g_object_unref (file_chooser);

    /* User canceled save action */
    if (file_chooser_result != GTK_RESPONSE_ACCEPT) {
        return;
    }

    /* Make sure the .getit extension is added */
    if (!g_str_has_suffix (file_name, ".getit")) {
        file_name = g_strconcat (file_name, ".getit", NULL);
    }

    getit_window_save_file (self, file_name);
}

static void
getit_window_cb_mi_save_clicked (GtkWidget *caller,
                                 gpointer   user_data)
{
    g_assert (GTK_IS_MODEL_BUTTON (caller));
    g_assert (GETIT_IS_WINDOW (user_data));

    GetitWindow *self;
    const gchar *file_name;

    self = GETIT_WINDOW (user_data);
    file_name = g_file_get_uri (self->file);

    if (self->file == NULL) {
        getit_window_cb_mi_save_as_clicked (caller, user_data);
        return;
    }

    getit_window_save_file (user_data, file_name);
}

static void
getit_window_cb_mi_clear_clicked (GtkWidget *caller,
                                  gpointer   user_data)
{
    g_assert (GTK_IS_MODEL_BUTTON (caller));
    g_assert (GETIT_IS_WINDOW (user_data));

    GetitWindow *self;
    GtkWidget *dialog_question;
    gint dialog_result;

    self = GETIT_WINDOW (user_data);

    /* Ask if the user really wants to clear the request */
    dialog_question = gtk_message_dialog_new_with_markup (GTK_WINDOW (self),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_MESSAGE_QUESTION,
                                                          GTK_BUTTONS_YES_NO,
                                                          MSG_QUESTION_CLEAR);
    dialog_result = gtk_dialog_run (GTK_DIALOG (dialog_question));
    gtk_widget_destroy (dialog_question);

    if (dialog_result == GTK_RESPONSE_YES) {
        getit_window_clear (self);
    }
}
