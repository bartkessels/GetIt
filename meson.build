project('GetIt', 'c', version: '3.2')

# Imports
gnome = import('gnome')

# Compile resources
giresources = gnome.compile_resources(
	'gi-resources', 'src/getit.gresource.xml',
	source_dir: 'src',
	c_name: 'gi_resources'
)

# Dependencies
deps = [
	dependency('gtk+-3.0'),
	dependency('gdk-3.0'),
	dependency('libsoup-2.4'),
	dependency('gtksourceview-3.0'),
	dependency('gio-2.0'),
	dependency('glib-2.0'),
	dependency('json-glib-1.0'),
	dependency('libnotify')
]

# Source files
src = [
	giresources,
    'src/gi-application.c',
    'src/gi-content-body.c',
    'src/gi-content-cookies.c',
    'src/gi-content-headers.c',
    'src/gi-content-response.c',
    'src/gi-element-cookie.c',
    'src/gi-element-formdata.c',
    'src/gi-element-header-bar.c',
    'src/gi-element-header.c',
    'src/gi-json.c',
    'src/gi-stack.c',
    'src/gi-window-main.c',
    'src/main.c'
]

# Desktop file
install_data('data/package/getit.desktop', install_dir: join_paths(get_option('datadir'), 'applications'))

# Executable information
executable('getit', src, dependencies: deps, install: true)
