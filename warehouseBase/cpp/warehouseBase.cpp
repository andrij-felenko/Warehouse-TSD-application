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
    qmlRegisterType <WUrl>  ("Url",  1, 0, "Url");
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
    root->setContextProperty("WApp",     m_view);
    root->setContextProperty("Cache",    Cache::registrate());
    root->setContextProperty("Model",    Model::registrate());
    root->setContextProperty("Server",   Server::registrate());
    root->setContextProperty("Setting",  Setting::registrate());

//    qmlRegisterType <MessageSingle> ("MsgSingle", 0, 1, "MsgSingle");
    Cache  ::get().registerType();
    Setting::get().registerType();
}

void WarehouseBase::init()
{
    Cache  ::instance(this);
    Message::instance(this);
    Model  ::instance(this);
    Server ::instance(this);
    Setting::instance(this);
}

void WarehouseBase::loadQML(const QUrl& url)
{
    m_view->load(url);
}

void WarehouseBase::start()
{
    m_view->show();
}
