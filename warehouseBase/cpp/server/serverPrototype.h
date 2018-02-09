#ifndef SERVERPROTOTYPE_H
#define SERVERPROTOTYPE_H

#include <QtCore/QJsonDocument>
#include <QtCore/QObject>
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include "enum/wurl.h"
#include "enum/wenum.h"
#include "enum/wjson.h"
#include "serverCache.h"

class ServerPrototype : public QNetworkAccessManager
{
    Q_OBJECT
    using QNetworkAccessManager::get;
    using QNetworkAccessManager::post;

public:
    explicit ServerPrototype(QObject *parent = nullptr);

    void request(QString url, QString msg,
                 QJsonObject json = QJsonObject(),
                 WEnum::Request_priority priority = WEnum::Request_just_info,
                 QObject* senderObject = nullptr,
                 QString functionName = QString(""));

public slots:
    void request(QList <int> url, int version, QString msg, QJsonObject json = QJsonObject(),
                 int priority = static_cast <int> (WEnum::Request_just_info),
                 QObject* senderObject = nullptr, QString functionName = QString(""));

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
