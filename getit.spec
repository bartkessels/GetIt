Name:		GetIt
Version:	1.0
Release:	1%{?dist}
Summary:	Send HTTP requests

License:	GPLv3+
URL:		https://github.com/bartkessels/GetIt
Source0:	https://github.com/bartkessels/%{name}/archive/%{version}/%{name}-%{version}.tar.gz

BuildRequires:	gtk3-devel
BuildRequires:	python3

Requires:	gtk3
Requires:	pygobject3
Requires:	python3-requests

%description
Application to send HTTP requests to test your own API's

%build
%configure
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
%make_install
desktop-file-install data/package/%{name}.desktop
cp data/mainwindow.ui %{buildroot}%{_datadir}/getit.ui

%files
%{_bindir}/getit
%{_prefix}/lib/python3.5/site-packages/getit
%{_datadir}/getit.ui
%{_datadir}/applications/%{name}.desktop

%changelog
* Wed Mar 29 2017 Bart Kessels <bartkessels@outlook.com> - 1-1
- Initial Packaging
