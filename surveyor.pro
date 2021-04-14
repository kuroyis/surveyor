QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    character.cpp \
    game.cpp \
    gamedate.cpp \
    hide.cpp \
    iteam.cpp \
    iteampushbutton.cpp \
    loadselect.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    mapselect.cpp \
    mypushbutton.cpp \
    persondate.cpp \
    personscene.cpp \
    player.cpp \
    saveselect.cpp \
    store.cpp

HEADERS += \
    character.h \
    game.h \
    gamedate.h \
    hide.h \
    iteam.h \
    iteampushbutton.h \
    loadselect.h \
    mainwindow.h \
    map.h \
    mapselect.h \
    mypushbutton.h \
    persondate.h \
    personscene.h \
    player.h \
    saveselect.h \
    store.h

FORMS += \
    game.ui \
    gamedate.ui \
    hide.ui \
    loadselect.ui \
    mainwindow.ui \
    mapselect.ui \
    persondate.ui \
    personscene.ui \
    saveselect.ui \
    store.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
