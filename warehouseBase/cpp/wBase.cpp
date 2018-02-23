#include <QtGui/QGuiApplication>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickView>

#include "wBase.h"
#include "wSingleton.h"
#include "enum/wurl.h"

WBase::WBase(QObject* parent) : QObject(parent)
{
    m_view = new WView;

    qmlRegisterType <WEnum> ("WEnum", 1, 0, "WEnum");
    qmlRegisterType <WJson> ("WJson", 1, 0, "WJson");
    qmlRegisterType <WUrl>  ("WUrl",  1, 0, "WUrl");

    qmlRegisterType <WDocumentBase>   ("WDocument", 1, 0, "WDocument");
    qmlRegisterType <WDocumentHeader> ("WDocument", 1, 0, "WHeader");

    qmlRegisterType <WLineActual> ("WLine", 1, 0, "WLineActual");
    qmlRegisterType <WLinePlan>   ("WLine", 1, 0, "WLinePlan");

    QObject::connect(qApp, &QGuiApplication::applicationNameChanged,    this, &WBase::appNameChanged);
    QObject::connect(qApp, &QGuiApplication::organizationNameChanged,   this, &WBase::orgNameChanged);
    QObject::connect(qApp, &QGuiApplication::organizationDomainChanged, this, &WBase::orgDomainChanged);
    QObject::connect(qApp, &QGuiApplication::applicationVersionChanged, this, &WBase::versionChanged);
}

void WBase::registrateApp(QString version, QString appName, QString orgName, QString orgDomain)
{
    QGuiApplication::setApplicationVersion(version);
    QGuiApplication::setApplicationName(appName);
    QGuiApplication::setOrganizationName(orgName);
    QGuiApplication::setOrganizationDomain(orgDomain);
}

void WBase::registrateTypes()
{
    QQmlContext* root = m_view->rootContext();
    root->setContextProperty("WApp",    this);
    root->setContextProperty("WCache",   WCache::registrate());
    root->setContextProperty("WModel",   WModel::registrate());
    root->setContextProperty("WServer",  WServer::registrate());
    root->setContextProperty("WSetting", WSetting::registrate());
    root->setContextProperty("WMsg",     WMessage::registrate());
    root->setContextProperty("WUser",    WUser::registrate());

//    qmlRegisterType <MessageSingle> ("MsgSingle", 0, 1, "MsgSingle");
    WCache  ::get().registerType();
    WSetting::get().registerType();
}

void WBase::quit()
{
    qDebug() << "try quit";
    qApp->quit();
}

QGuiApplication* WBase::app()
{
    return qApp;
}

void WBase::init()
{
    WSetting ::instance(this);
    WMessage ::instance(this);
    WServer  ::instance(this);
    WCache   ::instance(this);
    WDocument::instance(this);
    WUser    ::instance(this);
    WModel   ::instance(m_view);
}

void WBase::loadQML(const QUrl& url)
{
    m_view->load(url);
}

void WBase::start()
{
    m_view->show();
}

void WBase::setContextProperty(QString key, QObject* obj)
{
    m_view->rootContext()->setContextProperty(key, obj);
}
