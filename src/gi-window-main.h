/*
 * gi-window-main.h
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

#ifndef GI_WINDOW_MAIN_H
#define GI_WINDOW_MAIN_H

#include <glib-object.h>
#include <gtk/gtk.h>
#include <libsoup/soup.h>

#include "gi-application.h"
#include "gi-element-header-bar.h"
#include "gi-stack.h"

#define APPLICATION_TITLE "GetIt"

G_BEGIN_DECLS

typedef struct _GiWindowMain GiWindowMain;

#define GI_TYPE_WINDOW_MAIN gi_window_main_get_type()
G_DECLARE_FINAL_TYPE(GiWindowMain, gi_window_main, GI, WINDOW_MAIN, GtkApplicationWindow)

struct _GiWindowMain {
    GtkApplicationWindow parent;

    /*
        Member Variables
    */
    SoupSession* session;
    GiStack* stack;
    GtkWidget*  lbl_file;

    GiElementHeaderBar* header_bar;

    gboolean request_cancelled;
};

/*
    Methods
*/
GiWindowMain* gi_window_main_new(GiApplication* application);

G_END_DECLS

#endif /* GI_WINDOW_MAIN_H */