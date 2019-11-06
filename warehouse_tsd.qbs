import qbs

Project {
    name: "warehouse_tsd"

//    SubProject { filePath: "module/module.qbs" }
//    SubProject { filePath: "Plugins/plugins.qbs" }

    references: [
        "app_warehouseTsd/application.qbs",
        "lib_warehouse/whBase.qbs"
    ]
}
