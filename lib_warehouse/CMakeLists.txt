cmake_minimum_required(VERSION 3.14)
project(lib_warehouse)

set (wh_h
    include/wBase.h
    include/wBase_global.h
    include/wSingleton.h
    include/barcode/wBarcodePrototype.h
    include/cache/wCachePrototype.h
    include/cache/list/wCacheListObject.h
    include/cache/single/wCacheSingle.h
    include/cache/single/wCellSingle.h
    include/cache/single/wConsignmentSingle.h
    include/cache/single/wContainerSingle.h
    include/cache/single/wEmployeeSingle.h
    include/cache/single/wNomenclatureSingle.h
    include/cache/single/wQualitySingle.h
    include/document/wDocumentPrototype.h
    include/document/base/wDocumentBase.h
    include/document/base/wDocumentHeader.h
    include/document/line/wLineActual.h
    include/document/line/wLinePlan.h
    include/enum/wEnum.h
    include/enum/wJsonEnum.h
    include/enum/wUrlEnum.h
    include/message/wMessagePrototype.h
    include/message/wMessageSingle.h
    include/model/wModelCacheList.h
    include/model/wModelCacheListByDoc.h
    include/model/wModelDocumentList.h
    include/model/wModelPrototype.h
    include/server/wRequestGenerate.h
    include/server/wServerPrototype.h
    include/server/cache/wServerCache.h
    include/server/cache/wServerCacheSingle.h
    include/server/handler/wHandlerTemplate.h
    include/server/handler/wServerHandler.h
    include/server/handler/wServerHandlerManager.h
    include/setting/wSettingPrototype.h
    include/setting/wSettingServer.h
    include/template/wCacheListTemplate.h
    include/template/wModelListTemplate.h
    include/template/wTemplateSingleton.h
    include/view/wCurrentUser.h
    include/view/wView.h
    include/wclass/wConverter.h
    include/wclass/wJson.h
    include/wclass/wJsonConverter.h
    include/wclass/wStatic.h
    include/wclass/wTuple.h
    include/wclass/wUrlConverter.h
    )

set (wh_cpp
    src/wBase.cpp
    src/barcode/wBarcodePrototype.cpp
    src/cache/wCachePrototype.cpp
    src/cache/single/wCacheSingle.cpp
    src/cache/single/wCellSingle.cpp
    src/cache/single/wConsignmentSingle.cpp
    src/cache/single/wContainerSingle.cpp
    src/cache/single/wEmployeeSingle.cpp
    src/cache/single/wNomenclatureSingle.cpp
    src/cache/single/wQualitySingle.cpp
    src/document/wDocumentPrototype.cpp
    src/document/base/wDocumentBase.cpp
    src/document/base/wDocumentHeader.cpp
    src/document/line/wLineActual.cpp
    src/document/line/wLinePlan.cpp
    src/enum/wEnum.cpp
    src/enum/wJsonEnum.cpp
    src/enum/wUrlEnum.cpp
    src/message/wMessagePrototype.cpp
    src/model/wModelCacheListByDoc.cpp
    src/model/wModelDocumentList.cpp
    src/model/wModelPrototype.cpp
    src/server/wRequestGenerate.cpp
    src/server/wServerPrototype.cpp
    src/server/cache/wServerCache.cpp
    src/server/cache/wServerCacheSingle.cpp
    src/server/handler/wHandlerTemplate.cpp
    src/server/handler/wServerHandler.cpp
    src/server/handler/wServerHandlerManager.cpp
    src/setting/wSettingPrototype.cpp
    src/setting/wSettingServer.cpp
    src/template/wModelListTemplate.cpp
    src/view/wCurrentUser.cpp
    src/view/wView.cpp
    src/wclass/wConverter.cpp
    src/wclass/wJson.cpp
    src/wclass/wJsonConverter.cpp
    src/wclass/wUrlConverter.cpp
    )

set (CMAKE_AUTORCC)
find_package(Qt6 COMPONENTS Core Qml Quick)

add_library(lib_warehouse SHARED ${wh_h} ${wh_cpp})

set_target_properties(lib_warehouse PROPERTIES OUTPUT_NAME "warehouse")
target_include_directories(lib_warehouse PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(lib_warehouse Qt6::Core Qt6::Quick Qt6::Qml)
