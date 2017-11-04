/* getit-window.h
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

#pragma once

#include <glib/gi18n.h>
#include <gtk/gtk.h>
#include <libsoup/soup.h>

#include "getit-content-body.h"
#include "getit-dialog-about.h"
#include "getit-messages.h"
#include "getit-notification.h"
#include "getit-settings.h"
#include "getit-stack.h"
#include "getit-json.h"

G_BEGIN_DECLS

#define GETIT_TYPE_WINDOW (getit_window_get_type())

G_DECLARE_FINAL_TYPE (GetitWindow, getit_window, GETIT, WINDOW, GtkApplicationWindow)

/* Window information */
#define WINDOW_TITLE "GetIt"
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 600

/* Public function signatures */
GetitWindow *getit_window_new (GApplication *app);
void getit_window_set_title (GetitWindow *self,
                             const gchar *title);
void getit_window_set_subtitle (GetitWindow *self,
                                const gchar *subtitle);
void getit_window_save_file (GetitWindow *self,
                             const gchar *file_name);
void getit_window_open_file (GetitWindow *self,
                             const gchar *file_name);

G_END_DECLS
