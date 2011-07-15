#-------------------------------------------------
#
# Project created by QtCreator 2011-07-15T00:52:56
#
#-------------------------------------------------

QT       += core gui

TARGET = TranslatorUI
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x -U__STRICT_ANSI__


SOURCES += main.cpp\
        mainwindow.cpp\
        ../TranslatorBase/ttArray.cpp\
        ../TranslatorBase/ttDictionary.cpp\
        ../TranslatorBase/ttFileIOManager.cpp\
        ../TranslatorBase/ttMemoryManager.cpp\
        ../TranslatorBase/ttObject.cpp\
        ../TranslatorBase/ttObjectPool.cpp\
        ../TranslatorBase/ttParser.cpp\
        ../TranslatorBase/ttWord.cpp \
    aboutwindow.cpp



HEADERS  += mainwindow.h\
        ../TranslatorBase/TranslatorTools.h\
        ../TranslatorBase/ttArray.h\
        ../TranslatorBase/ttDictionary.h\
        ../TranslatorBase/ttFileIOManager.h\
        ../TranslatorBase/ttMacros.h\
        ../TranslatorBase/ttMemoryManager.h\
        ./TranslatorBase/ttObject.h\
        ../TranslatorBase/ttObjectPool.h\
        ../TranslatorBase/ttParser.h\
        ../TranslatorBase/ttWord.h\
        ../TranslatorBase/ttWordInformation.h \
    aboutwindow.h


FORMS    += mainwindow.ui \
    aboutwindow.ui
