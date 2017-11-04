/* getit-window-shortcuts.c
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

#include "getit-window-shortcuts.h"

struct _GetitWindowShortcuts {
	GtkShortcutsWindow parent_instance;
};

G_DEFINE_TYPE (GetitWindowShortcuts, getit_window_shortcuts, GTK_TYPE_SHORTCUTS_WINDOW)

/*
 * =============================================================================
 * Signatures
 *
 */
 static void getit_window_shortcuts_class_init (GetitWindowShortcutsClass *klass);
 static void getit_window_shortcuts_init (GetitWindowShortcuts *self);

 /*
 * =============================================================================
 * Public function implementations
 *
 */
GetitWindowShortcuts *
getit_window_shortcuts_new (GtkWindow *parent_window)
{
    g_assert (GTK_IS_WINDOW (parent_window));

    GetitWindowShortcuts *window_shortcuts;

    window_shortcuts = g_object_new (GETIT_TYPE_WINDOW_SHORTCUTS,
                                     "transient-for", parent_window,
                                     NULL);

    return window_shortcuts;
}

 /*
 * =============================================================================
 * Private function implementations
 *
 */
 static void
getit_window_shortcuts_class_init (GetitWindowShortcutsClass *klass)
{
    GtkWidgetClass *widget_class;

    widget_class = GTK_WIDGET_CLASS (klass);

    gtk_widget_class_set_template_from_resource (widget_class, "/net/bartkessels/getit/window-shortcuts.ui");
}

 static void
getit_window_shortcuts_init (GetitWindowShortcuts *self)
{
    g_assert (GTK_IS_WIDGET (self));

    gtk_widget_init_template (GTK_WIDGET (self));
}
