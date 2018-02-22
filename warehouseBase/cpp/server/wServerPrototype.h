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
#include "wServerCache.h"
#include "wServerHandlerManager.h"

class WServerPrototype : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit WServerPrototype(QObject *parent = nullptr);

    void request(QString url, QString msg, QJsonValue json = QJsonValue(),
                 WEnum::Request_priority priority = WEnum::Request_just_info,
                 QObject* senderObject = nullptr, QString functionName = QString(""));
    void request(QString url, QString msg, QJsonObject json = QJsonObject(),
                 WEnum::Request_priority priority = WEnum::Request_just_info,
                 QObject* senderObject = nullptr, QString functionName = QString(""));
    WServerHandlerManager* requestHandler();
    WServerCache* cache() const { return m_serverCache; }

public slots:
    void request(QList <int> url, int version, QString msg, QJsonObject json = QJsonObject(),
                 int priority = static_cast <int> (WEnum::Request_just_info),
                 QObject* senderObject = nullptr, QString functionName = QString(""));

private:
    WServerCache* m_serverCache;
    WServerHandlerManager* m_serverHandler;

    void authentificate(QNetworkReply* reply, QAuthenticator* auth);
    void handler(QNetworkReply* reply);
    void reconnect();
};

#endif // SERVERPROTOTYPE_H
