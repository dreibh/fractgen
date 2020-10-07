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
INSTALL(FILES fractgen.desktop DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)


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
