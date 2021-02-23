#include "server/wServerPrototype.h"
#include "wSingleton.h"
#include "server/wRequestGenerate.h"

WServerPrototype::WServerPrototype(QObject *parent) : QNetworkAccessManager(parent)
{
    m_serverCache = new WServerCache(this);
    m_serverHandler = new WServerHandlerManager(this);

    QObject::connect(this, &WServerPrototype::finished, this, &WServerPrototype::handler);
    QObject::connect(this, &WServerPrototype::authenticationRequired, this, &WServerPrototype::authentificate);
    QObject::connect(WSetting::get().server(), &WSettingServer::reconnect, this, &WServerPrototype::reconnect);

    get(QNetworkRequest(QUrl(WSetting::get().server()->domain())));
}

// FIXME
void WServerPrototype::request(QString url, QString msg, QJsonValue json, WEnum::Request_priority priority,
                               QObject* senderObject, QString functionName)
{
    Q_UNUSED(msg)

    // send message
    QString id_msg;
    switch (priority){
    case WEnum::Request_can_cache:
        id_msg = WMessage::get().setMessage(msg, WEnum::Msg_progress, WEnum::Priority_middle_bellow);
        break;
    case WEnum::Request_can_ignore:
        id_msg = WMessage::get().setInformationMessage(msg);
        break;
    case WEnum::Request_must_server:
        id_msg = WMessage::get().setMessage(msg, WEnum::Msg_progress, WEnum::Priority_middle);
        break;
    default:;
    }

    // create request object
    auto serverRequest = new WServerCacheSingle(senderObject, functionName, url, id_msg, json, this, priority);

    // send request to server cache system
    m_serverCache->add(serverRequest);
    qDebug() << serverRequest->json();

    // send request to server
    QNetworkRequest request;
    request.setUrl(QUrl(WSetting::get().server()->domain() + url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      QVariant("application/x-www-form-urlencoded"));
    post(request, serverRequest->formRequest());
    serverRequest->setStatus(WEnum::SCache_send);
}

// from QML
void WServerPrototype::request(QList<int> url, int version, QString msg, QJsonObject json,
                               int priority, QObject* senderObject, QString functionName)
{
    request(WUrlConverter::compareUrl(url, static_cast <WEnum::Version> (version)), msg, json,
            static_cast <WEnum::Request_priority> (priority), senderObject, functionName);
}

void WServerPrototype::request(QString url, QString msg,
                               QJsonObject json, WEnum::Request_priority priority,
                               QObject* senderObject, QString functionName)
{
    request(url, msg, QJsonValue(json), priority, senderObject, functionName);
}

WServerHandlerManager* WServerPrototype::requestHandler()
{
    return m_serverHandler;
}

// FIXME
void WServerPrototype::authentificate(QNetworkReply *reply, QAuthenticator *auth)
{
    Q_UNUSED(reply);
    auth->setUser(WSetting::get().server()->name());
    auth->setPassword(WSetting::get().server()->password());
    get(QNetworkRequest(QUrl(WSetting::get().server()->domain())));
    qDebug() << WSetting::get().server()->name() << WSetting::get().server()->password()
             << WSetting::get().server()->domain();
//    if (! Cache::get().employee()->is_authorizate())
//        get(WUrl::composeUrl({ WUrl::Get, WUrl::Employee, WUrl::List }));
}

// FIXME work with server cache
void WServerPrototype::handler(QNetworkReply *reply)
{
    QString url = reply->request().url().toString();
    url = url.right(url.length() - WSetting::get().server()->domain().length());

    // start request has empty url, and thats why we there skip it
    if (url.isEmpty())
        return;
    qDebug() << "REQUEST: " << url;

    // test request for standart
    WJson* json = new WJson(this);
    auto resultTestRequest = json->fromJsonDocument(QJsonDocument::fromJson(reply->readAll()), true);
    if (not resultTestRequest.first){
        WMessage::get().setWarningMessage(resultTestRequest.second, WEnum::Priority_middle_bellow);
        json->deleteLater();
        return;
    }

    WServerCacheSingle* cacheSingle = m_serverCache->getOne(json->request());
    if (not m_serverHandler->isUrlContains(url)){
        WMessage::get().setWarningMessage(QObject::tr("Не найден обработчик на метод ") + url,
                                          WEnum::Priority_middle_bellow);
        cacheSingle->setStatus(WEnum::SCache_canceled);
        return; // FIXME remove from temp cache
    }

    qDebug() << json;
    cacheSingle->setStatus(WEnum::SCache_takeResult);
    m_serverHandler->sendRequest(WUrlConverter::disunite(url), json);
    json->deleteLater();
    cacheSingle->setStatus(WEnum::SCache_done);
}

// FIXME
void WServerPrototype::reconnect()
{
    get(QNetworkRequest(QUrl(WSetting::get().server()->domain())));
}
