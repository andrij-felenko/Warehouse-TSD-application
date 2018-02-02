#-------------------------------------------------
#
# Project created by QtCreator 2018-01-29T11:55:21
#
#-------------------------------------------------

QT += core
QT += gui
QT += network
QT += qml
QT += quick
QT -= widgets

TARGET = warehouseBase
TEMPLATE = lib

DEFINES += WAREHOUSEBASE_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

DEPENDPATH += $$PWD/cpp
DEPENDPATH += $$PWD/cpp/enum

INCLUDEPATH += $$PWD/cpp
INCLUDEPATH += $$PWD/cpp/enum

OTHER_FILES += $$PWD/wcomponent/*.qml

RESOURCES += \
    icon.qrc \
    qml.qrc

SOURCES += \
    cpp/warehouseBase.cpp \
    cpp/barcode/barcodeprototype.cpp \
    cpp/enum/json.cpp \
    cpp/enum/url.cpp \
    cpp/model/modelPrototype.cpp \
    cpp/server/requestGenerate.cpp \
    cpp/server/serverPrototype.cpp \
    cpp/setting/settingPrototype.cpp \
    cpp/view/view.cpp \
    cpp/cache/cachePrototype.cpp \
    cpp/cache/single/cacheSingle.cpp \
    cpp/cache/single/containersingle.cpp \
    cpp/server/requestGenerate.cpp \
    cpp/server/serverCache.cpp \
    cpp/server/serverPrototype.cpp \
    cpp/setting/settingPrototype.cpp \
    cpp/setting/settingServer.cpp

HEADERS += \
    cpp/warehouseBase.h \
    cpp/warehousebase_global.h \
    cpp/singleton.h \
    cpp/barcode/barcodeprototype.h \
    cpp/enum/enum.h \
    cpp/enum/json.h \
    cpp/enum/static.h \
    cpp/enum/url.h \
    cpp/model/modelPrototype.h \
    cpp/server/requestGenerate.h \
    cpp/server/serverPrototype.h \
    cpp/setting/settingPrototype.h \
    cpp/template/cacheListTemplate.h \
    cpp/template/templateSingleton.h \
    cpp/view/view.h \
    cpp/cache/cachePrototype.h \
    cpp/cache/list/cacheListObject.h \
    cpp/cache/single/cacheSingle.h \
    cpp/cache/single/containersingle.h \
    cpp/server/requestGenerate.h \
    cpp/server/serverCache.h \
    cpp/server/serverCacheSingle.h \
    cpp/server/serverPrototype.h \
    cpp/setting/settingPrototype.h \
    cpp/setting/settingServer.h
