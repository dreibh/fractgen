<h1 align="center">
 FractGen<br />
 <span style="font-size: 75%">An Extensible Fractal Generator</span><br />
 <a href="https://www.nntb.no/~dreibh/fractalgenerator/">
  <span style="font-size: 75%;">https://www.nntb.no/~dreibh/fractalgenerator</span>
 </a>
</h1>


# 💡 What is FractGen?

FractGen (Fractal Generator) is a Qt/KDE-based program to generate fractal images (e.g.&nbsp;the Mandelbrot set). The size of the calculated images is only limited by the computer's virtual memory. That is, images may use the full printer resolution! I created this program as an example for object-oriented programming and writing Qt/KDE applications for our Linux Workshop&nbsp;2003. The goal of this workshop was to continue this basic application as an Open Source project.

The package consists of 3&nbsp;programs:

- [FractGen](#fractgen) (Qt version of the FractGen),
- [KFractGen](#kfractgen) (KDE version of the FractGen),
- [CLIFractGen](#clifractgen) (command-line version of the FractGen),


# 📚 FractGen

FractGen is the [Qt](https://doc.qt.io/) version of the fractal generator program. That is, it provides a Qt-based GUI.
It can simply be started via the GUI menu (depending on the desktop environment), or from the command-line:

<pre>
fractgen
</pre>

Alternatively, it is also possible to specify one or more input files (e.g.&nbsp;<tt>[alpha01.fsf](src/examples/alpha01.fsf)</tt>, <tt>[beta04.fsf](src/examples/beta04.fsf)</tt>, <tt>[delta07.fsf](src/examples/delta07.fsf)</tt>). These input files will then be loaded:

<pre>
fractgen alpha01.fsf beta04.fsf delta07.fsf
</pre>


# 📚 KFractGen

FractGen is the [KDE](https://develop.kde.org/) version of the fractal generator program. That is, it provides a KDE-based GUI (which itself is based on Qt).
It can simply be started via the GUI menu (depending on the desktop environment), or from the command-line:

<pre>
kfractgen
</pre>

Alternatively, it is also possible to specify one or more input files (e.g.&nbsp;<tt>[gamma01.fsf](src/examples/gamma01.fsf)</tt>, <tt>[delta03.fsf](src/examples/delta03.fsf)</tt>, <tt>[kappa02.fsf](src/examples/kappa02.fsf)</tt>). These input files will then be loaded:

<pre>
kfractgen gamma01.fsf delta03.fsf kappa02.fsf
</pre>


# 📚 CLIFractGen

CLIFractGen is the command-line version of the fractal generator program. That is, does not provide a GUI and can be used to process FractGen input files via scripts.

* Process <tt>[epsilon10.fsf](src/examples/epsilon10.fsf)</tt> and generate 1920x1080 (Full HD resolution) in PNG output format with a maximum of 2500&nbsp;iterations:
  <pre>
  clifractgen -W 1920 -H 1080 -M 2500 epsilon10.fsf epsilon10.png
  </pre>

* Process <tt>[gamma05.fsf](src/examples/gamma05.fsf)</tt> and generate 3840x2160 (Ultra-HD resolution) in WebP output format with a maximum of 5000&nbsp;iterations:

  <pre>
  clifractgen -W 3840 -H 2160 -M 5000 gamma05.fsf gamma05.webp
  </pre>

* Find all files matching pattern <tt>*.fsf</tt> in the local directory (e.g.&nbsp;using the examples from [src/examples](src/examples), and compute 3840x2160 WebP output format:

  <pre>
  find . -name "*.fsf" | xargs -i§ clifractgen -W 3840 -H 2160 -M 5000 § §.webp
  </pre>

* The manpage of CLIFractGen contains details and further examples:

  <pre>
  man clifractgen
  </pre>


# 😀 Examples

<table summary="System-Info Banner Examples">
 <tr>
  <td style="vertical-align: center;">
   <p align="center">
    <a href="src/figures/7680x4320/delta11.webp">
      <img alt="Example delta11.fsf" src="src/figures/1280x720/delta11.webp" width="100%" height="100%" />
    </a><br />
    <tt><a type="application/x-fractgen" href="src/examples/delta11.fsf">delta11.fsf</a></tt><br />
   </p>
  </td>
  <td style="vertical-align: center;">
   <p align="center">
    <a href="src/figures/7680x4320/epsilon06.webp">
      <img alt="Example epsilon06.fsf" src="src/figures/1280x720/epsilon06.webp" width="100%" height="100%" />
    </a><br />
    <tt><a type="application/x-fractgen" href="src/examples/epsilon06.fsf">epsilon06.fsf</a></tt><br />
   </p>
  </td>
  <td style="vertical-align: center;">
   <p align="center">
    <a href="src/figures/7680x4320/gamma08.webp">
      <img alt="Example gamma08.fsf" src="src/figures/1280x720/gamma08.webp" width="100%" height="100%" />
    </a><br />
    <tt><a type="application/x-fractgen" href="src/examples/gamma08.fsf">gamma08.fsf</a></tt><br />
   </p>
  </td>
 </tr>

 <tr>
  <td style="vertical-align: center;">
   <p align="center">
    <a href="src/figures/7680x4320/gamma10.webp">
      <img alt="Example gamma10.fsf" src="src/figures/1280x720/gamma10.webp" width="100%" height="100%" />
    </a><br />
    <tt><a type="application/x-fractgen" href="src/examples/gamma10.fsf">gamma10.fsf</a></tt><br />
   </p>
  </td>
  <td style="vertical-align: center;">
   <p align="center">
    <a href="src/figures/7680x4320/kappa11.webp">
      <img alt="Example kappa11.fsf" src="src/figures/1280x720/kappa11.webp" width="100%" height="100%" />
    </a><br />
    <tt><a type="application/x-fractgen" href="src/examples/kappa11.fsf">kappa11.fsf</a></tt><br />
   </p>
  </td>
  <td style="vertical-align: center;">
   <p align="center">
    <a href="src/figures/7680x4320/lambda01.webp">
      <img alt="Example lambda01.fsf" src="src/figures/1280x720/lambda01.webp" width="100%" height="100%" />
    </a><br />
    <tt><a type="application/x-fractgen" href="src/examples/lambda01.fsf">lambda01.fsf</a></tt><br />
   </p>
  </td>
 </tr>

 <tr>
  <td style="vertical-align: center;">
   <p align="center">
    <a href="src/figures/7680x4320/nu08.webp">
      <img alt="Example nu08.fsf" src="src/figures/1280x720/nu08.webp" width="100%" height="100%" />
    </a><br />
    <tt><a type="application/x-fractgen" href="src/examples/nu08.fsf">nu08.fsf</a></tt><br />
    </p>
  </td>
  <td style="vertical-align: center;">
    <p align="center">
    <a href="src/figures/7680x4320/phi04.webp">
      <img alt="Example phi04.fsf" src="src/figures/1280x720/phi04.webp" width="100%" height="100%" />
    </a><br />
    <tt><a type="application/x-fractgen" href="src/examples/phi04.fsf">phi04.fsf</a></tt><br />
   </p>
  </td>
  <td style="vertical-align: center;">
   <p align="center">
    <a href="src/figures/7680x4320/psi09.webp">
      <img alt="Example psi09.fsf" src="src/figures/1280x720/psi09.webp" width="100%" height="100%" />
    </a><br />
    <tt><a type="application/x-fractgen" href="src/examples/psi09.fsf">psi09.fsf</a></tt><br />
   </p>
  </td>
 </tr>

 <tr>
  <td style="vertical-align: center;">
   <p align="center">
    <a href="src/figures/7680x4320/sigma06.webp">
      <img alt="Example sigma06.fsf" src="src/figures/1280x720/sigma06.webp" width="100%" height="100%" />
    </a><br />
    <tt><a type="application/x-fractgen" href="src/examples/sigma06.fsf">sigma06.fsf</a></tt><br />
   </p>
  </td>
  <td style="vertical-align: center;">
   <p align="center">
    <a href="src/figures/7680x4320/theta04.webp">
      <img alt="Example theta04.fsf" src="src/figures/1280x720/theta04.webp" width="100%" height="100%" />
    </a><br />
    <tt><a type="application/x-fractgen" href="src/examples/theta04.fsf">theta04.fsf</a></tt><br />
   </p>
  </td>
  <td style="vertical-align: center;">
   <p align="center">
    <a href="src/figures/7680x4320/tau06.webp">
      <img alt="Example tau06.fsf" src="src/figures/1280x720/tau06.webp" width="100%" height="100%" />
    </a><br />
    <tt><a type="application/x-fractgen" href="src/examples/tau06.fsf">tau06.fsf</a></tt><br />
   </p>
  </td>
 </tr>

</table>


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
