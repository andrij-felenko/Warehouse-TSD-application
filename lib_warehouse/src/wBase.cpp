#include <QtGui/QGuiApplication>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickView>

#include "wBase.h"
#include "wSingleton.h"
#include "enum/wUrlEnum.h"
#include "server/wRequestGenerate.h"
#include "wclass/wConverter.h"

WBase::WBase(QString dateCompile, QObject* parent) : QObject(parent),
    m_dateCompile(dateCompile), m_libDateCompile(__DATE__)
{
    m_view = new WView;
    WSetting ::instance(this);

    qmlRegisterType <WEnum>     ("WEnum",     1, 0, "WEnum");
    qmlRegisterType <WJsonEnum> ("WJsonEnum", 1, 0, "WJsonEnum");
    qmlRegisterType <WUrlEnum > ("WUrlEnum",  1, 0, "WUrlEnum");

    qmlRegisterType <WDocumentBase>      ("WDocument", 1, 0, "WDocument");
    qmlRegisterType <WDocumentHeader>    ("WDocument", 1, 0, "WHeader");
    qmlRegisterType <WDocumentPrototype> ("WDocument", 1, 0, "WDocumentList");

    qmlRegisterType <WLineActual> ("WLine", 1, 0, "WLineActual");
    qmlRegisterType <WLinePlan>   ("WLine", 1, 0, "WLinePlan");

    qmlRegisterType <WSettingServer> ("WSetting", 1, 0, "WSettingServer");

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
    root->setContextProperty("WApp",     this);
    root->setContextProperty("WCache",   WCache   ::registrate());
    root->setContextProperty("WDocList", WDocument::registrate());
    root->setContextProperty("WMessage", WMessage ::registrate());
    root->setContextProperty("WModel",   WModel   ::registrate());
    root->setContextProperty("WServer",  WServer  ::registrate());
    root->setContextProperty("WSetting", WSetting ::registrate());
    root->setContextProperty("WUser",    WUser    ::registrate());

    root->setContextProperty("WConverter",     new WConverter      (this));
    root->setContextProperty("WJsonConverter", new WJsonConverter  (this));
    root->setContextProperty("WRequestor",     new WRequestGenerate(this));
    root->setContextProperty("WStatic",        new WStatic         (this));
    root->setContextProperty("WUrlConverter",  new WUrlConverter   (this));
}

void WBase::quit()
{
    qDebug() << "try quit";
    qApp->quit();
}

void WBase::init()
{
    WMessage ::instance(this);
    WServer  ::instance(this);
    WUser    ::instance(this);
    WCache   ::instance(this);
    WDocument::instance(this);
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
