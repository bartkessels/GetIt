/* getit-settings.h
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

#include <gio/gio.h>
#include <glib.h>

/* Setting keys */
#define SETTINGS_KEY_SHOW_NOTIFICATIONS "app-show-notifications"
#define SETTINGS_KEY_TIMEOUT "request-timeout"
#define SETTINGS_KEY_USER_AGENT "request-user-agent"

void getit_settings_set_show_notifications (gboolean show_notifications);
void getit_settings_set_timeout (gint timeout);
void getit_settings_set_user_agent (const gchar *user_agent);

gboolean getit_settings_get_show_notifications ();
gint getit_settings_get_timeout ();
const gchar *getit_settings_get_user_agent ();
