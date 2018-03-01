#ifndef WSERVERPROTOTYPE_H
#define WSERVERPROTOTYPE_H

#include <QtCore/QJsonDocument>
#include <QtCore/QObject>
#include <QtNetwork/QAuthenticator>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include "enum/wUrl.h"
#include "enum/wEnum.h"
#include "enum/wJson.h"
#include "wServerCache.h"
#include "wServerHandlerManager.h"

class WServerPrototype : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit WServerPrototype(QObject *parent = nullptr);

    void request(QString url, QString msg, QJsonValue json = QJsonValue(),
                 WEnum::Request_priority priority = WEnum::Request_can_ignore,
                 QObject* senderObject = nullptr, QString functionName = QString(""));
    void request(QString url, QString msg, QJsonObject json = QJsonObject(),
                 WEnum::Request_priority priority = WEnum::Request_can_ignore,
                 QObject* senderObject = nullptr, QString functionName = QString(""));
    WServerHandlerManager* requestHandler();
    WServerCache* cache() const { return m_serverCache; }

public slots:
    void request(QList <int> url, int version, QString msg, QJsonObject json = QJsonObject(),
                 int priority = static_cast <int> (WEnum::Request_can_ignore),
                 QObject* senderObject = nullptr, QString functionName = QString(""));

private:
    WServerCache* m_serverCache;
    WServerHandlerManager* m_serverHandler;

    void authentificate(QNetworkReply* reply, QAuthenticator* auth);
    void handler(QNetworkReply* reply);
    void reconnect();
};

#endif // SERVERPROTOTYPE_H
