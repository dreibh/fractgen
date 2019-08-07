Name: fractgen
Version: 2.1.7
Release: 1
Summary: Fractal Generator
Group: Applications/Multimedia
License: GPL-3+
URL: https://www.uni-due.de/~be0001/fractalgenerator/
Source: https://www.uni-due.de/~be0001/fractalgenerator/download/%{name}-%{version}.tar.xz

AutoReqProv: on
BuildRequires: cmake
BuildRequires: qt5-qtbase-devel
BuildRoot: %{_tmppath}/%{name}-%{version}-build


%description
FractGen is a simple Qt-based fractal generator program for Mandelbrot fractals. The image size is only limited by virtual memory. It is possible to zoom into images. Image parameters can be saved in XML files and loaded from XML files. Calculated images can be exported as PNG files. The intention of this program is to generate graphics to be post-processed by other image tools, e.g. in order to generate nice screen backgrounds or book covers.

%global debug_package %{nil}

%prep
%setup -q

%build
%cmake -DCMAKE_INSTALL_PREFIX=/usr .
make %{?_smp_mflags}

%install
make DESTDIR=%{buildroot} install

%files
%{_bindir}/fractgen
%{_datadir}/fractgen/examples/*.fsf
%{_mandir}/man1/fractgen.1.gz


%changelog
* Wed Aug 07 2019 Thomas Dreibholz <dreibh@iem.uni-due.de> - 2.1.7
- New upstream release.
* Fri Jul 26 2019 Thomas Dreibholz <dreibh@iem.uni-due.de> - 2.1.6
- New upstream release.
* Tue May 21 2019 Thomas Dreibholz <dreibh@iem.uni-due.de> - 2.1.5
- New upstream release.
* Wed Aug 09 2018 Thomas Dreibholz <dreibh@iem.uni-due.de> 2.0.16
- Created RPM package.
