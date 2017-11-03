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
  'getit-stack.c',
  'getit-window.c',
  'getit-window-shortcuts.c',
  'main.c'
]

getit_deps = [
  dependency('gio-2.0', version: '>= 2.50'),
  dependency('gtk+-3.0', version: '>= 3.22'),
  dependency('libsoup-2.4', version: '>= 2.40'),
  dependency('gtksourceview-3.0', version: '>= 3.22'),
  dependency('json-glib-1.0')
]

gnome = import('gnome')

getit_sources += gnome.compile_resources('getit-resources',
  'getit.gresource.xml',
  c_name: 'getit'
)

executable('getit', getit_sources,

  dependencies: getit_deps,
  install: true,
)
