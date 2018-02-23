#ifndef WWAREHOUSEBASE_H
#define WWAREHOUSEBASE_H

#include "wBase_global.h"
#include "view/wView.h"

class WAREHOUSEBASESHARED_EXPORT WBase : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString appName   READ appName   NOTIFY appNameChanged)
    Q_PROPERTY(QString version   READ version   NOTIFY versionChanged)
    Q_PROPERTY(QString orgName   READ orgName   NOTIFY orgNameChanged)
    Q_PROPERTY(QString orgDomain READ orgDomain NOTIFY orgDomainChanged)

public:
    WBase(QObject *parent = nullptr);

    void registrateApp(QString version = QString("1.0"),
                       QString appName = QString("Warehouse manager"),
                       QString orgName = QString("Warehouse manager"),
                       QString orgDomain = QString("http://wh-tech.com.ua"));

    void init();
    void loadQML(const QUrl& url);
    void registrateTypes();
    void start();
    void setContextProperty(QString key, QObject* obj);

    QString appName()   const { return qApp->applicationName(); }
    QString version()   const { return qApp->applicationVersion(); }
    QString orgName()   const { return qApp->organizationName(); }
    QString orgDomain() const { return qApp->organizationDomain(); }

public slots:
    void quit();
    QGuiApplication* app();

signals:
    void appNameChanged();
    void versionChanged();
    void orgNameChanged();
    void orgDomainChanged();

private:
    WView *m_view;
    QString m_appName;
    QString m_version;
    QString m_orgName;
    QString m_orgDomain;
};

#endif // WAREHOUSEBASE_H
