SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# ###### Program ############################################################
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
# INSTALL(FILES fractgen_de_DE.qm fractgen_nb_NO.qm DESTINATION ${CMAKE_INSTALL_DATADIR}/fractgen)


# ###### Examples ###########################################################
FILE(GLOB fractgen_examples "examples/*.fsf")
INSTALL(FILES ${fractgen_examples} DESTINATION ${CMAKE_INSTALL_DATADIR}/fractgen/examples)
