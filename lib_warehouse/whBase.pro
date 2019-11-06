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
TARGET = whBase

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
    cpp/cache/single/wContainerSingle.cpp \
    cpp/cache/single/wEmployeeSingle.cpp \
    cpp/cache/single/wNomenclatureSingle.cpp \
    cpp/cache/single/wQualitySingle.cpp \
    cpp/cache/wCachePrototype.cpp \
    cpp/document/base/wDocumentBase.cpp \
    cpp/document/base/wDocumentHeader.cpp \
    cpp/document/line/wLineActual.cpp \
    cpp/document/line/wLinePlan.cpp \
    cpp/document/wDocumentPrototype.cpp \
    cpp/enum/wEnum.cpp \
    cpp/enum/wJsonEnum.cpp \
    cpp/enum/wUrlEnum.cpp \
    cpp/message/wMessagePrototype.cpp \
    cpp/model/wModelCacheListByDoc.cpp \
    cpp/model/wModelDocumentList.cpp \
    cpp/model/wModelPrototype.cpp \
    cpp/server/cache/wServerCache.cpp \
    cpp/server/cache/wServerCacheSingle.cpp \
    cpp/server/handler/wHandlerTemplate.cpp \
    cpp/server/handler/wServerHandler.cpp \
    cpp/server/handler/wServerHandlerManager.cpp \
    cpp/server/wRequestGenerate.cpp \
    cpp/server/wServerPrototype.cpp \
    cpp/setting/wSettingPrototype.cpp \
    cpp/setting/wSettingServer.cpp \
    cpp/template/wModelListTemplate.cpp \
    cpp/view/wCurrentUser.cpp \
    cpp/view/wView.cpp \
    cpp/wclass/wConverter.cpp \
    cpp/wclass/wJson.cpp \
    cpp/wBase.cpp \
    cpp/wclass/wJsonConverter.cpp \
    cpp/wclass/wUrlConverter.cpp

HEADERS += \
    cpp/barcode/wBarcodePrototype.h \
    cpp/cache/list/wCacheListObject.h \
    cpp/cache/single/wCacheSingle.h \
    cpp/cache/single/wCellSingle.h \
    cpp/cache/single/wConsignmentSingle.h \
    cpp/cache/single/wContainerSingle.h \
    cpp/cache/single/wEmployeeSingle.h \
    cpp/cache/single/wNomenclatureSingle.h \
    cpp/cache/single/wQualitySingle.h \
    cpp/cache/wCachePrototype.h \
    cpp/document/base/wDocumentBase.h \
    cpp/document/base/wDocumentHeader.h \
    cpp/document/line/wLineActual.h \
    cpp/document/line/wLinePlan.h \
    cpp/document/wDocumentPrototype.h \
    cpp/enum/wEnum.h \
    cpp/enum/wJsonEnum.h \
    cpp/enum/wUrlEnum.h \
    cpp/message/wMessagePrototype.h \
    cpp/message/wMessageSingle.h \
    cpp/model/wModelCacheList.h \
    cpp/model/wModelCacheListByDoc.h \
    cpp/model/wModelDocumentList.h \
    cpp/model/wModelPrototype.h \
    cpp/server/cache/wServerCache.h \
    cpp/server/cache/wServerCacheSingle.h \
    cpp/server/handler/wHandlerTemplate.h \
    cpp/server/handler/wServerHandler.h \
    cpp/server/handler/wServerHandlerManager.h \
    cpp/server/wRequestGenerate.h \
    cpp/server/wServerPrototype.h \
    cpp/setting/wSettingPrototype.h \
    cpp/setting/wSettingServer.h \
    cpp/template/wCacheListTemplate.h \
    cpp/template/wModelListTemplate.h \
    cpp/template/wTemplateSingleton.h \
    cpp/view/wCurrentUser.h \
    cpp/view/wView.h \
    cpp/wclass/wConverter.h \
    cpp/wclass/wJson.h \
    cpp/wclass/wStatic.h \
    cpp/wclass/wTuple.h \
    cpp/wBase.h \
    cpp/wBase_global.h \
    cpp/wSingleton.h \
    cpp/wclass/wJsonConverter.h \
    cpp/wclass/wUrlConverter.h


DISTFILES += \
    jsonAPI.pdf \
