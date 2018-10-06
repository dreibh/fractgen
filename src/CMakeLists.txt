SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# ###### Program ############################################################
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


# ###### Examples ###########################################################
FILE(GLOB fractgen_examples "examples/*.fsf")
INSTALL(FILES ${fractgen_examples} DESTINATION ${CMAKE_INSTALL_DATADIR}/fractgen/examples)
