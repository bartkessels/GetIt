/* getit-settings.c
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

#include "getit-settings.h"

/*
 * =============================================================================
 * Signatures
 *
 */
static GSettings *getit_settings_get_g_settings ();

 /*
 * =============================================================================
 * Public function implementations
 *
 */
void
getit_settings_set_show_notifications (gboolean show_notifications)
{
    GSettings *settings;

    settings = getit_settings_get_g_settings ();

    g_settings_set_boolean (settings, SETTINGS_KEY_SHOW_NOTIFICATIONS, show_notifications);
}

void
getit_settings_set_show_recents_on_startup (gboolean show_recents_on_startup)
{
    GSettings *settings;

    settings = getit_settings_get_g_settings ();

    g_settings_set_boolean (settings, SETTINGS_KEY_SHOW_RECENTS_ON_STARTUP, show_recents_on_startup);
}

void
getit_settings_set_timeout (gint timeout)
{
    GSettings *settings;

    settings = getit_settings_get_g_settings ();

    g_settings_set_int (settings, SETTINGS_KEY_TIMEOUT, timeout);
}

void
getit_settings_set_user_agent (const gchar *user_agent)
{
    GSettings *settings;

    settings = getit_settings_get_g_settings ();

    g_settings_set_string (settings, SETTINGS_KEY_USER_AGENT, user_agent);
}

void
getit_settings_set_divider_value (const gint divider_value)
{
    GSettings *settings;

    settings = getit_settings_get_g_settings ();

    g_settings_set_int (settings, SETTINGS_KEY_DIVIDER_VALUE, divider_value);
}

gboolean
getit_settings_get_show_notifications ()
{
    GSettings *settings;
    gboolean show_notifications;

    settings = getit_settings_get_g_settings ();
    show_notifications = g_settings_get_boolean (settings, SETTINGS_KEY_SHOW_NOTIFICATIONS);

    return show_notifications;
}

gboolean
getit_settings_get_show_recents_on_startup ()
{
    GSettings *settings;
    gboolean show_recents_on_startup;

    settings = getit_settings_get_g_settings ();
    show_recents_on_startup = g_settings_get_boolean (settings, SETTINGS_KEY_SHOW_RECENTS_ON_STARTUP);

    return show_recents_on_startup;
}

gint
getit_settings_get_timeout ()
{
    GSettings *settings;
    gint timeout;

    settings = getit_settings_get_g_settings ();
    timeout = g_settings_get_int (settings, SETTINGS_KEY_TIMEOUT);

    return timeout;
}

const gchar *
getit_settings_get_user_agent ()
{
    GSettings *settings;
    const gchar *user_agent;

    settings = getit_settings_get_g_settings ();
    user_agent = g_settings_get_string (settings, SETTINGS_KEY_USER_AGENT);

    return user_agent;
}

gint
getit_settings_get_divider_value ()
{
    GSettings *settings;
    gint divider_value;

    settings = getit_settings_get_g_settings ();
    divider_value = g_settings_get_int (settings, SETTINGS_KEY_DIVIDER_VALUE);

    return divider_value;
}

 /*
 * =============================================================================
 * Private function implementations
 *
 */
static GSettings *
getit_settings_get_g_settings ()
{
    GSettings *settings;

    settings = g_settings_new ("net.bartkessels.getit");

    return settings;
}
