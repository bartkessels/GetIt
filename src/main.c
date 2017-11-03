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
#include <libnotify/notify.h>

#include "getit-application.h"
#include "getit-config.h"



int
main (int   argc,
      char *argv[])
{
    GetitApplication *app;
    int return_status;

    /* Set up gettext translations */
    bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
    bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
    textdomain (GETTEXT_PACKAGE);

    /* Setup libnotify */
    notify_init (APPLICATION_ID);

    /* Create and launch application */
    app = getit_application_new ();

    return_status = g_application_run (G_APPLICATION (app), argc, argv);

    notify_uninit ();
    g_object_unref (G_OBJECT (app));

    return return_status;
}


