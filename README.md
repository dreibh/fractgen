# FractalGenerator Project
An extensible Fractal Generator software

<https://www.nntb.no/~dreibh/fractalgenerator/>

## Description

FractalGenerator is a Qt-based program to generate fractal images (e.g. Mandelbrot set). The size of the calculated images is only limited by the computer's virtual memory. That is, images may use the full printer resolution! It is Open Source. I created this program as an example for object-oriented programming and writing Qt applications for our Linux Workshop 2003. The goal of this workshop is to continue this basic application as an Open Source project.

## Screenshots

[Click here to view some screenshots!](https://www.nntb.no/~dreibh/fractalgenerator/pictures.html)

## Binary Package Installation

Please use the issue tracker at [https://github.com/dreibh/fractgen/issues](https://github.com/dreibh/fractgen/issues) to report bugs and issues!

### Ubuntu Linux

For ready-to-install Ubuntu Linux packages of FractalGenerator, see [Launchpad PPA for Thomas Dreibholz](https://launchpad.net/~dreibh/+archive/ubuntu/ppa/+packages?field.name_filter=fractgen&field.status_filter=published&field.series_filter=)!

```
sudo apt-add-repository -sy ppa:dreibh/ppa
sudo apt-get update
sudo apt-get install fractgen
```

### Fedora Linux

For ready-to-install Fedora Linux packages of FractalGenerator, see [COPR PPA for Thomas Dreibholz](https://copr.fedorainfracloud.org/coprs/dreibh/ppa/package/fractgen/)!

```
sudo dnf copr enable -y dreibh/ppa
sudo dnf install fractgen
```

### FreeBSD

For ready-to-install FreeBSD packages of FractalGenerator, it is included in the ports collection, see [FreeBSD ports tree index of graphics/fractgen/](https://cgit.freebsd.org/ports/tree/graphics/fractgen/)!

```
pkg install fractgen
```

Alternatively, to compile it from the ports sources:

```
cd /usr/ports/graphics/fractgen
make
make install
```

## Sources Download

FractalGenerator is released under the GNU General Public Licence (GPL).

Please use the issue tracker at [https://github.com/dreibh/fractgen/issues](https://github.com/dreibh/fractgen/issues) to report bugs and issues!

### Development Version

The Git repository of the FractalGenerator sources can be found at [https://github.com/dreibh/fractgen](https://github.com/dreibh/fractgen):

```
git clone https://github.com/dreibh/fractgen
cd fractgen
cmake .
make
```

Contributions:

- Issue tracker: [https://github.com/dreibh/fractgen/issues](https://github.com/dreibh/fractgen/issues).
  Please submit bug reports, issues, questions, etc. in the issue tracker!

- Pull Requests for FractalGenerator: [https://github.com/dreibh/fractgen/pulls](https://github.com/dreibh/fractgen/pulls).
  Your contributions to FractalGenerator are always welcome!

- CI build tests of FractalGenerator: [https://github.com/dreibh/fractgen/actions](https://github.com/dreibh/fractgen/actions).

- Coverity Scan analysis of FractalGenerator: [https://scan.coverity.com/projects/dreibh-fractgen](https://scan.coverity.com/projects/dreibh-fractgen).

### Current Stable Release

See [https://www.nntb.no/~dreibh/fractalgenerator/#StableRelease](https://www.nntb.no/~dreibh/fractalgenerator/#StableRelease)!
