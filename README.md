# FractalGenerator Project
An extensible Fractal Generator software

<https://www.nntb.no/~dreibh/fractalgenerator/>

## Description

FractalGenerator is a Qt-based program to generate fractal images (e.g. Mandelbrot set). The size of the calculated images is only limited by the computer's virtual memory. That is, images may use the full printer resolution! It is Open Source. I created this program as an example for object-oriented programming and writing Qt applications for our Linux Workshop 2003. The goal of this workshop is to continue this basic application as an Open Source project.

## Screenshots

[Click here to view some screenshots!](https://www.nntb.no/~dreibh/fractalgenerator/pictures.html)

## Binary Package Installation

Please use the issue tracker at https://github.com/dreibh/fractgen/issues to report bugs and issues!

### Ubuntu Linux

For ready-to-install Ubuntu Linux packages of FractalGenerator, see Launchpad PPA for Thomas Dreibholz!

```
sudo apt-add-repository -sy ppa:dreibh/ppa
sudo apt-get update
sudo apt-get install fractgen
```

### Fedora Linux

For ready-to-install Fedora Linux packages of FractalGenerator, see COPR PPA for Thomas Dreibholz!

```
sudo dnf copr enable -y dreibh/ppa
sudo dnf install fractgen
```

### FreeBSD

For ready-to-install FreeBSD packages of FractGen, it is included in the ports collection, see Index of /head/graphics/fractgen/!

    pkg install fractgen

Alternatively, to compile it from the ports sources:

```
cd /usr/ports/graphics/fractgen
make
make install
```

## Sources Download

FractalGenerator is released under the GNU General Public Licence (GPL).

Please use the issue tracker at https://github.com/dreibh/fractgen/issues to report bugs and issues!

### Development Version

The Git repository of the FractalGenerator sources can be found at https://github.com/dreibh/fractgen:

- Issue tracker: https://github.com/dreibh/fractgen/issues.
  Please submit bug reports, issues, questions, etc. in the issue tracker!

- Pull Requests for FractalGenerator: https://github.com/dreibh/fractgen/pulls.
  Your contributions to FractalGenerator are always welcome!

- Travis CI automated build tests of FractalGenerator: https://travis-ci.org/dreibh/fractgen.

- Coverity Scan analysis of FractalGenerator: https://scan.coverity.com/projects/dreibh-fractgen.

### Current Stable Release

The tarball has been signed with my GnuPG key DF605BB0760F2D65. Its authenticity and integrity can be verified by:

gpg --keyserver hkp://keyserver.ubuntu.com --recv-keys DF605BB0760F2D65
gpg --verify fractgen-VERSION.tar.xz.asc fractgen-VERSION.tar.xz

- [fractgen-2.1.7.tar.xz (Tar/XZ file)](https://www.nntb.no/~dreibh/fractalgenerator/download/fractgen-2.1.7.tar.xz)
- [fractgen-2.1.7.tar.xz.asc (Signature)](https://www.nntb.no/~dreibh/fractalgenerator/download/fractgen-2.1.7.tar.xz.asc)

## Requirements

- Linux or FreeBSD (other OS should work too)
- Qt 5.x development package

07.08.2019 Thomas Dreibholz, University of Duisburg-Essen / Institute for Experimental Mathematics / Computer Networking Technology Group
