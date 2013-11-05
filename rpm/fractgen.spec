Name: fractgen
Version: 2.0.16
Release: 1%{?dist}
Summary: Fractal Generator
Group: Productivity/Graphics/Visualization/Other
License: GPLv3
Source: %{name}-%{version}.tar.gz
URL: http://www.iem.uni-due.de/~dreibh/fractalgenerator/download/fractgen-2.0.16.tar.gz

AutoReqProv: on
BuildRequires: qt-devel

%define _unpackaged_files_terminate_build 0

%description
FractGen is a simple Qt-based fractal generator program for Mandelbrot fractals. The image size is only limited by virtual memory. It is possible to zoom into images. Image parameters can be saved in XML files and loaded from XML files. Calculated images can be exported as PNG files. The intention of this program is to generate graphics to be post-processed by other image tools, e.g. in order to generate nice screen backgrounds or book covers.

%prep
%setup -q


%build
qmake-qt4 -makefile
make %{?_smp_mflags} PREFIX=%{buildroot}

%install
make PREFIX=%{buildroot} install

%files
%{_bindir}/fractgen

%changelog
* Thu Sep 26 2013 Thomas Dreibholz <dreibh@iem.uni-due.de> - 2.0.16
- Created RPM package.
