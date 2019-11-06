import qbs
import "../../../qbs/lib_static.qbs" as LibStatic

LibStatic {
    libraryName: "warehouseBaseLib"

    Depends {
        name: "Qt"
        submodules: [ 'quick', 'qml' ]
    }
}
