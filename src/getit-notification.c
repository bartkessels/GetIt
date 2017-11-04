/* getit-notification.c
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

#include "getit-notification.h"

void
getit_notification_display (const gchar *title,
                            const gchar *body,
                            const gchar *icon)
{
    gboolean show_notifications;
    GError *error_notification = NULL;
    NotifyNotification *notification;

    show_notifications = getit_settings_get_show_notifications ();

    if (!show_notifications) {
        return;
    }

    notification = notify_notification_new (title, body, icon);
    notify_notification_show (notification, &error_notification);

    if (error_notification != NULL) {
        g_error_free (error_notification);
    }
}
