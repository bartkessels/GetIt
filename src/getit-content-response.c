/* getit-content-response.c
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

#include "getit-content-response.h"

struct _GetitContentResponse {
    GtkScrolledWindow parent_instance;

    /* Template widgets */
    GtkLabel *lbl_default_message;
    GtkGrid *grd_sending;
    GtkGrid *grd_error;
    GtkLabel *lbl_error_message;
    GtkGrid *grd_output;
    GtkGrid *grd_headers;
    GtkSourceView *sv_output_pretty;
    GtkSourceView *sv_output_raw;
    GtkScrolledWindow *sw_output_preview;
    GtkWidget *wv_output_preview;
    GtkGrid *grd_timeout;
};

G_DEFINE_TYPE (GetitContentResponse, getit_content_response, GTK_TYPE_SCROLLED_WINDOW)

/*
 * =============================================================================
 * Signatures
 *
 */
static void getit_content_response_class_init (GetitContentResponseClass *klass);
static void getit_content_response_init (GetitContentResponse *self);
static void getit_content_response_add_header (const gchar *key,
                                               const gchar *value,
                                               gpointer     user_data);
static void getit_content_response_show_screen (GetitContentResponse *self,
                                                const gboolean        show_default,
                                                const gboolean        show_sending,
                                                const gboolean        show_response,
                                                const gboolean        show_error,
                                                const gboolean        show_timeout);

/*
 * =============================================================================
 * Public function implementations
 *
 */
GetitContentResponse *
getit_content_response_new ()
{
    GetitContentResponse *content_response;

    content_response = g_object_new (GETIT_TYPE_CONTENT_RESPONSE, NULL);
    content_response->wv_output_preview = webkit_web_view_new ();
    gtk_container_add (GTK_CONTAINER (content_response->sw_output_preview), content_response->wv_output_preview);

    return content_response;
}

void
getit_content_response_show_default (GetitContentResponse *self)
{
    g_assert (GETIT_CONTENT_RESPONSE (self));

    getit_content_response_show_screen (self,
                                        TRUE,
                                        FALSE,
                                        FALSE,
                                        FALSE,
                                        FALSE);
}

void
getit_content_response_show_sending (GetitContentResponse *self)
{
    g_assert (GETIT_CONTENT_RESPONSE (self));

    getit_content_response_show_screen (self,
                                        FALSE,
                                        TRUE,
                                        FALSE,
                                        FALSE,
                                        FALSE);
}

void
getit_content_response_show_response (GetitContentResponse *self,
                                      GtkSourceLanguage    *language,
                                      SoupMessageHeaders   *headers,
                                      const gchar          *body,
                                      guint                 status_code,
                                      const gchar          *status_message,
                                      const gchar          *uri)
{
    g_assert (GETIT_CONTENT_RESPONSE (self));

    GList *children, *children_iter;
    const gchar *status_value;
    GtkTextBuffer *text_buffer_pretty;
    GtkTextBuffer *text_buffer_raw;
    const gchar *mimetype;
    GString *string_response;
    GBytes *bytes_response;

    getit_content_response_show_screen (self,
                                        FALSE,
                                        FALSE,
                                        TRUE,
                                        FALSE,
                                        FALSE);

    /* Clear headers grid */
    children = gtk_container_get_children (GTK_CONTAINER (self->grd_headers));


    for (children_iter = children; children_iter != NULL; children_iter = g_list_next(children_iter)) {
        gtk_widget_destroy (GTK_WIDGET (children_iter->data));
    }

    g_list_free (children);
    g_list_free (children_iter);

    /* Add headers */
    status_value = g_strdup_printf ("%i (%s)", status_code, status_message);
    getit_content_response_add_header (_("Status"), status_value, self);

    soup_message_headers_foreach (headers, getit_content_response_add_header, self);

    /* Create and clear buffer */
    text_buffer_pretty = gtk_text_view_get_buffer (GTK_TEXT_VIEW (self->sv_output_pretty));
    text_buffer_raw = gtk_text_view_get_buffer (GTK_TEXT_VIEW (self->sv_output_raw));
    gtk_text_buffer_set_text (text_buffer_pretty, "", 0);
    gtk_text_buffer_set_text (text_buffer_raw, "", 0);

    /* Add body to sourceviews if it's not null */
    if (body != NULL) {
        gtk_text_buffer_set_text (text_buffer_pretty, body, strlen (body));
        gtk_text_buffer_set_text (text_buffer_raw, body, strlen (body));
    }

    /* Get mimetype */
    mimetype = NULL;
    if (language != NULL) {
        mimetype = gtk_source_language_get_mime_types (language)[0];
    }

    /* Load webview */
    string_response = g_string_new (body);
    bytes_response = g_string_free_to_bytes (string_response);
    webkit_web_view_load_bytes (WEBKIT_WEB_VIEW (self->wv_output_preview),
                                bytes_response,
                                mimetype,
                                NULL,
                                uri);

    /* Set language of response */
    if (GTK_SOURCE_IS_LANGUAGE (language)) {
        gtk_source_buffer_set_language (GTK_SOURCE_BUFFER (text_buffer_pretty), language);
    }

    gtk_widget_show_all (GTK_WIDGET (self->grd_output));
}

void
getit_content_response_show_error (GetitContentResponse *self,
                                   const gchar          *error_message)
{
    g_assert (GETIT_IS_CONTENT_RESPONSE (self));

    getit_content_response_show_screen (self,
                                        FALSE,
                                        FALSE,
                                        FALSE,
                                        TRUE,
                                        FALSE);

    if (error_message == NULL || strlen (error_message) < 1) {
        error_message = MSG_ERROR_SENDING;
    }

    gtk_label_set_text (self->lbl_error_message, error_message);
}

void
getit_content_response_show_timeout (GetitContentResponse *self)
{
    g_assert (GETIT_IS_CONTENT_RESPONSE (self));

    getit_content_response_show_screen (self,
                                        FALSE,
                                        FALSE,
                                        FALSE,
                                        FALSE,
                                        TRUE);
}

 /*
 * =============================================================================
 * Private function implementations
 *
 */
static void
getit_content_response_class_init (GetitContentResponseClass *klass)
{
    /* Load the GtkSourceView in the GObject symbol table
     * without this GtkBuilder is not able to load the
     * ui file because it cannot find the GtkSourceView type
     */
    g_type_ensure (gtk_source_view_get_type());

    GtkWidgetClass *widget_class;

    widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/net/bartkessels/getit/content-response.ui");
    gtk_widget_class_bind_template_child (widget_class, GetitContentResponse, lbl_default_message);
    gtk_widget_class_bind_template_child (widget_class, GetitContentResponse, grd_sending);
    gtk_widget_class_bind_template_child (widget_class, GetitContentResponse, grd_error);
    gtk_widget_class_bind_template_child (widget_class, GetitContentResponse, lbl_error_message);
    gtk_widget_class_bind_template_child (widget_class, GetitContentResponse, grd_output);
    gtk_widget_class_bind_template_child (widget_class, GetitContentResponse, grd_headers);
    gtk_widget_class_bind_template_child (widget_class, GetitContentResponse, sv_output_pretty);
    gtk_widget_class_bind_template_child (widget_class, GetitContentResponse, sv_output_raw);
    gtk_widget_class_bind_template_child (widget_class, GetitContentResponse, sw_output_preview);
    gtk_widget_class_bind_template_child (widget_class, GetitContentResponse, grd_timeout);
}

static void
getit_content_response_init (GetitContentResponse *self)
{
    g_assert (GETIT_IS_CONTENT_RESPONSE (self));
    g_assert (GTK_IS_WIDGET (self));

    gtk_widget_init_template (GTK_WIDGET (self));
}

static void
getit_content_response_add_header (const gchar *key,
                                   const gchar *value,
                                   gpointer     user_data)
{
    g_assert (GETIT_IS_CONTENT_RESPONSE (user_data));

    GetitContentResponse *self;
    gint row_index;

    self = GETIT_CONTENT_RESPONSE (user_data);
    row_index = g_list_length (gtk_container_get_children (GTK_CONTAINER (self->grd_headers))) / 3; // Divide by 3 'cause there are
                                                                                                    // 3 widgets for each header

    GtkWidget *lbl_key, *lbl_arrow, *lbl_value;

    lbl_key = gtk_label_new (key);
    lbl_arrow = gtk_label_new (NULL);
    lbl_value = gtk_label_new (value);

    gtk_label_set_markup_with_mnemonic (GTK_LABEL (lbl_arrow), "&#8594;");

    gtk_label_set_xalign (GTK_LABEL (lbl_key), 0);
    gtk_label_set_xalign (GTK_LABEL (lbl_value), 0);

    gtk_grid_attach (GTK_GRID (self->grd_headers), lbl_key, 0, row_index, 1, 1);
    gtk_grid_attach (GTK_GRID (self->grd_headers), lbl_arrow, 1, row_index, 1, 1);
    gtk_grid_attach (GTK_GRID (self->grd_headers), lbl_value, 2, row_index, 1, 1);
}

static void
getit_content_response_show_screen (GetitContentResponse *self,
                                    const gboolean        show_default,
                                    const gboolean        show_sending,
                                    const gboolean        show_response,
                                    const gboolean        show_error,
                                    const gboolean        show_timeout)
{
    g_assert (GETIT_IS_CONTENT_RESPONSE (self));

    gtk_widget_set_visible (GTK_WIDGET (self->lbl_default_message), show_default);
    gtk_widget_set_visible (GTK_WIDGET (self->grd_sending), show_sending);
    gtk_widget_set_visible (GTK_WIDGET (self->grd_output), show_response);
    gtk_widget_set_visible (GTK_WIDGET (self->grd_error), show_error);
    gtk_widget_set_visible (GTK_WIDGET (self->grd_timeout), show_timeout);
}
