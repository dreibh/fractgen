# ==========================================================================
# ====                   FRACTAL GRAPHICS GENERATOR                     ====
# ==========================================================================
#
# Copyright (C) 2003-2024 by Thomas Dreibholz
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

SET(BUILD_MAJOR "2")
SET(BUILD_MINOR "2")
SET(BUILD_PATCH "0~beta0")
SET(BUILD_VERSION ${BUILD_MAJOR}.${BUILD_MINOR}.${BUILD_PATCH})


#############################################################################
#### INSTALLATION_DIRECTORIES                                            ####
#############################################################################

# See: https://cmake.org/cmake/help/v3.0/module/GNUInstallDirs.html
INCLUDE(GNUInstallDirs)


#############################################################################
#### PACKAGING                                                           ####
#############################################################################

SET(CPACK_SOURCE_GENERATOR "TXZ")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME
    "${CMAKE_PROJECT_NAME}-${BUILD_MAJOR}.${BUILD_MINOR}.${BUILD_PATCH}")
SET(CPACK_SOURCE_IGNORE_FILES "\\\\.git;\\\\.swp$;~$;\\\\.\\\\#;/\\\\#")
LIST(APPEND CPACK_SOURCE_IGNORE_FILES "^${PROJECT_SOURCE_DIR}/${CMAKE_PROJECT_NAME}[_-]")
LIST(APPEND CPACK_SOURCE_IGNORE_FILES "\\\\.cmake$|\\\\.make$|\\\\.log$")
LIST(APPEND CPACK_SOURCE_IGNORE_FILES "/CMakeCache\\\\.txt$")
LIST(APPEND CPACK_SOURCE_IGNORE_FILES "/(CMakeFiles|CMakeScripts|_CPack_Packages)/")
LIST(APPEND CPACK_SOURCE_IGNORE_FILES "/package-version\\\\.h$")
LIST(APPEND CPACK_SOURCE_IGNORE_FILES "/packaging\\\\.conf$")
LIST(APPEND CPACK_SOURCE_IGNORE_FILES "^${PROJECT_SOURCE_DIR}/(po.*/|src.*/|)Makefile$")
INCLUDE(CPack)

ADD_CUSTOM_TARGET(dist COMMAND ${CMAKE_MAKE_PROGRAM} clean package_source)


INCLUDE(CheckIncludeFile)
INCLUDE(CheckStructHasMember)


#############################################################################
#### OS-DEPENDENT                                                        ####
#############################################################################

IF (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    MESSAGE(STATUS ${CMAKE_SYSTEM_NAME} " supported")

ELSEIF (${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD")
    MESSAGE(STATUS ${CMAKE_SYSTEM_NAME} " supported")
    SET(CMAKE_REQUIRED_INCLUDES "/usr/local/include" "/usr/include")
    SET(CMAKE_LIBRARY_PATH "/usr/local/lib")
    INCLUDE_DIRECTORIES("/usr/local/include")

ELSEIF (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    MESSAGE(STATUS ${CMAKE_SYSTEM_NAME} " supported")
    SET(CMAKE_REQUIRED_INCLUDES "/usr/local/include" "/usr/include" "/usr/local/opt/openssl/include")
    SET(CMAKE_LIBRARY_PATH "/usr/local/lib")
    INCLUDE_DIRECTORIES("/usr/local/include" "/usr/local/opt/openssl/include")

ELSEIF (${CMAKE_SYSTEM_NAME} MATCHES "NetBSD")
    MESSAGE(STATUS ${CMAKE_SYSTEM_NAME} " supported")
    SET(CMAKE_REQUIRED_INCLUDES "/usr/pkg/include" "/usr/include" "/usr/local/include")
    SET(CMAKE_LIBRARY_PATH "/usr/local/lib")
    INCLUDE_DIRECTORIES("/usr/pkg/include" "/usr/local/include")

ELSE()
    MESSAGE(FATAL_ERROR ${CMAKE_SYSTEM_NAME} " not supported (yet?)")

ENDIF()


#############################################################################
#### REQUIREMENTS                                                        ####
#############################################################################

# ###### Qt #################################################################
SET(CMAKE_AUTOMOC ON)
FIND_PACKAGE(QT NAMES Qt6 COMPONENTS Core Network Widgets Xml PrintSupport)
IF (NOT QT_FOUND)
   FIND_PACKAGE(QT NAMES Qt5 REQUIRED COMPONENTS Core Network Widgets Xml PrintSupport)
ENDIF()
MESSAGE("Using Qt version ${QT_VERSION_MAJOR}!")
FIND_PACKAGE(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network Widgets Xml PrintSupport)
FIND_PROGRAM(LRELEASE lrelease PATHS /usr/local/lib/qt${QT_VERSION_MAJOR}/bin
                                     /usr/lib/qt${QT_VERSION_MAJOR}/bin
                                     /usr/bin
                               REQUIRED)
MESSAGE("Using LRelease ${LRELEASE}!")

# ###### KDE ################################################################
OPTION(WITH_KDE "Build with KDE support" 0)
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
feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)


#############################################################################
#### SUBDIRECTORIES                                                      ####
#############################################################################

ADD_SUBDIRECTORY(src)
