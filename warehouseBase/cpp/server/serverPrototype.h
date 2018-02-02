#ifndef SERVERPROTOTYPE_H
#define SERVERPROTOTYPE_H

#include <QtCore/QJsonDocument>
#include <QtCore/QObject>
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include "url.h"
#include "enum.h"
#include "json.h"
#include "singleton.h"
#include "serverCache.h"

class ServerPrototype : public QNetworkAccessManager
{
    Q_OBJECT
    using QNetworkAccessManager::get;
    using QNetworkAccessManager::post;

public:
    explicit ServerPrototype(QObject *parent = nullptr);

    bool request(const QString& url, const QString& msg,
                 const QJsonDocument& document = QJsonDocument(),
                 Enum::Request_priority priority = Enum::Request_just_info,
                 const QObject* senderObject = nullptr,
                 const QString& functionName = QString(""));

public slots:
    bool request(QList <int> url, Enum::Version version, QString msg,
                 QJsonDocument document = QJsonDocument(),
                 int priority = +Enum::Request_just_info,
                 QObject* senderObject = nullptr,
                 QString functionName = QString(""));

signals:

private:
    ServerCache* m_serverCache;

    void authentificate(QNetworkReply* reply, QAuthenticator* auth);
    void handler(QNetworkReply* reply);
    void reconnect();

    // call request to server
    void get(QString url);
    void post(QString url, QJsonDocument document);
};

#endif // SERVERPROTOTYPE_H
