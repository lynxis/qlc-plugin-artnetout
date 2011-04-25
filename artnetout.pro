include(../../variables.pri)

TEMPLATE = lib
LANGUAGE = C++
TARGET   = artnetout

INCLUDEPATH += ../interfaces
CONFIG      += plugin
QT          += xml

# Input
HEADERS += artnetout.h \
            artnetthread.h \
            configureartnetout.h \
            ../interfaces/qlcoutplugin.h \
    configureartnetoutdialog.h

FORMS += configureartnetout.ui \
    configureartnetoutdialog.ui
SOURCES += artnetout.cpp \
            artnetthread.cpp \
            configureartnetout.cpp \
    configureartnetoutdialog.cpp


PRO_FILE = artnetout.pro

target.path = $$INSTALLROOT/$$INPUTPLUGINDIR
INSTALLS   += target
