/* getit-application.h
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

#pragma once

#include <gtk/gtk.h>

#include "getit-window.h"
#include "getit-window-shortcuts.h"

/* Application information */
#define APPLICATION_ID "net.bartkessels.getit"

G_BEGIN_DECLS

#define GETIT_TYPE_APPLICATION (getit_application_get_type())

G_DECLARE_FINAL_TYPE (GetitApplication, getit_application, GETIT, APPLICATION, GtkApplication);

/* Public function signatures */
GetitApplication *getit_application_new ();

G_END_DECLS
