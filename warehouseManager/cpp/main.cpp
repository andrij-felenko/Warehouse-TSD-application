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

    QJsonArray array;
    array.push_back("buka");
    array.push_back("buka2");
    array.push_back("buka3");
    QJsonObject obj = WJson::createObject({ std::make_pair(WJson::Actual, "test msg"),
                                            std::make_pair(WJson::Barcode, "test msg"),
                                            std::make_pair(WJson::Name, "test msg")});
    obj.insert("array", array);

    Server::get().request("getUserList", "test msg", obj);

    return app.exec();
}
