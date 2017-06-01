Name:		getit
Version:	1.3
Release:	1%{?dist}
Summary:	Send HTTP requests

License:	GPLv3+
URL:		https://github.com/bartkessels/GetIt
Source0:	https://github.com/bartkessels/%{name}/archive/%{version}/%{name}-%{version}.tar.gz

BuildRequires:	gtk3-devel
BuildRequires:	python3-devel
BuildRequires:	automake
BuildRequires:	gettext
BuildRequires:  intltool
BuildRequires:  itstool
BuildRequires:	%{_bindir}/desktop-file-install

Requires:	gtk3
Requires:	pygobject3
Requires:	python3-requests

%description
Application to send HTTP requests to test your own API's

%global debug_package %{nil}

%prep
%autosetup -p1

%build
bash autogen.sh
%configure
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
mkdir -p %{buildroot}%{_datadir}/%{name}/ui
%make_install
desktop-file-install data/package/%{name}.desktop
cp -r data/ui/* %{buildroot}%{_datadir}/%{name}/ui

%files
%license COPYING
%{python3_sitelib}/%{name}
%{_bindir}/%{name}
%{_datadir}/%{name}/ui/*.ui
%{_datadir}/applications/%{name}.desktop

%changelog
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
