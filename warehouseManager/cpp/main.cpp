#include "wSingleton.h"
#include "wBase.h"
#include "model.h"

#include "testHandler.h"

int main(int argc, char** argv)
{
    QGuiApplication app(argc, argv);

    WBase* module = new WBase(&app);
    module->registrateApp("0.2", "Warehouse Manager", "WHTech", "http://wh-tech.com.ua");
    module->init();
    module->registrateTypes();
    module->setContextProperty("Model", new Model(module));
    WMessage::get().setShowingPriority(WEnum::Priority_high | WEnum::Priority_middle_above);


    qmlRegisterType <WUrl> ("WUrl", 1, 0, "WUrl");
    module->loadQML(QUrl("qrc:/qml/qml/main.qml"));
    module->start();

    // tests json sender from sender
//    testVocabulary();
    testDocumentReceivingList();

    return app.exec();
}
