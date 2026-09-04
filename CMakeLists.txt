# ==========================================================================
# ====                   FRACTAL GRAPHICS GENERATOR                     ====
# ==========================================================================
#
# Copyright (C) 2003-2026 by Thomas Dreibholz
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Contact: thomas.dreibholz@gmail.com

CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
PROJECT(fractgen LANGUAGES C CXX)

SET(BUILD_MAJOR "3")
SET(BUILD_MINOR "0")
SET(BUILD_PATCH "13")
SET(BUILD_VERSION ${BUILD_MAJOR}.${BUILD_MINOR}.${BUILD_PATCH})


INCLUDE(CheckIncludeFile)
INCLUDE(CheckStructHasMember)


#############################################################################
#### CMAKE INCLUDES                                                      ####
#############################################################################

INCLUDE(CheckCCompilerFlag)
INCLUDE(CheckCSourceCompiles)
INCLUDE(CheckCSourceRuns)
INCLUDE(CheckIncludeFile)
INCLUDE(CheckStructHasMember)
INCLUDE(GNUInstallDirs)


#############################################################################
#### PACKAGING                                                           ####
#############################################################################

SET(CPACK_SOURCE_GENERATOR "TXZ")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${BUILD_MAJOR}.${BUILD_MINOR}.${BUILD_PATCH}")
SET(CPACK_SOURCE_IGNORE_FILES "\\\\.git;\\\\.swp$;~$;\\\\.\\\\#;/\\\\#")
LIST(APPEND CPACK_SOURCE_IGNORE_FILES "^${PROJECT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}[_-]")
LIST(APPEND CPACK_SOURCE_IGNORE_FILES "\\\\.make$|\\\\.log$")
LIST(APPEND CPACK_SOURCE_IGNORE_FILES "/CMakeCache\\\\.txt$")
LIST(APPEND CPACK_SOURCE_IGNORE_FILES "/(CMakeFiles|CMakeScripts|_CPack_Packages)/")
LIST(APPEND CPACK_SOURCE_IGNORE_FILES "/package-version\\\\.h$")
LIST(APPEND CPACK_SOURCE_IGNORE_FILES "/packaging\\\\.conf$")
LIST(APPEND CPACK_SOURCE_IGNORE_FILES "^${PROJECT_SOURCE_DIR}/(po.*/|src.*/|)Makefile$")
LIST(APPEND CPACK_SOURCE_IGNORE_FILES "^${PROJECT_SOURCE_DIR}/(po.*|src.*|[^/]*)\\\\.cmake$")
INCLUDE(CPack)

ADD_CUSTOM_TARGET(dist COMMAND ${CMAKE_MAKE_PROGRAM} clean package_source)


#############################################################################
#### UNINSTALL                                                           ####
#############################################################################

IF(NOT TARGET uninstall)
   CONFIGURE_FILE(
      "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
      "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
      IMMEDIATE @ONLY)

   ADD_CUSTOM_TARGET(uninstall
      COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
ENDIF()


#############################################################################
#### OS-DEPENDENT                                                        ####
#############################################################################

IF (CMAKE_SYSTEM_NAME MATCHES "NetBSD")
   IF(NOT DEFINED CMAKE_INSTALL_RPATH_USE_LINK_PATH)
      SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)
   ENDIF()
   # SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_FULL_LIBDIR}")
ENDIF()


#############################################################################
#### OPTIONS                                                             ####
#############################################################################

OPTION(WITH_QT       "Build the Qt version"           ON)
OPTION(WITH_KDE      "Build the KDE version"          OFF)
OPTION(WITH_CLI      "Build the command-line version" ON)
OPTION(WITH_EXAMPLES "Include example files"          ON)


#############################################################################
#### REQUIREMENTS                                                        ####
#############################################################################

# ====== Qt =================================================================
FIND_PROGRAM(QMAKE NAMES qmake6 qmake-qt6 qmake5 qmake-qt5 qmake PATHS /usr/lib/qt/*/bin)
IF (QMAKE)
   EXECUTE_PROCESS(
      COMMAND "${QMAKE}" -query QT_INSTALL_PREFIX
      OUTPUT_VARIABLE QT_INSTALL_PREFIX
      OUTPUT_STRIP_TRAILING_WHITESPACE
   )
   LIST(APPEND CMAKE_PREFIX_PATH
      "${QT_INSTALL_PREFIX}"
      "${QT_INSTALL_PREFIX}/lib/amd64"
      "${QT_INSTALL_PREFIX}/lib/amd64/cmake"
   )
ENDIF()

SET(CMAKE_AUTOMOC ON)
FIND_PACKAGE(QT NAMES Qt6 COMPONENTS Core Network Widgets Xml PrintSupport)
IF (NOT QT_FOUND)
   # Try Qt5 instead:
   FIND_PACKAGE(QT NAMES Qt5 COMPONENTS Core Network Widgets Xml PrintSupport)
ENDIF()
IF (NOT QT_FOUND)
   MESSAGE(FATAL_ERROR
           "Cannot find Qt! Try:\n"
           " * Ubuntu/Debian: sudo apt install -y qt6-base-dev\n"
           " * Fedora:        sudo dnf install -y qt6-qtbase-devel\n"
           " * OpenSUSE:      sudo zypper install -y libqt6-qtbase-devel\n"
           " * Alpine:        sudo apk add qt6-qtbase-dev\n"
           " * FreeBSD:       sudo pkg install -y qt6-base\n"
           " * NetBSD:        sudo pkgin -y install qt6-qtbase\n"
           " * OpenBSD:       sudo pkg_add qt6-qtbase\n"
           " * Solaris:       sudo pkg install library/qt6 print/cups\n"
           " * Apple:         brew install qt")
ENDIF()
MESSAGE("Using Qt version ${QT_VERSION_MAJOR}!")

FIND_PROGRAM(LRELEASE lrelease lrelease-qt${QT_VERSION_MAJOR}
             PATHS ${QT_INSTALL_PREFIX}/bin
                   /usr/pkg/qt${QT_VERSION_MAJOR}/bin
                   /usr/local/lib/qt${QT_VERSION_MAJOR}/bin
                   /usr/lib64/qt${QT_VERSION_MAJOR}/bin
                   /usr/lib/qt${QT_VERSION_MAJOR}/bin
                   /usr/bin
             EQUIRED)
IF (LRELEASE)
   MESSAGE("LRelease found: ${LRELEASE}!")
ELSE()
   MESSAGE(FATAL_ERROR
           "Cannot find Qt Linguist's LRelease tool! Try:\n"
           " * Ubuntu/Debian: sudo apt install -y qt6-l10n-tools\n"
           " * Fedora:        sudo dnf install -y qt6-linguist\n"
           " * OpenSUSE:      sudo zypper install -y qt6-tools-linguist\n"
           " * Alpine:        sudo apk add qt6-qttools\n"
           " * FreeBSD:       sudo pkg install -y qt6-tools\n"
           " * NetBSD:        sudo pkgin -y install qt6-qttools\n"
           " * OpenBSD:       sudo pkg_add qt6-qttools\n"
           " * Solaris:       sudo pkg install library/cups library/qt6\n"
           " * Apple:         brew install qt")
ENDIF()

# ====== KDE ================================================================
IF (WITH_KDE)
   # Needed:
   # KDE5: libkf5coreaddons-dev libkf5xmlgui-dev
   # KDE6: libkf6coreaddons-dev libkf6xmlgui-dev

   FIND_PACKAGE(ECM "1.0.0" NO_MODULE REQUIRED)
   SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})

   INCLUDE(KDEInstallDirs)
   INCLUDE(KDECMakeSettings)
   INCLUDE(KDECompilerSettings NO_POLICY_SCOPE)
   INCLUDE(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)

   FIND_PACKAGE(KF${QT_VERSION_MAJOR} "${QT_VERSION_MAJOR}.0.0" REQUIRED COMPONENTS CoreAddons WidgetsAddons XmlGui)
ENDIF()

INCLUDE(FeatureSummary)
FEATURE_SUMMARY(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)


#############################################################################
#### SUBDIRECTORIES                                                      ####
#############################################################################

ADD_SUBDIRECTORY(src)
