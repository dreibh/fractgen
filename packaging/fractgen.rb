class Fractgen < Formula
  desc "Fractal Generator"
  homepage "https://www.nntb.no/~dreibh/fractalgenerator/"
  url "https://www.nntb.no/~dreibh/fractalgenerator/download/fractgen-3.0.13.tar.xz"
  sha256 "06951765b2145456de54d2c5ff0c2d09685eb0951a5157399621bacf4a1f9244"
  license "GPL-3.0-or-later"

  # Option OFF by default (matching OPTIONS_DEFAULT exclusion in FreeBSD)
  option "with-kde", "Build with KDE GUI interface"

  # Options ON by default (matching OPTIONS_DEFAULT in FreeBSD)
  option "without-cli", "Build without command-line interface"
  option "without-examples", "Build without example files"
  option "without-qt", "Build without Qt GUI interface"

  # Build-time dependencies
  depends_on "cmake" => :build
  depends_on "extra-cmake-modules" => :build if build.with?("kde")
  depends_on "ninja" => :build
  depends_on "pkg-config" => :build
  depends_on "qttools" => :build if build.with?("qt") || build.with?("kde")
  depends_on "qtbase" if build.with?("qt") || build.with?("kde")
  depends_on "qtimageformats" if build.with?("qt") || build.with?("kde")

  def install
    args = std_cmake_args + %W[
      -GNinja
      -DCMAKE_MACOSX_RPATH=ON
      -DCMAKE_BUILD_WITH_INSTALL_RPATH=ON
      -DCMAKE_INSTALL_RPATH_USE_LINK_PATH=ON
      -DCMAKE_INSTALL_RPATH=#{rpath}
      -DWITH_CLI=#{build.with?("cli") ? "ON" : "OFF"}
      -DWITH_EXAMPLES=#{build.with?("examples") ? "ON" : "OFF"}
      -DWITH_KDE=#{build.with?("kde") ? "ON" : "OFF"}
      -DWITH_QT=#{build.with?("qt") ? "ON" : "OFF"}
    ]

    system "cmake", "-S", ".", "-B", "build", *args
    system "cmake", "--build", "build"
    system "cmake", "--install", "build"
  end

  test do
    assert_path_exists bin/"fractgen" if build.with?("cli") || build.with?("qt") || build.with?("kde")
  end
end
