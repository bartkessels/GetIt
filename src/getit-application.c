/* getit-application.c
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

#include "getit-application.h"

struct _GetitApplication {
    GtkApplication parent_instance;
};

G_DEFINE_TYPE (GetitApplication, getit_application, GTK_TYPE_APPLICATION);

/*
 * =============================================================================
 * Signatures
 *
 */
static void getit_application_class_init (GetitApplicationClass *klass);
static void getit_application_init (GetitApplication *self);

/* Callback functions */
static void getit_application_cb_activate (GApplication *app);
static void getit_application_cb_startup (GApplication *app);
static void getit_application_cb_open (GApplication  *app,
                                       GFile        **files,
                                       gint           n_files,
                                       const gchar   *hint);
static void getit_application_cb_recent (GSimpleAction *action,
                                         GVariant      *parameter,
                                         gpointer       user_data);
static void getit_application_cb_shortcuts (GSimpleAction *action,
                                            GVariant      *parameter,
                                            gpointer       user_data);
static void getit_application_cb_preferences (GSimpleAction *action,
                                              GVariant      *parameter,
                                              gpointer       user_data);
static void getit_application_cb_about (GSimpleAction *action,
                                        GVariant      *parameter,
                                        gpointer       user_data);
static void getit_application_cb_quit (GSimpleAction *action,
                                       GVariant      *parameter,
                                       gpointer       user_data);

/*
 * =============================================================================
 * App menu entries
 *
 */
const GActionEntry app_actions[] = {
        { "recent", getit_application_cb_recent },
        { "shortcuts", getit_application_cb_shortcuts },
        { "preferences", getit_application_cb_preferences },
        { "about", getit_application_cb_about },
        { "quit", getit_application_cb_quit }
};

/*
 * =============================================================================
 * Public function implementations
 *
 */
GetitApplication *
getit_application_new ()
{
    GetitApplication *application;

    application = g_object_new (GETIT_TYPE_APPLICATION,
                                "application-id", APPLICATION_ID,
                                "flags", G_APPLICATION_HANDLES_OPEN,
                                NULL);

    return application;
}

/*
 * =============================================================================
 * Private function implementations
 *
 */
static void
getit_application_class_init (GetitApplicationClass *klass)
{
    GApplicationClass *parent_class;

    parent_class = G_APPLICATION_CLASS (klass);

    parent_class->activate = getit_application_cb_activate;
    parent_class->open = getit_application_cb_open;
}

static void
getit_application_init (GetitApplication *self)
{
    g_assert (GETIT_IS_APPLICATION (self));

    g_signal_connect (self, "startup", G_CALLBACK (getit_application_cb_startup), NULL);
}

/*
 * =============================================================================
 * Callback function implementations
 *
 */
static void
getit_application_cb_activate (GApplication *app)
{
    g_assert (G_IS_APPLICATION (app));

    GtkWindow *window;

    /* Get the current window or create one if necessary. */
    window = gtk_application_get_active_window (GTK_APPLICATION (app));
    if (window == NULL)
        window = g_object_new (GETIT_TYPE_WINDOW,
                               "application", app,
                               "default-width", WINDOW_WIDTH,
                               "default-height", WINDOW_HEIGHT,
                               NULL);

    /* Ask the window manager/compositor to present the window. */
    gtk_window_present (window);
}

static void
getit_application_cb_startup (GApplication *app)
{
    g_assert (G_IS_APPLICATION (app));
    g_assert (GTK_IS_APPLICATION (app));

    GObject *menu;
    GtkBuilder *builder;

    builder = gtk_builder_new_from_resource ("/net/bartkessels/getit/menu-app.ui");
    menu = gtk_builder_get_object (builder, "app-menu");

    g_return_if_fail (G_IS_MENU_MODEL (menu));

    g_action_map_add_action_entries (G_ACTION_MAP (app),
                                     app_actions,
                                     G_N_ELEMENTS (app_actions),
                                     app);
    gtk_application_set_app_menu (GTK_APPLICATION (app), G_MENU_MODEL (menu));
    g_object_unref (menu);
}

static void
getit_application_cb_open (GApplication  *app,
                           GFile        **files,
                           gint           n_files,
                           const gchar   *hint)
{
    g_assert (G_IS_APPLICATION (app));

    GtkWindow *window;
    const gchar *file_name;

    window = gtk_application_get_active_window (GTK_APPLICATION (app));
    if (window == NULL)
        window = g_object_new (GETIT_TYPE_WINDOW,
                               "application", app,
                               "default-width", WINDOW_WIDTH,
                               "default-height", WINDOW_HEIGHT,
                               NULL);

    if (n_files > 0) {
        file_name = g_file_get_path (files[0]);

        getit_window_open_file (GETIT_WINDOW (window), file_name);
    }

    gtk_window_present (window);
}

static void
getit_application_cb_recent (GSimpleAction *action,
                             GVariant      *parameter,
                             gpointer       user_data)
{
    g_assert (GETIT_IS_APPLICATION (user_data));

    GetitApplication *self;
    GtkWindow *parent_window;
    GtkRecentManager *recent_manager;
    GtkRecentFilter *recent_filter;
    GtkWidget *recent_chooser_dialog;
    gint recent_chooser_dialog_result;
    const gchar *selected_file;

    self = GETIT_APPLICATION (user_data);
    parent_window = gtk_application_get_active_window (GTK_APPLICATION (self));
    recent_manager = gtk_recent_manager_get_default ();
    recent_filter = gtk_recent_filter_new ();
    gtk_recent_filter_set_name (recent_filter, _("GetIt Files"));
    gtk_recent_filter_add_pattern (recent_filter, "*.getit");
    recent_chooser_dialog = gtk_recent_chooser_dialog_new_for_manager (_("Recent Requests"),
                                                                       parent_window,
                                                                       recent_manager,
                                                                       _("Open Request"), GTK_RESPONSE_ACCEPT,
                                                                       NULL);

    gtk_recent_chooser_add_filter (GTK_RECENT_CHOOSER (recent_chooser_dialog), recent_filter);
    recent_chooser_dialog_result = gtk_dialog_run (GTK_DIALOG (recent_chooser_dialog));
    selected_file = gtk_recent_chooser_get_current_uri (GTK_RECENT_CHOOSER (recent_chooser_dialog));

    gtk_widget_destroy (recent_chooser_dialog);

    if (recent_chooser_dialog_result == GTK_RESPONSE_ACCEPT && selected_file != NULL) {
        selected_file = getit_string_remove (selected_file, "file://");
        getit_window_open_file (GETIT_WINDOW (parent_window), selected_file);
    }
}

static void
getit_application_cb_preferences (GSimpleAction *action,
                                  GVariant      *parameter,
                                  gpointer       user_data)
{
    g_assert (GTK_IS_APPLICATION (user_data));

    GtkApplication *app;
    GtkWindow *window;
    GetitWindowSettings *window_settings;

    app = GTK_APPLICATION (user_data);
    window = gtk_application_get_active_window (app);
    window_settings = getit_window_settings_new (window);

    gtk_window_present (GTK_WINDOW (window_settings));
}

static void
getit_application_cb_about (GSimpleAction *action,
                            GVariant      *parameter,
                            gpointer       user_data)
{
    g_assert (GTK_IS_APPLICATION (user_data));

    GtkApplication *app;
    GtkWindow *window;
    GetitDialogAbout *dialog_about;

    app = GTK_APPLICATION (user_data);
    window = gtk_application_get_active_window (app);
    dialog_about = getit_dialog_about_new (window);

    gtk_dialog_run (GTK_DIALOG (dialog_about));
    gtk_widget_destroy (GTK_WIDGET (dialog_about));
}

static void
getit_application_cb_shortcuts (GSimpleAction *action,
                                GVariant      *parameter,
                                gpointer       user_data)
{
    g_assert (G_IS_APPLICATION (user_data));

    GtkApplication *app;
    GtkWindow *window;
    GetitWindowShortcuts *window_shortcuts;

    app = GTK_APPLICATION (user_data);
    window = gtk_application_get_active_window (app);
    window_shortcuts = getit_window_shortcuts_new (window);

    gtk_window_present (GTK_WINDOW (window_shortcuts));
}

static void
getit_application_cb_quit (GSimpleAction *action,
                           GVariant      *parameter,
                           gpointer       user_data)
{
    g_assert (G_IS_APPLICATION (user_data));

    g_application_quit (G_APPLICATION (user_data));
}
