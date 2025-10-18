Name: fractgen
Version: 3.0.6
Release: 1
Summary: Fractal Generator
Group: Applications/Multimedia
License: GPL-3.0-or-later
URL: https://www.nntb.no/~dreibh/fractalgenerator/
Source: https://www.nntb.no/~dreibh/fractalgenerator/download/%{name}-%{version}.tar.xz

AutoReqProv: on
BuildRequires: cmake
BuildRequires: extra-cmake-modules
BuildRequires: kf6-kcoreaddons-devel
BuildRequires: kf6-kxmlgui-devel
BuildRequires: qt6-linguist
BuildRequires: qt6-qtbase-devel
BuildRoot: %{_tmppath}/%{name}-%{version}-build

Requires: %{name}-common = %{version}-%{release}
Recommends: %{name}-examples = %{version}-%{release}
Recommends: rsplib-tools


%description
FractGen is a simple Qt-based fractal generator program for Mandelbrot
fractals. The image size is only limited by virtual memory. It is possible
to zoom into images. Image parameters can be saved in XML files and loaded
from XML files. Calculated images can be exported as PNG files.
The intention of this program is to generate graphics to be post-processed
by other image tools, e.g. in order to generate nice screen backgrounds or
book covers.
This is the Qt version of FractGen.

%prep
%setup -q

%build
%cmake -DCMAKE_INSTALL_PREFIX=/usr . -DWITH_KDE=1
%cmake_build

%install
%cmake_install

%files
%{_bindir}/fractgen
%{_datadir}/applications/fractgen.desktop
%{_datadir}/bash-completion/completions/fractgen
%{_mandir}/man1/fractgen.1.gz


%package kfractgen
Summary: FractGen Fractal Generator (KDE version)
Group: Applications/Multimedia
Requires: %{name}-common = %{version}-%{release}
Recommends: %{name}-examples = %{version}-%{release}
Recommends: rsplib-tools

%description kfractgen
FractGen is a simple Qt-based fractal generator program for Mandelbrot
fractals. The image size is only limited by virtual memory. It is possible
to zoom into images. Image parameters can be saved in XML files and loaded
from XML files. Calculated images can be exported as PNG files.
The intention of this program is to generate graphics to be post-processed
by other image tools, e.g. in order to generate nice screen backgrounds or
book covers.
This is the KDE version of FractGen.

%files kfractgen
%{_bindir}/kfractgen
%{_datadir}/applications/kfractgen.desktop
%{_datadir}/bash-completion/completions/kfractgen
%{_mandir}/man1/kfractgen.1.gz


%package clifractgen
Summary: FractGen Fractal Generator (command-line) version)
Group: Applications/Multimedia
Requires: %{name}-common = %{version}-%{release}
Recommends: %{name}-examples = %{version}-%{release}
Suggests: rsplib-tools

%description clifractgen
FractGen is a simple Qt-based fractal generator program for Mandelbrot
fractals. The image size is only limited by virtual memory. It is possible
to zoom into images. Image parameters can be saved in XML files and loaded
from XML files. Calculated images can be exported as PNG files.
The intention of this program is to generate graphics to be post-processed
by other image tools, e.g. in order to generate nice screen backgrounds or
book covers.
This is the KDE version of FractGen.

%files clifractgen
%{_bindir}/clifractgen
%{_datadir}/bash-completion/completions/clifractgen
%{_mandir}/man1/clifractgen.1.gz


%package common
Summary: FractGen common files
Group: Applications/Multimedia
BuildArch: noarch

%description common
FractGen is a simple Qt-based fractal generator program for Mandelbrot
fractals. The image size is only limited by virtual memory. It is possible
to zoom into images. Image parameters can be saved in XML files and loaded
from XML files. Calculated images can be exported as PNG files.
The intention of this program is to generate graphics to be post-processed
by other image tools, e.g. in order to generate nice screen backgrounds or
book covers.
This package contains common files for the Qt, KDE and command-line
versions of FractGen.

%files common
%{_datadir}/fractgen/*.qm
%{_datadir}/icons/hicolor/512x512/apps/fractgen.png
%{_datadir}/mime/packages/fractgen.xml


%package example
Summary: FractGen example files
Group: Applications/Multimedia
BuildArch: noarch

%description example
This package contains some example input files for the fractal generator
program FractGen. The example files contain the parameters for the
fractal calculations. FractGen can perform the computations and display
the resulting images.

%files example
%{_datadir}/fractgen/examples/*.fsf


%changelog
* Sun Sep 21 2025 Thomas Dreibholz <thomas.dreibholz@gmail.com> - 3.0.6-1
- New upstream release.
* Sat Jul 05 2025 Thomas Dreibholz <thomas.dreibholz@gmail.com> - 3.0.5
- New upstream release.
* Mon May 19 2025 Thomas Dreibholz <thomas.dreibholz@gmail.com> - 3.0.4
- New upstream release.
* Mon May 12 2025 Thomas Dreibholz <thomas.dreibholz@gmail.com> - 3.0.3
- New upstream release.
* Fri Dec 20 2024 Thomas Dreibholz <thomas.dreibholz@gmail.com> - 3.0.2
- New upstream release.
* Wed Dec 18 2024 Thomas Dreibholz <thomas.dreibholz@gmail.com> - 3.0.1
- New upstream release.
* Fri Dec 13 2024 Thomas Dreibholz <thomas.dreibholz@gmail.com> - 3.0.0
- New upstream release.
* Fri Dec 13 2024 Thomas Dreibholz <thomas.dreibholz@gmail.com> - 2.2.0
- New upstream release.
* Wed Dec 06 2023 Thomas Dreibholz <thomas.dreibholz@gmail.com> - 2.1.14
- New upstream release.
* Sun Jan 22 2023 Thomas Dreibholz <thomas.dreibholz@gmail.com> - 2.1.13
- New upstream release.
* Fri Nov 12 2021 Thomas Dreibholz <dreibh@iem.uni-due.de> - 2.1.12
- New upstream release.
* Sat Mar 06 2021 Thomas Dreibholz <dreibh@iem.uni-due.de> - 2.1.11
- New upstream release.
* Fri Nov 13 2020 Thomas Dreibholz <dreibh@iem.uni-due.de> - 2.1.10
- New upstream release.
* Fri Apr 24 2020 Thomas Dreibholz <dreibh@iem.uni-due.de> - 2.1.9
- New upstream release.
* Fri Feb 07 2020 Thomas Dreibholz <dreibh@iem.uni-due.de> - 2.1.8
- New upstream release.
* Wed Aug 07 2019 Thomas Dreibholz <dreibh@iem.uni-due.de> - 2.1.7
- New upstream release.
* Fri Jul 26 2019 Thomas Dreibholz <dreibh@iem.uni-due.de> - 2.1.6
- New upstream release.
* Tue May 21 2019 Thomas Dreibholz <dreibh@iem.uni-due.de> - 2.1.5
- New upstream release.
* Wed Aug 09 2018 Thomas Dreibholz <dreibh@iem.uni-due.de> 2.0.16
- Created RPM package.
