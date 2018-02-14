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

INCLUDEPATH += $$PWD/cpp

OTHER_FILES += $$PWD/wcomponent/*.qml

RESOURCES += \
    icon.qrc \
    qml.qrc

SOURCES += \
    cpp/warehouseBase.cpp \
    cpp/barcode/barcodeprototype.cpp \
    cpp/enum/wjson.cpp \
    cpp/enum/wurl.cpp \
    cpp/model/modelPrototype.cpp \
    cpp/view/view.cpp \
    cpp/cache/cachePrototype.cpp \
    cpp/cache/single/cacheSingle.cpp \
    cpp/server/requestGenerate.cpp \
    cpp/server/serverCache.cpp \
    cpp/server/serverPrototype.cpp \
    cpp/setting/settingPrototype.cpp \
    cpp/setting/settingServer.cpp \
    cpp/message/messagePrototype.cpp \
    cpp/server/wjsonTemplate.cpp \
    cpp/cache/single/consignmentSingle.cpp \
    cpp/cache/single/containerSingle.cpp \
    cpp/cache/single/nomenclatureSingle.cpp \
    cpp/cache/single/cellSingle.cpp \
    cpp/cache/single/qualitySingle.cpp \
    cpp/server/handlerTemplate.cpp \
    cpp/server/serverHandlerManager.cpp \
    cpp/server/serverHandler.cpp \
    cpp/cache/single/employeeSingle.cpp \
    cpp/document/line/linePlan.cpp

HEADERS += \
    cpp/enum/wenum.h \
    cpp/enum/wjson.h \
    cpp/enum/wstatic.h \
    cpp/enum/wurl.h \
    cpp/warehouseBase.h \
    cpp/warehousebase_global.h \
    cpp/singleton.h \
    cpp/barcode/barcodeprototype.h \
    cpp/model/modelPrototype.h \
    cpp/template/cacheListTemplate.h \
    cpp/template/templateSingleton.h \
    cpp/view/view.h \
    cpp/cache/cachePrototype.h \
    cpp/cache/list/cacheListObject.h \
    cpp/cache/single/cacheSingle.h \
    cpp/server/requestGenerate.h \
    cpp/server/serverCache.h \
    cpp/server/serverCacheSingle.h \
    cpp/server/serverPrototype.h \
    cpp/setting/settingPrototype.h \
    cpp/setting/settingServer.h \
    cpp/message/messagePrototype.h \
    cpp/message/messageSingle.h \
    cpp/server/wjsonTemplate.h \
    cpp/cache/single/containerSingle.h \
    cpp/cache/single/consignmentSingle.h \
    cpp/cache/single/nomenclatureSingle.h \
    cpp/cache/single/cellSingle.h \
    cpp/cache/single/qualitySingle.h \
    cpp/server/handlerTemplate.h \
    cpp/server/serverHandlerManager.h \
    cpp/server/serverHandler.h \
    cpp/cache/single/employeeSingle.h \
    cpp/document/line/linePlan.h

DISTFILES += \
    jsonAPI.pdf
