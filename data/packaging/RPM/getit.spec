Name:			getit
Version:		4.0.7
Release:		1%{?dist}
Summary:		Send HTTP requests to your API endpoints

License:		GPLv3+
URL:			https://getit.bartkessels.net
Source0:		https://github.com/bartkessels/%{name}/archive/%{version}.tar.gz

BuildRequires:		gcc
BuildRequires:		meson
BuildRequires:		gtk3-devel
BuildRequires:		gtksourceview3-devel
BuildRequires:		json-glib-devel
BuildRequires:		glib-devel
BuildRequires:		libsoup-devel
BuildRequires:		libnotify-devel
BuildRequires:		gettext
BuildRequires:		webkitgtk4-devel

Requires:		gtk3
Requires:		gtksourceview3
Requires:		json-glib
Requires:		glib
Requires:		libsoup
Requires:		libnotify
Requires:		webkitgtk4

%description
Application to send HTTP requests to test your own API endpoints

%global debug_package %{nil}

%prep
%autosetup -p1

%build
%meson
%meson_build

%install
rm -rf $RPM_BUILD_ROOT
%meson_install
%find_lang %{name}

%files -f %{name}.lang
%{_bindir}/%{name}
%{_datadir}/applications/net.bartkessels.%{name}.desktop
%{_datadir}/glib-2.0/schemas/net.bartkessels.%{name}.gschema.xml
%{_datadir}/mime/packages/net.bartkessels.%{name}.xml
%{_datadir}/appdata/net.bartkessels.%{name}.appdata.xml
%{_datadir}/icons/hicolor/*/apps/net.bartkessels.%{name}.png
%{_datadir}/icons/hicolor/*/apps/net.bartkessels.%{name}-symbolic.png
%{_datadir}/icons/hicolor/*/actions/%{name}-remove-symbolic.png

%changelog
* Sat Feb 03 2018 Bart Kessels <bartkessels@bk-mail.com> 4.0.7
- Add option to disable X.509 certificate check
- Update appstream translations

* Mon Jan 29 2018 Bart Kessels <bartkessels@bk-mail.com> 4.0.6
- Updated save and open file dialogs
- Update Dutch translation desktop and appstream file

* Wed Jan 24 2018 Bart Kessels <bartkessels@bk-mail.com> 4.0.5
- Save state of divider between headers and output in response stack
- Make response headers selectable

* Tue Jan 23 2018 Bart Kessels <bartkessels@bk-mail.com> 4.0.4
- Update scrollviews
- Add ability to enlarge headers on response

* Tue Jan 23 2018 Bart Kessels <bartkessels@bk-mail.com> 4.0.3.1
- Update Dutch translations

* Tue Jan 23 2018 Bart Kessels <bartkessels@bk-mail.com> 4.0.3
- Add view for HTML preview
- Automatically make JSON view readable

* Fri Jan 19 2018 Bart Kessels <bartkessels@bk-mail.com> 4.0.2
- Clear headerbar when clearing a request
- Fix bug showing syntax highlighting

* Mon Nov 06 2017 Bart Kessels <bartkessels@bk-mail.com> 4.0.1
- Update .desktop file actions menu
- Ship own icons

* Sat Nov 04 2017 Bart Kessels <bartkessels@bk-mail.com> 4.0
- Add recent files support
- Add ability to set timeout for request
- Add ability to set user agent for request
- Add preferences window
- Add shortcuts window
- Add support for translations
- Add support for flatpak

* Tue Sep 05 2017 Bart Kessels <bartkessels@bk-mail.com> 3.2
- Fix non-highlighting bug in response
- Fix bug application crash on re-save

* Sun Aug 13 2017 Bart Kessels <bartkessels@bk-mail.com> 3.1
- Move to Meson build system
- Allow opening files at startup

* Tue Jul 11 2017 Bart Kessels <bartkessels@bk-mail.com> 3.0
- Rewrite application to C

* Sat Jun 17 2017 Bart Kessels <bartkessels@outlook.com> 2.0-1
- Display message when something has wrong while sending the request
- Add ability to save a request
- Add ability to open a request
- Add ability to clear the current request

* Sun Jun 11 2017 Bart Kessels <bartkessels@outlook.com> 1.4.1-1
- Add cancel request button
- Add shortcuts for send and cancel button
- Display notification when request is processed

* Fri Jun 9 2017 Bart Kessels <bartkessels@outlook.com> 1.4-1
- Add spinner to indicate the request is still being sent
- Add shortcut to send request

* Thu Jun 1 2017 Bart Kessels <bartkessels@outlook.com> 1.3-1
- Refactor codebase
- Add ability to create raw body instead of form-data

* Fri Apr 7 2017 Bart Kessels <bartkessels@outlook.com> 1.2-1
- Add ability to add cookies to a requests
- Fix endless scrolling bug on response stack

* Fri Mar 31 2017 Bart Kessels <bartkessels@outlook.com> 1.1-1
- Add ability to add files to request

* Wed Mar 29 2017 Bart Kessels <bartkessels@outlook.com> - 1.0-1
- Initial Packaging

