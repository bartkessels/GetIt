project('getit','c',
	version: '4.0.7',
	meson_version: '>= 0.40.0',
)
i18n = import('i18n')

add_project_arguments([
	'-I' + meson.build_root(),
], language: 'c')

subdir('data')
subdir('src')
subdir('po')

meson.add_install_script('build-aux/meson/postinstall.py')
