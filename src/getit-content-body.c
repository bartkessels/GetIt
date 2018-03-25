/* getit-content-body.c
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

#include "getit-content-body.h"

struct _GetitContentBody {
    GtkViewport parent_instance;

    /* Template widgets */
    GtkEntry *et_uri;
    GtkComboBoxText *cb_method;
    GtkCheckButton *cbtn_validate_x509;
    GtkStackSwitcher *sw_data;
    GtkStack *stack_data;
    GtkGrid *grd_data_formdata_data;
    GtkGrid *grd_data_raw;
    GtkButton *btn_data_formdata_add;
    GtkComboBoxText *cb_data_raw_syntax;
    GtkSourceView *sv_data_raw_input;
};

G_DEFINE_TYPE (GetitContentBody, getit_content_body, GTK_TYPE_VIEWPORT)

/*
 * =============================================================================
 * Signatures
 *
 */
static void getit_content_body_class_init (GetitContentBodyClass *klass);
static void getit_content_body_init (GetitContentBody *self);
static void getit_content_body_add_formdata_to_request (GetitContentBody *self,
                                                        SoupMessage      *soup_message);
static void getit_content_body_add_raw_data_to_request (GetitContentBody *self,
                                                        SoupMessage      *soup_message);

/* Callback functions */
static void getit_content_body_cb_btn_add_formdata_clicked (GtkWidget *caller,
                                                            gpointer   user_data);
static void getit_content_body_cb_combobox_raw_syntax_changed (GtkWidget *caller,
                                                               gpointer   user_data);

/*
 * =============================================================================
 * Public function implementations
 *
 */
GetitContentBody *
getit_content_body_new()
{
    GetitContentBody *content_body;

    content_body = g_object_new(GETIT_TYPE_CONTENT_BODY, NULL);

    return content_body;
}

void
getit_content_body_clear (GetitContentBody *self)
{
    g_assert (GETIT_IS_CONTENT_BODY (self));

    gint total_list_size;
    GtkTextBuffer *raw_text_buffer;

    /* Clear method */
    gtk_combo_box_set_active (GTK_COMBO_BOX (self->cb_method), 0);

    /* Clear uri */
    gtk_entry_set_text (self->et_uri, "");

    /* Clear formdata */
    total_list_size = g_list_length (gtk_container_get_children (GTK_CONTAINER (self->grd_data_formdata_data)));

    /*
     * Iterate through elements
     */
    for (int list_iterator = 0; list_iterator < total_list_size; list_iterator++) {
        GetitElementFormdata *formdata;

        formdata = GETIT_ELEMENT_FORMDATA (gtk_grid_get_child_at (self->grd_data_formdata_data, 0, list_iterator));
        g_object_run_dispose (G_OBJECT (formdata));
    }

    /* Clear raw */
    gtk_combo_box_set_active (GTK_COMBO_BOX (self->cb_data_raw_syntax), 0);
    raw_text_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (self->sv_data_raw_input));
    gtk_text_buffer_set_text (raw_text_buffer, "", 0);

    /* Set default value for X.509 validation */
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (self->cbtn_validate_x509), DEF_VAL_VALIDATE_X509);
}

const gchar *
getit_content_body_get_uri (GetitContentBody *self)
{
    g_assert (GETIT_IS_CONTENT_BODY (self));

    const gchar *uri;
    uri = gtk_entry_get_text (GTK_ENTRY (self->et_uri));

    return uri;
}

const gchar *
getit_content_body_get_method (GetitContentBody *self)
{
    g_assert (GETIT_IS_CONTENT_BODY (self));

    const gchar *method;
    method = gtk_combo_box_get_active_id (GTK_COMBO_BOX (self->cb_method));

    return method;
}

gboolean
getit_content_body_get_validate_x509 (GetitContentBody *self)
{
    g_assert (GETIT_IS_CONTENT_BODY (self));

    gboolean validate_x509;
    validate_x509 = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (self->cbtn_validate_x509));

    return validate_x509;
}

const gchar *
getit_content_body_get_data_raw (GetitContentBody *self)
{
    g_assert (GETIT_IS_CONTENT_BODY (self));

    const gchar *data_raw;
    GtkTextBuffer *buffer;
    GtkTextIter iter_start;
    GtkTextIter iter_end;

    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (self->sv_data_raw_input));
    gtk_text_buffer_get_bounds (buffer, &iter_start, &iter_end);
    data_raw = gtk_text_buffer_get_text (buffer, &iter_start, &iter_end, FALSE);

    return data_raw;
}

const gchar *
getit_content_body_get_data_type (GetitContentBody *self)
{
    g_assert (GETIT_IS_CONTENT_BODY (self));

    const gchar *data_type;

    data_type = gtk_stack_get_visible_child_name (self->stack_data);

    return data_type;
}

void
getit_content_body_set_raw_input (GetitContentBody *self,
                                  const gchar      *input)
{
    g_assert (GETIT_IS_CONTENT_BODY (self));
    g_return_if_fail (input != NULL);

    GtkTextBuffer *text_buffer;

    text_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (self->sv_data_raw_input));

    gtk_text_buffer_set_text (text_buffer, input, strlen (input));
}

void
getit_content_body_add_to_request (GetitContentBody *self,
                                   SoupMessage      *soup_message)
{
    g_assert (GETIT_IS_CONTENT_BODY (self));
    g_assert (SOUP_IS_MESSAGE (soup_message));

    const gchar *body_type;

    /* Check what to add to the request */
    body_type = gtk_stack_get_visible_child_name (GTK_STACK (self->stack_data));

    if (g_str_equal (body_type, BODY_TYPE_FORMDATA)) {
        getit_content_body_add_formdata_to_request (self, soup_message);
    } else if (g_str_equal (body_type, BODY_TYPE_RAW)) {
        getit_content_body_add_raw_data_to_request (self, soup_message);
    }
}

void
getit_content_body_add_to_json_object (GetitContentBody *self,
                                       JsonObject       *json_body_object,
                                       const gchar      *formdata_array_name,
                                       const gchar      *body_uri_key,
                                       const gchar      *body_method_key,
                                       const gchar      *validate_x509_key,
                                       const gchar      *body_data_type_key,
                                       const gchar      *raw_language_key,
                                       const gchar      *raw_string_key,
                                       const gchar      *enabled_key,
                                       const gchar      *key_key,
                                       const gchar      *value_key,
                                       const gchar      *file_key,
                                       const gchar      *type_key)
{
    g_assert (GETIT_IS_CONTENT_BODY (self));
    g_assert_nonnull (json_body_object);

    gint total_list_size;
    JsonArray *json_array_formdata;
    const gchar *body_uri;
    gint body_method;
    gboolean validate_x509;
    const gchar *body_data_type;
    gint raw_language;
    const gchar *raw_data;

    json_array_formdata = json_array_new ();
    body_uri = getit_content_body_get_uri (self);
    body_method = gtk_combo_box_get_active (GTK_COMBO_BOX (self->cb_method));
    validate_x509 = getit_content_body_get_validate_x509 (self);
    body_data_type = getit_content_body_get_data_type (self);
    raw_language = gtk_combo_box_get_active (GTK_COMBO_BOX (self->cb_data_raw_syntax));
    raw_data = getit_content_body_get_data_raw (self);

    /*
     * Count the formdata elements in the grid
     */
    total_list_size = g_list_length (gtk_container_get_children (GTK_CONTAINER (self->grd_data_formdata_data)));

    /*
     * Iterate through formdata objects
     */
    for (int list_iterator = 0; list_iterator <= total_list_size; list_iterator++) {
        GetitElementFormdata *formdata;
        JsonObject *json_object_formdata;

        GtkWidget *current_widget;
        gboolean is_enabled;
        gint datatype;
        const gchar *key;
        const gchar *value;
        const gchar *file_name;

        /* Skip this iteration if it's not a cookie type */
        current_widget = gtk_grid_get_child_at (GTK_GRID (self->grd_data_formdata_data), 0, list_iterator);

        if (!GETIT_IS_ELEMENT_FORMDATA (current_widget)) {
            continue;
        }

        formdata = GETIT_ELEMENT_FORMDATA (current_widget);
        json_object_formdata = json_object_new ();
        is_enabled = getit_element_formdata_get_enabled (formdata);
        datatype = getit_element_formdata_get_datatype_int (formdata);
        key = getit_element_formdata_get_key (formdata);
        value = getit_element_formdata_get_value (formdata);
        file_name = getit_element_formdata_get_filename (formdata);

        /* Add values to formdata object */
        json_object_set_boolean_member (json_object_formdata, enabled_key, is_enabled);
        json_object_set_string_member (json_object_formdata, key_key, key);
        json_object_set_string_member (json_object_formdata, value_key, value);
        json_object_set_string_member (json_object_formdata, file_key, file_name);
        json_object_set_int_member (json_object_formdata, type_key, datatype);

        json_array_add_object_element (json_array_formdata, json_object_formdata);
    }

    json_object_set_array_member (json_body_object, formdata_array_name, json_array_formdata);
    json_object_set_string_member (json_body_object, body_uri_key, body_uri);
    json_object_set_int_member (json_body_object, body_method_key, body_method);
    json_object_set_boolean_member (json_body_object, validate_x509_key, validate_x509);
    json_object_set_string_member (json_body_object, body_data_type_key, body_data_type);
    json_object_set_int_member (json_body_object, raw_language_key, raw_language);
    json_object_set_string_member (json_body_object, raw_string_key, raw_data);
}

void
getit_content_body_add_formdata_with_values (GetitContentBody *self,
                                             const gboolean    enabled,
                                             const gchar      *key,
                                             const gchar      *value,
                                             const gchar      *file,
                                             const gint        type)
{
    g_assert (GETIT_CONTENT_BODY (self));

    gtk_container_add (GTK_CONTAINER (self->grd_data_formdata_data),
                       GTK_WIDGET (getit_element_formdata_new_with_values (enabled,
                                                                           key,
                                                                           value,
                                                                           file,
                                                                           type)));
}

void
getit_content_body_set_values (GetitContentBody *self,
                               const gint        method,
                               const gboolean    validate_x509,
                               const gchar      *uri,
                               const gchar      *data_type,
                               const gint        raw_language,
                               const gchar      *raw_input)
{
    g_assert (GETIT_IS_CONTENT_BODY (self));

    gtk_combo_box_set_active (GTK_COMBO_BOX (self->cb_method), method);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (self->cbtn_validate_x509), validate_x509);
    gtk_entry_set_text (self->et_uri, uri);
    gtk_stack_set_visible_child_name (self->stack_data, data_type);
    gtk_combo_box_set_active (GTK_COMBO_BOX (self->cb_data_raw_syntax), raw_language);
    getit_content_body_set_raw_input (self, raw_input);
}

/*
 * =============================================================================
 * Private function implementations
 *
 */
static void
getit_content_body_class_init (GetitContentBodyClass *klass)
{
    /* Load the GtkSourceView in the GObject symbol table
     * without this GtkBuilder is not able to load the
     * ui file because it cannot find the GtkSourceView type
     */
    g_type_ensure (gtk_source_view_get_type());

    GtkWidgetClass *widget_class;

    widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/net/bartkessels/getit/content-body.ui");
    gtk_widget_class_bind_template_child (widget_class, GetitContentBody, stack_data);
    gtk_widget_class_bind_template_child (widget_class, GetitContentBody, et_uri);
    gtk_widget_class_bind_template_child (widget_class, GetitContentBody, cb_method);
    gtk_widget_class_bind_template_child (widget_class, GetitContentBody, cbtn_validate_x509);
    gtk_widget_class_bind_template_child (widget_class, GetitContentBody, sw_data);
    gtk_widget_class_bind_template_child (widget_class, GetitContentBody, btn_data_formdata_add);
    gtk_widget_class_bind_template_child (widget_class, GetitContentBody, grd_data_formdata_data);
    gtk_widget_class_bind_template_child (widget_class, GetitContentBody, cb_data_raw_syntax);
    gtk_widget_class_bind_template_child (widget_class, GetitContentBody, sv_data_raw_input);
}

static void
getit_content_body_init (GetitContentBody *self)
{
    g_assert (GETIT_IS_CONTENT_BODY (self));
    g_assert (GTK_IS_WIDGET (self));

    gtk_widget_init_template (GTK_WIDGET (self));

    g_signal_connect (self->btn_data_formdata_add, "clicked",
                      G_CALLBACK (getit_content_body_cb_btn_add_formdata_clicked), self->grd_data_formdata_data);
    g_signal_connect (self->cb_data_raw_syntax, "changed",
                      G_CALLBACK (getit_content_body_cb_combobox_raw_syntax_changed), self);
}

static void
getit_content_body_add_formdata_to_request (GetitContentBody *self,
                                            SoupMessage      *soup_message)
{
    g_assert (GETIT_IS_CONTENT_BODY (self));
    g_assert (SOUP_IS_MESSAGE (soup_message));

    SoupMultipart *multipart;
    gint total_list_size;

    /* Initialize new soup multipart */
    multipart = soup_multipart_new (SOUP_FORM_MIME_TYPE_MULTIPART);

    /*
     * Count the formdata elements in the grid
     */
    total_list_size = g_list_length (gtk_container_get_children (GTK_CONTAINER (self->grd_data_formdata_data)));

    /*
     * Iterate through formdata objects
     */
    for (int list_iterator = 0; list_iterator <= total_list_size; list_iterator++) {
        GetitElementFormdata *formdata;

        GtkWidget *current_widget;
        gboolean is_enabled;
        const gchar *datatype;
        const gchar *key;
        const gchar *value;
        const gchar *file_name;

        GError *error = NULL; // Must be initialized as NULL
        GMappedFile *file;
        gsize file_length;
        const gchar *file_contents;
        SoupBuffer *file_buffer;

        /* Skip this iteration if it's not a cookie type */
        current_widget = gtk_grid_get_child_at (GTK_GRID (self->grd_data_formdata_data), 0, list_iterator);

        if (!GETIT_IS_ELEMENT_FORMDATA (current_widget)) {
            continue;
        }

        formdata = GETIT_ELEMENT_FORMDATA (current_widget);
        is_enabled = getit_element_formdata_get_enabled (formdata);
        datatype = getit_element_formdata_get_datatype (formdata);
        key = getit_element_formdata_get_key (formdata);
        value = getit_element_formdata_get_value (formdata);
        file_name = getit_element_formdata_get_filename (formdata);

        /* Skip this iteration if it's not enabled */
        if (!is_enabled) {
            continue;
        }

        /* Check if the user wants to upload a file or send a regular request */
        if (g_str_equal (datatype, DATATYPE_STRING)) {
            soup_multipart_append_form_string (multipart, key, value);
        } else if (g_str_equal (datatype, DATATYPE_FILE)) {
            file = g_mapped_file_new (file_name, FALSE, &error);

            /* Skip this iteration if an error occured */
            if (error != NULL) {
                continue;
            }

            file_length = g_mapped_file_get_length (file);
            file_contents = g_mapped_file_get_contents (file);

            file_buffer = soup_buffer_new (SOUP_MEMORY_STATIC, file_contents, file_length);

            soup_multipart_append_form_file (multipart, key, file_name, NULL, file_buffer);
        }
    }

    soup_multipart_to_message (multipart, soup_message->request_headers,
                               soup_message->request_body);
}

static void
getit_content_body_add_raw_data_to_request (GetitContentBody *self,
                                            SoupMessage      *soup_message)
{
    g_assert (GETIT_IS_CONTENT_BODY (self));
    g_assert (SOUP_IS_MESSAGE (soup_message));

    const gchar *language;
    const gchar *language_prefix;
    const gchar *mime_type;
    const gchar *data;

    language = gtk_combo_box_text_get_active_text (self->cb_data_raw_syntax);
    data = getit_content_body_get_data_raw (self);

    if (g_str_equal (language, "plain")) {
        language_prefix = "text/";
    } else {
        language_prefix = "application/";
    }

    mime_type = g_strconcat (language_prefix, language, NULL);

    soup_message_set_request (soup_message, mime_type, SOUP_MEMORY_COPY, data, strlen (data));
}

/*
 * =============================================================================
 * Private callback implementations
 *
 */
static void
getit_content_body_cb_btn_add_formdata_clicked (GtkWidget *caller,
                                                gpointer   user_data)
{
    g_assert (GTK_IS_BUTTON (caller));
    g_assert (GTK_IS_GRID (user_data));

    gtk_container_add (GTK_CONTAINER (user_data),
                       GTK_WIDGET (getit_element_formdata_new ()));

}

static void
getit_content_body_cb_combobox_raw_syntax_changed (GtkWidget *caller,
                                                   gpointer   user_data)
{
    g_assert (GTK_IS_COMBO_BOX (caller));
    g_assert (GETIT_IS_CONTENT_BODY (user_data));

    GetitContentBody *self;
    GtkTextBuffer *text_buffer;
    const gchar *syntax;
    GtkSourceLanguageManager *language_manager;
    GtkSourceLanguage *language;

    self = GETIT_CONTENT_BODY (user_data);
    text_buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (self->sv_data_raw_input));
    syntax = gtk_combo_box_get_active_id (GTK_COMBO_BOX (caller));
    language_manager = gtk_source_language_manager_new();
    language = gtk_source_language_manager_get_language (language_manager, syntax);

    gtk_source_buffer_set_language (GTK_SOURCE_BUFFER (text_buffer), language);
}
