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
        ../TranslatorBase/ttWord.cpp \
	../TranslatorBase/ttBasicWordInformation.cpp \
	../PersianParser/PersianParser.cpp \
	../EnglishParser/EnglishParser.cpp \
    aboutwindow.cpp \
    addwordwindow.cpp



HEADERS  += mainwindow.h\
        ../TranslatorBase/TranslatorTools.h\
        ../TranslatorBase/ttArray.h\
        ../TranslatorBase/ttDictionary.h\
        ../TranslatorBase/ttFileIOManager.h\
        ../TranslatorBase/ttMacros.h\
        ../TranslatorBase/ttMemoryManager.h\
	../TranslatorBase/ttObject.h\
        ../TranslatorBase/ttObjectPool.h\
        ../TranslatorBase/ttParser.h\
        ../TranslatorBase/ttWord.h\
	../TranslatorBase/ttBasicWordInformation.h \
	../PersianParser/PersianParser.h \
	../EnglishParser/EnglishParser.h \
    aboutwindow.h \
    addwordwindow.h


FORMS    += mainwindow.ui \
    aboutwindow.ui \
    addwordwindow.ui
