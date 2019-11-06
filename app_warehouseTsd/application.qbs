import qbs
import "../../../qbs/app.qbs" as App

App {
    projectName: "warehouse_tsd"
    cpp.includePaths: base.concat([ 'cpp', '../whBase/cpp' ])

    Depends { name: "lib_warehouseBaseLib" }
}
