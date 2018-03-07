config_h = configuration_data()
config_h.set_quoted('GETTEXT_PACKAGE', 'getit')
config_h.set_quoted('LOCALEDIR', join_paths(get_option('prefix'), get_option('localedir')))

getit_sources = [
  'getit-application.c',
  'getit-content-body.c',
  'getit-content-cookies.c',
  'getit-content-headers.c',
  'getit-content-response.c',
  'getit-dialog-about.c',
  'getit-element-cookie.c',
  'getit-element-formdata.c',
  'getit-element-header.c',
  'getit-json.c',
  'getit-notification.c',
  'getit-settings.c',
  'getit-stack.c',
  'getit-string.c',
  'getit-window.c',
  'getit-window-settings.c',
  'getit-window-shortcuts.c',
  'main.c'
]

# Required dependencies
getit_deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('glib-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
  dependency('libsoup-2.4', version: '>= 2.40'),
  dependency('gtksourceview-3.0', version: '>= 3.22'),
  dependency('libnotify', version: '>= 0.7.6'),
  dependency('json-glib-1.0', version: '>= 1.2')
]

# Optional dependencies
webkit_dep = dependency('webkit2gtk-4.0', version: '>= 2.18.5', required: false)

if webkit_dep.found()
	config_h.set('WEBKIT2_AVAILABLE', 'TRUE')
	getit_deps += webkit_dep
endif

gnome = import('gnome')

getit_sources += gnome.compile_resources('getit-resources',
  'getit.gresource.xml',
  c_name: 'getit'
)

configure_file(
	output: 'getit-config.h',
	configuration: config_h,
)

executable('getit', getit_sources,

  dependencies: getit_deps,
  install: true,
)
