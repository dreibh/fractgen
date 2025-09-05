<h1 align="center">
 FractGen<br />
 <span style="font-size: 75%">An Extensible Fractal Generator</span><br />
 <a href="https://www.nntb.no/~dreibh/fractalgenerator/">
  <span style="font-size: 75%;">https://www.nntb.no/~dreibh/fractalgenerator</span>
 </a>
</h1>


# 💡 What is FractGen?

FractGen (Fractal Generator) is a Qt/KDE-based program to generate fractal images (e.g.&nbsp;the Mandelbrot set). The size of the calculated images is only limited by the computer's virtual memory. That is, images may use the full printer resolution! I created this program as an example for object-oriented programming and writing Qt/KDE applications for our Linux Workshop&nbsp;2003. The goal of this workshop was to continue this basic application as an Open Source project.


# 😀 Screenshots

[Click here to view some screenshots!](https://www.nntb.no/~dreibh/fractalgenerator/screenshots.html)


# 📦 Binary Package Installation

Please use the issue tracker at [https://github.com/dreibh/fractgen/issues](https://github.com/dreibh/fractgen/issues) to report bugs and issues!

## Ubuntu Linux

For ready-to-install Ubuntu Linux packages of FractGen, see [Launchpad PPA for Thomas Dreibholz](https://launchpad.net/~dreibh/+archive/ubuntu/ppa/+packages?field.name_filter=fractgen&field.status_filter=published&field.series_filter=)!

<pre>
sudo apt-add-repository -sy ppa:dreibh/ppa
sudo apt-get update
sudo apt-get install fractgen
</pre>

## Fedora Linux

For ready-to-install Fedora Linux packages of FractGen, see [COPR PPA for Thomas Dreibholz](https://copr.fedorainfracloud.org/coprs/dreibh/ppa/package/fractgen/)!

<pre>
sudo dnf copr enable -y dreibh/ppa
sudo dnf install fractgen
</pre>

## FreeBSD

For ready-to-install FreeBSD packages of FractGen, it is included in the ports collection, see [FreeBSD ports tree index of benchmarks/fractgen/](https://cgit.freebsd.org/ports/tree/graphics/fractgen/)!

<pre>
pkg install fractgen
</pre>

Alternatively, to compile it from the ports sources:

<pre>
cd /usr/ports/graphics/fractgen
make
make install
</pre>


# 💾 Build from Sources

FractGen is released under the [GNU General Public Licence&nbsp;(GPL)](https://www.gnu.org/licenses/gpl-3.0.en.html#license-text).

Please use the issue tracker at [https://github.com/dreibh/fractgen/issues](https://github.com/dreibh/fractgen/issues) to report bugs and issues!

## Development Version

The Git repository of the FractGen sources can be found at [https://github.com/dreibh/fractgen](https://github.com/dreibh/fractgen):

<pre>
git clone https://github.com/dreibh/fractgen
cd fractgen
cmake .
make
</pre>

Contributions:

* Issue tracker: [https://github.com/dreibh/fractgen/issues](https://github.com/dreibh/fractgen/issues).
  Please submit bug reports, issues, questions, etc. in the issue tracker!

* Pull Requests for FractGen: [https://github.com/dreibh/fractgen/pulls](https://github.com/dreibh/fractgen/pulls).
  Your contributions to FractGen are always welcome!

* CI build tests of FractGen: [https://github.com/dreibh/fractgen/actions](https://github.com/dreibh/fractgen/actions).

* Coverity Scan analysis of FractGen: [https://scan.coverity.com/projects/dreibh-fractgen](https://scan.coverity.com/projects/dreibh-fractgen).

## Release Versions

See [https://www.nntb.no/~dreibh/fractalgenerator/#current-stable-release](https://www.nntb.no/~dreibh/fractalgenerator/#current-stable-release) for release packages!


# 🔗 Useful Links

* [Qt](https://doc.qt.io/)
* [KDE](https://develop.kde.org/)
* [Linux Weekly News](https://lwn.net)
* [Linux.org](https://www.linux.org)
