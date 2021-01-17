SET(CMAKE_INCLUDE_CURRENT_DIR ON)

#############################################################################
# PROGRAMS
#############################################################################

ADD_EXECUTABLE(fractgen
   colorschemeinterface.cc
   doubleconfigentry.cc
   dreibholz1.cc
   fractalalgorithminterface.cc
   fractalbuffer.cc
   fractalcalculationthread.cc
   fractgen.cc
   imagedisplay.cc
   fractalgenerator.cc
   fractalgeneratordoc.cc
   fractalgeneratorview.cc
   mandelbrot.cc
   mandelbrotn.cc
   optionsdialog.cc
   simplehsv.cc
   simplergb.cc
   uintconfigentry.cc)
TARGET_LINK_LIBRARIES(fractgen Qt5::Widgets Qt5::Xml Qt5::Core Qt5::PrintSupport)

INSTALL(TARGETS             fractgen
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        BUNDLE DESTINATION  ${CMAKE_INSTALL_BINDIR})
INSTALL(FILES fractgen.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)

INSTALL(FILES fractgen.png     DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/512x512/apps)
INSTALL(FILES fractgen.desktop DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)
INSTALL(FILES fractgen.xml     DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/mime/packages)

FILE(GLOB FRACTGEN_TS_FILES  "fractgen_*.ts")
SET(FRACTGEN_QM_FILES "")
FOREACH(tsFile IN LISTS FRACTGEN_TS_FILES)
   GET_FILENAME_COMPONENT(fileBase ${tsFile} NAME_WE)
   SET(qmFile "${fileBase}.qm")
   ADD_CUSTOM_COMMAND(OUTPUT ${qmFile}
                      COMMAND qtchooser -qt=qt5 -run-tool=lrelease ${tsFile})
   ADD_CUSTOM_TARGET(target_${qmFile} ALL DEPENDS ${qmFile})
   LIST(APPEND FRACTGEN_QM_FILES ${qmFile})
ENDFOREACH()
INSTALL(FILES ${FRACTGEN_QM_FILES} DESTINATION ${CMAKE_INSTALL_DATADIR}/fractgen)


IF (ENABLE_KDE)
   ADD_EXECUTABLE(kfractgen
   colorschemeinterface.cc
   doubleconfigentry.cc
   dreibholz1.cc
   fractalalgorithminterface.cc
   fractalbuffer.cc
   fractalcalculationthread.cc
   fractgen.cc
   imagedisplay.cc
   fractalgenerator.cc
   fractalgeneratordoc.cc
   fractalgeneratorview.cc
   mandelbrot.cc
   mandelbrotn.cc
   optionsdialog.cc
   simplehsv.cc
   simplergb.cc
   uintconfigentry.cc)

   SET_TARGET_PROPERTIES(kfractgen PROPERTIES COMPILE_FLAGS "-DWITH_KDE")
   TARGET_LINK_LIBRARIES(kfractgen Qt5::Widgets Qt5::Xml Qt5::Core Qt5::PrintSupport KF5::CoreAddons KF5::WidgetsAddons KF5::XmlGui)
   INSTALL(TARGETS             kfractgen
           RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
           BUNDLE DESTINATION  ${CMAKE_INSTALL_BINDIR})
ENDIF()


# ###### Examples ###########################################################
FILE(GLOB fractgen_examples "examples/*.fsf")
INSTALL(FILES ${fractgen_examples} DESTINATION ${CMAKE_INSTALL_DATADIR}/fractgen/examples)
