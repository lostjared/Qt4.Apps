######################################################################
# Automatically generated by qmake (2.01a) Fri May 1 08:46:53 2009
######################################################################

QT += opengl
TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += .
RESOURCES += resource.qrc
!macx {
    LIBS += -lGLU
}
# Input
HEADERS += gameWidget.h mainWindow.h mpmut.h
SOURCES += appMain.cc gameWidget.cc mainWindow.cc mpmut.cpp
