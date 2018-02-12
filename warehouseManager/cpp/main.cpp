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

    Server::get().request("getUserList", "test msg", WJson::createObject(WJson::Name, "test msg"));
    Server::get().request("getUserList", "test msg",
                          WJson::createObject({ std::make_pair(WJson::Actual, "test msg"),
                                              std::make_pair(WJson::Barcode, "test msg"),
                                              std::make_pair(WJson::Name, "test msg")}));

    return app.exec();
}
