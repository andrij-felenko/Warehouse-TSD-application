#include "serverPrototype.h"
#include "singleton.h"
#include "requestGenerate.h"

ServerPrototype::ServerPrototype(QObject *parent) : QNetworkAccessManager(parent)
{
    m_serverCache = new ServerCache(this);
}

// from QML
void ServerPrototype::request(QList<int> url, int version, QString msg,
                              QJsonObject json, int priority,
                              QObject* senderObject, QString functionName)
{
    request(WUrl::compareUrl(url, static_cast <WEnum::Version> (version)), msg, json,
            static_cast <WEnum::Request_priority> (priority), senderObject, functionName);
}

// FIXME
void ServerPrototype::request(QString url, QString msg,
                              QJsonObject json, WEnum::Request_priority priority,
                              QObject* senderObject, QString functionName)
{
    Q_UNUSED(msg)

    // send message
    QString id_msg;
    switch (priority){
    case WEnum::Request_can_cache:
        id_msg = Message::get().setMessage(msg, WEnum::Msg_progress, WEnum::Priority_middle);
        break;
    case WEnum::Request_just_info:
        id_msg = Message::get().setMessage(msg, WEnum::Msg_progress, WEnum::Priority_middle_bellow);
        break;
    case WEnum::Request_must_server:
        id_msg = Message::get().setMessage(msg, WEnum::Msg_progress, WEnum::Priority_middle_above);
        break;
    default:;
    }

    // create request object
    auto serverRequest = new ServerCacheSingle(senderObject, functionName, url, id_msg, json, this, priority);

    // send request to server cache system
    m_serverCache->add(serverRequest);

    // send request to server
    post(url, serverRequest->json()->toJsonDocument());
}

// FIXME
void ServerPrototype::authentificate(QNetworkReply *reply, QAuthenticator *auth)
{
    Q_UNUSED(reply);
    auth->setUser(Setting::get().server()->name());
    auth->setPassword(Setting::get().server()->password());
    get(QNetworkRequest(QUrl(Setting::get().server()->domain())));
    qDebug() << Setting::get().server()->name() << Setting::get().server()->password()
             << Setting::get().server()->domain();
//    if (! Cache::get().employee()->is_authorizate())
//        get(WUrl::composeUrl({ WUrl::Get, WUrl::Employee, WUrl::List }));
}

// FIXME
void ServerPrototype::handler(QNetworkReply *reply)
{
    Q_UNUSED(reply)
    //
}

// FIXME
void ServerPrototype::reconnect()
{
    //
}

void ServerPrototype::get(QString url)
{
    qDebug() << QString("Get at " + QTime::currentTime().toString("hh:mm:ss.zzz")
                        + "   URL:" + url + "   " + Setting::get().server()->domain() + url)
                .leftJustified(120, '-');
    qDebug() << QString().leftJustified(120, '-') << '\n';

    get(QNetworkRequest(QUrl(Setting::get().server()->domain() + url)));
}

void ServerPrototype::post(QString url, QJsonDocument document)
{
    qDebug() << QString("Post at " + QTime::currentTime().toString("hh:mm:ss.zzz")
                        + "   URL:" + url + "   " + Setting::get().server()->domain() + url)
                .leftJustified(120, '-');
    qDebug() << "document" << document;
    qDebug() << QString().leftJustified(120, '-') << '\n';

    QNetworkRequest request;
    request.setUrl(QUrl(Setting::get().server()->domain() + url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QVariant("application/x-www-form-urlencoded"));
    post(request, document.toJson());
}
