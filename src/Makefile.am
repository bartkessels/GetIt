bin_PROGRAMS = getit

gi-resources.c: getit.gresource.xml
		$(AM_V_GEN) \
		glib-compile-resources \
                --sourcedir=$(srcdir) \
				--generate-source \
                --target=$@ \
				$(srcdir)/getit.gresource.xml

BUILT_RESOURCES = \
		gi-resources.c

getit_SOURCES = \
            $(BUILT_RESOURCES) \
            gi-application.c \
            gi-content-body.c \
            gi-content-cookies.c \
            gi-content-headers.c \
            gi-content-response.c \
            gi-element-cookie.c \
            gi-element-formdata.c \
            gi-element-header.c \
            gi-element-header-bar.c \
            gi-stack.c \
            gi-window-main.c \
            main.c

getit_CPPFLAGS = @GTK_CFLAGS@ @GDK_CFLAGS@ @SOURCEVIEW_CFLAGS@ @GIO_CFLAGS@ @GLIB_CFLAGS@ @JSON_CFLAGS@ @SOUP_CFLAGS@ @LIBNOTIFY_CFLAGS@
getit_LDFLAGS = @GTK_LIBS@ @GDK_LIBS@ @SOURCEVIEW_LIBS@ @GIO_LIBS@ @GLIB_LIBS@ @JSON_LIBS@ @SOUP_LIBS@ @LIBNOTIFY_LIBS@
