Name:		GetIt
Version:	1
Release:	1%{?dist}
URL:		https://github.com/bartkessels/GetIt
Summary:	Send HTTP requests
License:	GPLv3+

BuildRequires:	gtk3-devel

%description
Application to send HTTP requests to test your own API's

%build
%configure
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
%make_install
desktop-file-install data/package/getit.desktop
cp data/mainwindow.ui %{buildroot}%{_datadir}/getit.ui
# Change mainwindow.ui file path in all python files
find %{buildroot} -type f -exec sed -i 's|UI_FILE = ".*"|UI_FILE = "/usr/share/getit.ui"|g' {} \;

%files
%{_bindir}/getit
%{_prefix}/lib/python3.5/site-packages/getit
%{_datadir}/getit.ui
%{_datadir}/applications/getit.desktop

%changelog
* Wed Mar 29 2017 Bart Kessels <bartkessels@outlook.com> - 1-1
- Initial Packaging
