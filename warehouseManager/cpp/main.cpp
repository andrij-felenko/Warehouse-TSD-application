#include <QtGui/QGuiApplication>
#include "warehouseBase.h"
#include "singleton.h"

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);
    WarehouseBase::registrateApp();

    WarehouseBase module;
    module.init();
    module.registrateTypes();
    Message::get().setShowingPriority(WEnum::Priority_high | WEnum::Priority_middle);

    module.loadQML(QUrl("qrc:/qml/qml/main.qml"));
    module.start();

    Server::get().request("getUserList", "tututx", QJsonValue("tt"));
    qDebug() << WEnum::Priority_low << WEnum::Priority_middle_bellow << WEnum::Priority_middle
             << WEnum::Priority_middle_above << WEnum::Priority_high;

    return app.exec();
}
