# ==========================================================================
# ====                   FRACTAL GRAPHICS GENERATOR                     ====
# ==========================================================================
#
# Copyright (C) 2003-2025 by Thomas Dreibholz
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

SET(CMAKE_INCLUDE_CURRENT_DIR ON)


#############################################################################
#### VERSION FILE                                                        ####
#############################################################################

CONFIGURE_FILE (
   "${CMAKE_CURRENT_SOURCE_DIR}/package-version.h.in"
   "${CMAKE_CURRENT_BINARY_DIR}/package-version.h"
)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})


#############################################################################
#### PROGRAMS                                                            ####
#############################################################################

SET(basicSourceFiles
   classregistry.cc
   colorschemeinterface.cc
   doubleconfigentry.cc
   dreibholz1.cc
   fractalalgorithminterface.cc
   fractalbuffer.cc
   fractalcalculationthread.cc
   fractalgeneratordoc.cc
   fractalgeneratorviewbase.cc
   mandelbrot.cc
   mandelbrotn.cc
   simplehsv.cc
   simplergb.cc
   uintconfigentry.cc
)
SET(guiSourceFiles
   ${basicSourceFiles}
   fractgen.cc
   imagedisplay.cc
   fractalgenerator.cc
   fractalgeneratorview.cc
   optionsdialog.cc
)

# ====== Qt version =========================================================
ADD_EXECUTABLE(fractgen ${guiSourceFiles})
TARGET_LINK_LIBRARIES(fractgen
   Qt${QT_VERSION_MAJOR}::Core
   Qt${QT_VERSION_MAJOR}::PrintSupport
   Qt${QT_VERSION_MAJOR}::Widgets
   Qt${QT_VERSION_MAJOR}::Xml
)

INSTALL(TARGETS             fractgen
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        BUNDLE DESTINATION  ${CMAKE_INSTALL_BINDIR})
INSTALL(FILES fractgen.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)

INSTALL(FILES fractgen.png     DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/512x512/apps)
INSTALL(FILES fractgen.desktop DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)
INSTALL(FILES fractgen.xml     DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/mime/packages)
INSTALL(FILES       fractgen.bash-completion
        DESTINATION ${CMAKE_INSTALL_DATADIR}/bash-completion/completions
        RENAME      fractgen)

FILE(GLOB FRACTGEN_TS_FILES  "fractgen_*.ts")
SET(FRACTGEN_QM_FILES "")
FOREACH(tsFile IN LISTS FRACTGEN_TS_FILES)
   GET_FILENAME_COMPONENT(fileBase ${tsFile} NAME_WE)
   SET(qmFile "${fileBase}.qm")
   ADD_CUSTOM_COMMAND(OUTPUT  ${qmFile}
                      COMMAND ${LRELEASE} -removeidentical ${tsFile})
   ADD_CUSTOM_TARGET(target_${qmFile} ALL DEPENDS ${qmFile})
   LIST(APPEND FRACTGEN_QM_FILES ${qmFile})
ENDFOREACH()
INSTALL(FILES ${FRACTGEN_QM_FILES} DESTINATION ${CMAKE_INSTALL_DATADIR}/fractgen)


# ====== KDE version ========================================================
IF (WITH_KDE)
   ADD_EXECUTABLE(kfractgen ${guiSourceFiles})
   SET_TARGET_PROPERTIES(kfractgen PROPERTIES COMPILE_FLAGS "-DWITH_KDE")
   TARGET_LINK_LIBRARIES(kfractgen
      Qt${QT_VERSION_MAJOR}::Core
      Qt${QT_VERSION_MAJOR}::PrintSupport
      Qt${QT_VERSION_MAJOR}::Widgets
      Qt${QT_VERSION_MAJOR}::Xml
      KF${QT_VERSION_MAJOR}::CoreAddons
      KF${QT_VERSION_MAJOR}::WidgetsAddons
      KF${QT_VERSION_MAJOR}::XmlGui
   )
   INSTALL(TARGETS             kfractgen
           RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
           BUNDLE DESTINATION  ${CMAKE_INSTALL_BINDIR})
   INSTALL(FILES kfractgen.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
   INSTALL(FILES kfractgen.desktop DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)
   INSTALL(FILES       kfractgen.bash-completion
           DESTINATION ${CMAKE_INSTALL_DATADIR}/bash-completion/completions
           RENAME      kfractgen)
ENDIF()


# ====== CLI version ========================================================
IF (WITH_CLI)
   ADD_EXECUTABLE(clifractgen
      ${basicSourceFiles}
      clifractgen.cc
   )
   TARGET_LINK_LIBRARIES(clifractgen
      Qt${QT_VERSION_MAJOR}::Core
      Qt${QT_VERSION_MAJOR}::Widgets
      Qt${QT_VERSION_MAJOR}::Xml
   )

   INSTALL(TARGETS             clifractgen
           RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
           BUNDLE DESTINATION  ${CMAKE_INSTALL_BINDIR})
   INSTALL(FILES clifractgen.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)
   INSTALL(FILES       clifractgen.bash-completion
           DESTINATION ${CMAKE_INSTALL_DATADIR}/bash-completion/completions
           RENAME      clifractgen)
ENDIF()


# ==== Examples =============================================================
FILE(GLOB fractgen_examples "examples/*.fsf")
INSTALL(FILES ${fractgen_examples} DESTINATION ${CMAKE_INSTALL_DATADIR}/fractgen/examples)
