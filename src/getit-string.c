/* getit-string.c
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

#include "getit-string.h"

const gchar *
getit_string_remove (const gchar *complete_string,
                     const char  *remove_string)
{
    g_assert_nonnull (complete_string);
    g_assert_nonnull (remove_string);

    gchar **splitted_string;
    gint splitted_string_index;
    const gchar *new_string;

    splitted_string_index = 0;
    new_string = "";

    /* Split string on the string to replace characters */
    splitted_string = g_strsplit (complete_string, remove_string, 2);

    while (splitted_string[splitted_string_index] != NULL) {
        new_string = g_strconcat (new_string,
                                  splitted_string[splitted_string_index],
                                  NULL);

        splitted_string_index++;
    }

    if (strlen (new_string) < 1) {
        return complete_string;
    }

    return new_string;
}
