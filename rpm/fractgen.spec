Name: fractgen
Version: 2.1.2
Release: 1
Summary: Fractal Generator
Group: Applications/Multimedia
License: GPLv3
URL: https://www.uni-due.de/~be0001/fractalgenerator/
Source: https://www.uni-due.de/~be0001/fractalgenerator/download/%{name}-%{version}.tar.gz

AutoReqProv: on
BuildRequires: qt5-qtbase-devel
BuildRequires: qtchooser
BuildRoot: %{_tmppath}/%{name}-%{version}-build

%define _unpackaged_files_terminate_build 0

%description
FractGen is a simple Qt-based fractal generator program for Mandelbrot fractals. The image size is only limited by virtual memory. It is possible to zoom into images. Image parameters can be saved in XML files and loaded from XML files. Calculated images can be exported as PNG files. The intention of this program is to generate graphics to be post-processed by other image tools, e.g. in order to generate nice screen backgrounds or book covers.

%global debug_package %{nil}

%prep
%setup -q

%build
qtchooser -qt=5 -run-tool=qmake
make %{?_smp_mflags}

%install
mkdir -p %{buildroot}%{_bindir}/
install -m 755 -p %{_builddir}/%{buildsubdir}/src/fractgen %{buildroot}%{_bindir}/

%files
%{_bindir}/fractgen

%changelog
* Wed Aug 09 2017 Thomas Dreibholz <dreibh@iem.uni-due.de> 2.0.16
- Created RPM package.
