#include <QtGui/QGuiApplication>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickView>

//#include "enum.h"
//#include "json.h"
//#include "url.h"
//#include "static.h"
//#include "singleton.h"

//#include "barcode/barcodeprototype.h"
//#include "server/requestGenerate.h"
#include "view/view.h"
#include "enum/url.h"

int main(int argc, char** argv)
{
    // register app info ---------------------------------------------------------------------------
    QGuiApplication app(argc, argv);
    QGuiApplication::setApplicationVersion("0.1");
    QGuiApplication::setApplicationName("Warehouse manager");
    QGuiApplication::setOrganizationName("Warehouse manager");
    QGuiApplication::setOrganizationDomain("http://wh-tech.com.ua");

    // create qml view object ----------------------------------------------------------------------
    View* view = new View;

    // create singleton object ---------------------------------------------------------------------
//    Singleton::instance(view);

    // declare C++ classes to qml ------------------------------------------------------------------
//    qmlRegisterType <Enum> ("Enum", 1, 0, "Enum");
//    qmlRegisterType <Json> ("Json", 1, 0, "Json");
//    qmlRegisterType <Url>  ("Url",  1, 0, "Url");

//    Cache::get().registerType();
//    Document::get().registerType();
//    Settings::get().registerType();

    // set context property ------------------------------------------------------------------------
    QQmlContext* root = view->rootContext();
//    root->setContextProperty("Barcode", new BarcodeHandler);
//    root->setContextProperty("Request", new Requestor);
//    root->setContextProperty("Static",  new Static());

//    root->setContextProperty("Cache",    Cache::registrate());
//    root->setContextProperty("Document", Document::registrate());
//    root->setContextProperty("Model",    Model::registrate());
//    root->setContextProperty("Msg",      Message::registrate());
//    root->setContextProperty("Server",   Server::registrate());
//    root->setContextProperty("Setting",  Settings::registrate());

    root->setContextProperty("Eridon_app", view);
    qDebug() << Url::compareUrl({ Url::Accept, Url::Allotted, Url::All });
    qDebug() << Url::disunite("acceptAllocatedAllList");
    for (auto it : Url::disunite("acceptAllocatedAllList"))
        qDebug() << it << Url::toString(it);

    // start program -------------------------------------------------------------------------------
    view->resize(400, 550);
    view->load();

    return app.exec();
}
