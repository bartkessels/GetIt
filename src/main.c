/* main.c
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

#include <glib/gi18n.h>

#include "getit-config.h"
#include "getit-window.h"
#include "getit-window-shortcuts.h"


static void on_activate (GtkApplication *app);
static void on_startup (GtkApplication *app);
static void cb_about (GSimpleAction *action,
                      GVariant      *parameter,
                      gpointer       user_data);
static void cb_shortcuts (GSimpleAction *action,
                          GVariant      *parameter,
                          gpointer       user_data);
static void cb_quit (GSimpleAction *action,
                     GVariant      *parameter,
                     gpointer       user_data);

/* App menu entries */
const GActionEntry app_actions[] = {
        { "about", cb_about },
        { "shortcuts", cb_shortcuts },
        { "quit", cb_quit }
};

int
main (int   argc,
      char *argv[])
{
    GtkApplication *app;
    int return_status;

    /* Set up gettext translations */
    bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
    bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
    textdomain (GETTEXT_PACKAGE);

    /* Create and launch application */
    app = gtk_application_new ("net.bartkessels.getit", G_APPLICATION_FLAGS_NONE);

    g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);
    g_signal_connect (app, "startup", G_CALLBACK (on_startup), NULL);

    return_status = g_application_run (G_APPLICATION (app), argc, argv);

    return return_status;
}

static void
on_activate (GtkApplication *app)
{
    g_assert (GTK_IS_APPLICATION (app));

    GtkWindow *window;

    /* Get the current window or create one if necessary. */
    window = gtk_application_get_active_window (app);
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
on_startup (GtkApplication *app)
{
    g_assert (GTK_IS_APPLICATION (app));

    GObject *menu;
    GtkBuilder *builder;

    builder = gtk_builder_new_from_resource ("/net/bartkessels/getit/menu-app.ui");
    menu = gtk_builder_get_object (builder, "app-menu");

    g_assert (G_IS_MENU_MODEL (menu));

    g_action_map_add_action_entries (G_ACTION_MAP (app),
                                     app_actions,
                                     G_N_ELEMENTS (app_actions),
                                     app);
    gtk_application_set_app_menu (app, G_MENU_MODEL (menu));
    g_object_unref (menu);
}

static void
cb_about (GSimpleAction *action,
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
cb_shortcuts (GSimpleAction *action,
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
cb_quit (GSimpleAction *action,
         GVariant      *parameter,
         gpointer       user_data)
{
    g_assert (G_IS_APPLICATION (user_data));

    g_application_quit (G_APPLICATION (user_data));
}
