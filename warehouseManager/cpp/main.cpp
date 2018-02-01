#include <QtGui/QGuiApplication>
#include "view/view.h"
#include "enum/url.h"
#include "warehouseBase.h"

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    WarehouseBase::registrateApp();

    WarehouseBase module;
    module.init();
    module.registrateTypes();

    module.loadQML(QUrl("qrc:/qml/qml/main.qml"));
    module.start();

    return app.exec();
}
