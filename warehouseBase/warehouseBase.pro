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

TEMPLATE = lib
TARGET = warehouseBase

DEFINES += WAREHOUSEBASE_LIBRARY
DEFINES += QT_DEPRECATED_WARNINGS

DEPENDPATH += $$PWD/cpp

INCLUDEPATH += $$PWD/cpp

OTHER_FILES += $$PWD/wcomponent/*.qml
OTHER_FILES += $$PWD/icon/*.png

RESOURCES += \
    icon.qrc \
    qml.qrc

SOURCES += \
    cpp/barcode/wBarcodePrototype.cpp \
    cpp/cache/single/wCacheSingle.cpp \
    cpp/cache/single/wCellSingle.cpp \
    cpp/cache/single/wConsignmentSingle.cpp \
    cpp/cache/single/wEmployeeSingle.cpp \
    cpp/cache/single/wQualitySingle.cpp \
    cpp/cache/single/wContainerSingle.cpp \
    cpp/cache/single/wNomenclatureSingle.cpp \
    cpp/cache/wCachePrototype.cpp \
    cpp/document/base/wDocumentBase.cpp \
    cpp/document/base/wDocumentHeader.cpp \
    cpp/document/line/wLineActual.cpp \
    cpp/document/line/wLinePlan.cpp \
    cpp/document/wDocumentPrototype.cpp \
    cpp/message/wMessagePrototype.cpp \
    cpp/model/wModelDocumentList.cpp \
    cpp/model/wModelPrototype.cpp \
    cpp/server/wHandlerTemplate.cpp \
    cpp/server/wRequestGenerate.cpp \
    cpp/server/wJsonTemplate.cpp \
    cpp/server/wServerCache.cpp \
    cpp/server/wServerHandler.cpp \
    cpp/server/wServerHandlerManager.cpp \
    cpp/server/wServerPrototype.cpp \
    cpp/wBase.cpp \
    cpp/setting/wSettingPrototype.cpp \
    cpp/setting/wSettingServer.cpp \
    cpp/view/wView.cpp \
    cpp/view/wCurrentUser.cpp \
    cpp/enum/wEnum.cpp \
    cpp/enum/wJson.cpp \
    cpp/enum/wUrl.cpp \
    cpp/model/wModelCacheListByDoc.cpp \
    cpp/server/wServerCacheSingle.cpp

HEADERS += \
    cpp/document/base/wDocumentBase.h \
    cpp/document/base/wDocumentHeader.h \
    cpp/document/wDocumentPrototype.h \
    cpp/document/line/wLineActual.h \
    cpp/document/line/wLinePlan.h \
    cpp/message/wMessagePrototype.h \
    cpp/message/wMessageSingle.h \
    cpp/model/wModelCacheList.h \
    cpp/model/wModelDocumentList.h \
    cpp/model/wModelPrototype.h \
    cpp/server/wHandlerTemplate.h \
    cpp/server/wJsonTemplate.h \
    cpp/server/wServerPrototype.h \
    cpp/server/wServerHandlerManager.h \
    cpp/server/wServerHandler.h \
    cpp/server/wServerCacheSingle.h \
    cpp/server/wServerCache.h \
    cpp/server/wRequestGenerate.h \
    cpp/setting/wSettingPrototype.h \
    cpp/setting/wSettingServer.h \
    cpp/template/wCacheListTemplate.h \
    cpp/template/wTemplateSingleton.h \
    cpp/view/wView.h \
    cpp/wBase.h \
    cpp/wBase_global.h \
    cpp/wSingleton.h \
    cpp/wclass/wTuple.h \
    cpp/barcode/wBarcodePrototype.h \
    cpp/cache/list/wCacheListObject.h \
    cpp/cache/wCachePrototype.h \
    cpp/cache/single/wCacheSingle.h \
    cpp/cache/single/wCellSingle.h \
    cpp/cache/single/wConsignmentSingle.h \
    cpp/cache/single/wContainerSingle.h \
    cpp/cache/single/wEmployeeSingle.h \
    cpp/cache/single/wNomenclatureSingle.h \
    cpp/cache/single/wQualitySingle.h \
    cpp/view/wCurrentUser.h \
    cpp/enum/wUrl.h \
    cpp/enum/wStatic.h \
    cpp/enum/wJson.h \
    cpp/enum/wEnum.h \
    cpp/model/wModelCacheListByDoc.h

DISTFILES += \
    jsonAPI.pdf \
