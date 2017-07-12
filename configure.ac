#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([GetIt], [3.1], [https://github.com/bartkessels/getit])
AC_CONFIG_SRCDIR([src/main.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
PKG_CHECK_MODULES([GTK], gtk+-3.0)
PKG_CHECK_MODULES([GDK], gdk-3.0)
PKG_CHECK_MODULES([SOURCEVIEW], gtksourceview-3.0)
PKG_CHECK_MODULES([GIO], gio-2.0)
PKG_CHECK_MODULES([GLIB], glib-2.0)
PKG_CHECK_MODULES([JSON], json-glib-1.0)
PKG_CHECK_MODULES([SOUP], libsoup-2.4)
PKG_CHECK_MODULES([LIBNOTIFY], libnotify)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 data/Makefile
                 src/Makefile])
AC_OUTPUT
