TEMPLATE = app
TARGET = fractgen
INCLUDEPATH += .

target.path +=  /usr/bin/
INSTALLS +=  target

SOURCES += \
colorschemeinterface.cpp \
doubleconfigentry.cpp \
dreibholz1.cpp \
fractalalgorithminterface.cpp \
fractalbuffer.cpp \
fractalcalculationthread.cpp \
fractgen.cpp \
imagedisplay.cpp \
fractalgenerator.cpp \
fractalgeneratordoc.cpp \
fractalgeneratorview.cpp \
mandelbrot.cpp \
mandelbrotn.cpp \
optionsdialog.cpp \
simplehsv.cpp \
simplergb.cpp \
uintconfigentry.cpp

HEADERS += \
colorschemeinterface.h \
configentry.h \
doubleconfigentry.h \
dreibholz1.h \
fractalalgorithminterface.h \
fractalbuffer.h \
fractalcalculationthread.h \
imagedisplay.h \
fractalgenerator.h \
fractalgeneratordoc.h \
fractalgeneratorview.h \
mandelbrot.h \
mandelbrotn.h \
optionsdialog.h \
simplehsv.h \
simplergb.h \
uintconfigentry.h

QT += xml
