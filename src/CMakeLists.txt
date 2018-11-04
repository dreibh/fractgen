SET(CMAKE_INCLUDE_CURRENT_DIR ON)

#############################################################################
# PROGRAMS
#############################################################################

ADD_EXECUTABLE(fractgen
   colorschemeinterface.cpp
   doubleconfigentry.cpp
   dreibholz1.cpp
   fractalalgorithminterface.cpp
   fractalbuffer.cpp
   fractalcalculationthread.cpp
   fractgen.cpp
   imagedisplay.cpp
   fractalgenerator.cpp
   fractalgeneratordoc.cpp
   fractalgeneratorview.cpp
   mandelbrot.cpp
   mandelbrotn.cpp
   optionsdialog.cpp
   simplehsv.cpp
   simplergb.cpp
   uintconfigentry.cpp)

TARGET_LINK_LIBRARIES(fractgen Qt5::Widgets Qt5::Xml Qt5::Core Qt5::PrintSupport)
INSTALL(TARGETS             fractgen
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        BUNDLE DESTINATION  ${CMAKE_INSTALL_BINDIR})
INSTALL(FILES fractgen.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)


IF (ENABLE_KDE)
   ADD_EXECUTABLE(kfractgen
   colorschemeinterface.cpp
   doubleconfigentry.cpp
   dreibholz1.cpp
   fractalalgorithminterface.cpp
   fractalbuffer.cpp
   fractalcalculationthread.cpp
   fractgen.cpp
   imagedisplay.cpp
   fractalgenerator.cpp
   fractalgeneratordoc.cpp
   fractalgeneratorview.cpp
   mandelbrot.cpp
   mandelbrotn.cpp
   optionsdialog.cpp
   simplehsv.cpp
   simplergb.cpp
   uintconfigentry.cpp)

   SET_TARGET_PROPERTIES(kfractgen PROPERTIES COMPILE_FLAGS "-DWITH_KDE")
   TARGET_LINK_LIBRARIES(kfractgen Qt5::Widgets Qt5::Xml Qt5::Core Qt5::PrintSupport KF5::CoreAddons KF5::I18n KF5::WidgetsAddons)
   INSTALL(TARGETS             kfractgen
           RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
           BUNDLE DESTINATION  ${CMAKE_INSTALL_BINDIR})
ENDIF()


# ###### Examples ###########################################################
FILE(GLOB fractgen_examples "examples/*.fsf")
INSTALL(FILES ${fractgen_examples} DESTINATION ${CMAKE_INSTALL_DATADIR}/fractgen/examples)
