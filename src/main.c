/*
 * main.c
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
 *
 */

#include <gtk/gtk.h>
#include <libnotify/notify.h>

#include "gi-application.h"

/**
 * main
 *
 * @argc: The number of arguments
 * @argv: The arguments
 *
 * Create a new instance of GiApplication and launch it
 *
 * Return value: int
 */
int main(int argc, char** argv)
{
    GiApplication* application = gi_application_new();
    int status = 0;

    notify_init(APPLICATION_ID);
    status = g_application_run(G_APPLICATION(application), argc, argv);
    notify_uninit();
    g_object_unref(application);

    return status;
}