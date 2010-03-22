# -------------------------------------------------
# Project created by QtCreator 2010-02-28T18:40:49
# -------------------------------------------------
QT += network \
    sql
TARGET = MusicFinder
TEMPLATE = app

# Libs
# LIBS += -lTagLib
# Sources
SOURCES += src/main.cpp \
    src/lastfm/lastfm.cpp \
    src/lastfm/searchbox.cpp \
    src/lastfm/lastfmsuggest.cpp \
    src/3tdparty/QProgressIndicator/QProgressIndicator.cpp \
    src/3tdparty/jsonstreamreader/jsonstreamreader.cpp \
    src/lastfm/imgloader.cpp \
    src/lastfm/title.cpp \
    src/wnd/mainwnd.cpp \
    src/widgets/leftpanel.cpp
HEADERS += src/lastfm/lastfm.h \
    src/lastfm/searchbox.h \
    src/lastfm/lastfmsuggest.h \
    src/3tdparty/QProgressIndicator/QProgressIndicator.h \
    src/3tdparty/jsonstreamreader/jsonstreamreader.h \
    src/lastfm/imgloader.h \
    src/lastfm/title.h \
    src/wnd/mainwnd.h \
    src/widgets/leftpanel.h
RESOURCES += src/resources.qrc
FORMS += src/wnd/mainwnd.ui

# Anti-trash ;)
OBJECTS_DIR = temp
MOC_DIR = temp
UI_DIR = temp
RCC_DIR = temp
