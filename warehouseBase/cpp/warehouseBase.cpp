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

    QObject::connect(qApp, &QGuiApplication::applicationNameChanged,    this, &WarehouseBase::appNameChanged);
    QObject::connect(qApp, &QGuiApplication::organizationNameChanged,   this, &WarehouseBase::orgNameChanged);
    QObject::connect(qApp, &QGuiApplication::organizationDomainChanged, this, &WarehouseBase::orgDomainChanged);
    QObject::connect(qApp, &QGuiApplication::applicationVersionChanged, this, &WarehouseBase::versionChanged);
}

void WarehouseBase::registrateApp(QString version, QString appName, QString orgName, QString orgDomain)
{
    QGuiApplication::setApplicationVersion(version);
    QGuiApplication::setApplicationName(appName);
    QGuiApplication::setOrganizationName(orgName);
    QGuiApplication::setOrganizationDomain(orgDomain);
}

void WarehouseBase::registrateTypes()
{
    QQmlContext* root = m_view->rootContext();
    root->setContextProperty("WApp",    this);
    root->setContextProperty("Cache",   Cache::registrate());
    root->setContextProperty("Model",   Model::registrate());
    root->setContextProperty("Server",  Server::registrate());
    root->setContextProperty("Setting", Setting::registrate());
    root->setContextProperty("User",    User::registrate());

//    qmlRegisterType <MessageSingle> ("MsgSingle", 0, 1, "MsgSingle");
    Cache  ::get().registerType();
    Setting::get().registerType();
}

void WarehouseBase::quit()
{
    qDebug() << "try quit";
    qApp->quit();
}

QGuiApplication* WarehouseBase::app()
{
    return qApp;
}

void WarehouseBase::init()
{
    Setting ::instance(this);
    Message ::instance(this);
    Server  ::instance(this);
    Cache   ::instance(this);
    Document::instance(this);
    User    ::instance(this);
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

void WarehouseBase::setContextProperty(QString key, QObject* obj)
{
    m_view->rootContext()->setContextProperty(key, obj);
}
