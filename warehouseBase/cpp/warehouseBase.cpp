#include <QtGui/QGuiApplication>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickView>

#include "warehouseBase.h"
#include "singleton.h"
#include "enum/wurl.h"

WarehouseBase::WarehouseBase(QObject* parent) : QObject(parent)
{
    m_view = new View;

    qmlRegisterType <WEnum> ("WEnum", 1, 0, "WEnum");
    qmlRegisterType <WJson> ("WJson", 1, 0, "WJson");
    qmlRegisterType <WUrl>  ("WUrl",  1, 0, "WUrl");
}

void WarehouseBase::registrateApp()
{
    QGuiApplication::setApplicationVersion("0.1");
    QGuiApplication::setApplicationName("Warehouse manager");
    QGuiApplication::setOrganizationName("Warehouse manager");
    QGuiApplication::setOrganizationDomain("http://wh-tech.com.ua");
}

void WarehouseBase::registrateTypes()
{
    QQmlContext* root = m_view->rootContext();
    root->setContextProperty("WApp",    m_view);
    root->setContextProperty("Cache",   Cache::registrate());
    root->setContextProperty("Model",   Model::registrate());
    root->setContextProperty("Server",  Server::registrate());
    root->setContextProperty("Setting", Setting::registrate());

//    qmlRegisterType <MessageSingle> ("MsgSingle", 0, 1, "MsgSingle");
    Cache  ::get().registerType();
    Setting::get().registerType();
}

void WarehouseBase::init()
{
    Setting ::instance(this);
    Message ::instance(this);
    Server  ::instance(this);
    Cache   ::instance(this);
    Document::instance(this);
    Model   ::instance(m_view);
}

void WarehouseBase::loadQML(const QUrl& url)
{
    m_view->load(url);
}

void WarehouseBase::start()
{
    m_view->show();
}
