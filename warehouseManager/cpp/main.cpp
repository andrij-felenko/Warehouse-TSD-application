#include "singleton.h"
#include "warehouseBase.h"
#include "whmodel.h"

#include "testhandler.h"

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    WarehouseBase* module = new WarehouseBase;
    module->registrateApp("0.2", "Warehouse Manager", "WHTech", "http://wh-tech.com.ua");
    module->init();
    module->registrateTypes();
    module->setContextProperty("WHModel", new WHModel(module));
    Message::get().setShowingPriority(WEnum::Priority_high | WEnum::Priority_middle);

    module->loadQML(QUrl("qrc:/qml/qml/main.qml"));
    module->start();
//    testVocabulary();

    return app.exec();
}
