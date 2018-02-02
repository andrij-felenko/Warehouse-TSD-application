#include "serverPrototype.h"

ServerPrototype::ServerPrototype(QObject *parent) : QObject(parent)
{
    m_serverCache = new ServerCache(this);
}

bool ServerPrototype::request(QList<int> url, Enum::Version version, QString msg,
                              QJsonDocument document, int priority,
                              QObject* senderObject, QString functionName)
{
    request(Url::compareUrl(url, version), msg, document, priority, senderObject, functionName);
}

// FIXME
bool ServerPrototype::request(const QString& url, const QString& msg,
                              const QJsonDocument& document, Enum::Request_priority priority,
                              const QObject* senderObject, const QString& functionName)
{
    if (not document.isEmpty())
        if (not Json::contains(document.object(), Json::Request)){
//            Message::get().set_message("Запрос оформлен некоректно",
//                                       Enum::Msg_error, Enum::Priority_high);
            return false;
        }

    // send message
    QString id_msg;
//    switch (priority){
//    case Enum::Request_priority_can_cache:
//        id_msg = Message::get().setMessage(text, Enum::Msg_inquery, Enum::Priority_middle_above);
//        break;
//    case Enum::Request_priority_can_ignore:
//        id_msg = Message::get().setMessage(text, Enum::Msg_inquery, Enum::Priority_middle_above);
//        break;
//    case Enum::Request_priority_must_server:
//        id_msg = Message::get().setMessage(text, Enum::Msg_inquery, Enum::Priority_high);
//        break;
//    default:;
//    }

    // send request to server cache system
    if (document.isEmpty()) // haven`t body, call when try send get request
        m_serverCache->add(new ServerCacheSingle(senderObject, functionName, "", url, id_msg, this));
    else if (Json::contains(document.object(), Json::Request))
        m_serverCache->add(new ServerCacheSingle(senderObject, functionName,
                                                 Json::get(document.object(),
                                                           Json::Request).toString(),
                                                 url, id_msg, document, this, priority));

    // send request to server
    if (document.isEmpty()) // haven`t body, call when try send get request
        get(url);
    else
        post(url, document);

    return true;
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
//        get(Url::composeUrl({ Url::Get, Url::Employee, Url::List }));
}

// FIXME
void ServerPrototype::handler(QNetworkReply *reply)
{
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
