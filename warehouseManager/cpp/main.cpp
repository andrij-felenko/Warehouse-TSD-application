#include "wSingleton.h"
#include "wBase.h"
#include "model.h"

#include "testHandler.h"

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    WBase* module = new WBase(__DATE__, &app);
    module->registrateApp("0.2", "Lefromazh warehouse manager", "Lefromazh", "http://wh-tech.com.ua");
    WSetting::get().server()->setDefaultWorkingDomain("");
    WSetting::get().server()->setDefaultTestingDomain("http://138.201.225.55/leformazh/hs/tcd-http/");
    WSetting::get().server()->setDefaultName("Admin");
    WSetting::get().server()->setDefaultPassword("WMS#2016");

    module->init();
    module->registrateTypes();
    module->setContextProperty("Model", new Model(module));
//    WMessage::get().setShowingPriority(WEnum::Priority_high);

    module->loadQML(QUrl("qrc:/qml/qml/main.qml"));
    module->start();

    // tests json sender from sender
//    if (WCache::get().employee()->length() == 0)
//        testVocabulary();
    testDocumentReceivingList();

    return app.exec();
}
