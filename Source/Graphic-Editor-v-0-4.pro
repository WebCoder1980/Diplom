QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GraphicDisplay/brush.cpp \
    GraphicDisplay/core.cpp \
    GraphicDisplay/erasser.cpp \
    GraphicDisplay/figures.cpp \
    GraphicDisplay/fill.cpp \
    GraphicDisplay/highlighting.cpp \
    GraphicDisplay/insertphoto.cpp \
    GraphicDisplay/pencil.cpp \
    GraphicDisplay/ruller.cpp \
    GraphicDisplay/text.cpp \
    GraphicDisplay/toolcore.cpp \
    GraphicDisplay/vector.cpp \
    dialogcreatefile.cpp \
    main.cpp \
    mainmenu.cpp

HEADERS += \
    GraphicDisplay/brush.h \
    GraphicDisplay/core.h \
    GraphicDisplay/erasser.h \
    GraphicDisplay/figures.h \
    GraphicDisplay/fill.h \
    GraphicDisplay/highlighting.h \
    GraphicDisplay/insertphoto.h \
    GraphicDisplay/pencil.h \
    GraphicDisplay/ruller.h \
    GraphicDisplay/text.h \
    GraphicDisplay/toolcore.h \
    GraphicDisplay/vector.h \
    dialogcreatefile.h \
    mainmenu.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resurses.qrc
