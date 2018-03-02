#include "wServerCacheSingle.h"
#include "wSingleton.h"

WServerCacheSingle::WServerCacheSingle(QObject* sender, QString functionName, QString url, QString id_msg,
                                       QJsonValue json, QObject* parent, WEnum::Request_priority priority)
    : QObject(parent), m_sender(sender), m_functionName(functionName), m_id_msg(id_msg),
      m_json(new WJson(url, json, this)), m_priority(priority), m_status(WEnum::SCache_created)
{
    //
}

WServerCacheSingle::WServerCacheSingle(QObject* sender, QString functionName, QString url, QString id_msg,
                                       QObject* parent)
    : WServerCacheSingle(sender, functionName, url, id_msg, QJsonObject(), parent)
{
    //
}

WServerCacheSingle::~WServerCacheSingle()
{
    // WARNING why i do this?
//    WMessage::get().removeMessage(m_id_msg);
}

QByteArray WServerCacheSingle::formRequest() const
{
    return m_json->toJsonDocument().toJson();
}

QObject*WServerCacheSingle::sender() const
{
    return m_sender;
}

QString WServerCacheSingle::functionName() const
{
    return m_functionName;
}

QString WServerCacheSingle::id_msg() const
{
    return m_id_msg;
}

WJson*WServerCacheSingle::json() const
{
    return m_json;
}

WEnum::Request_priority WServerCacheSingle::priority() const
{
    return m_priority;
}

WEnum::ServerCacheStatus WServerCacheSingle::status() const
{
    return m_status;
}

int WServerCacheSingle::secAfterRequest() const
{
    return m_json->dateTime().secsTo(QDateTime::currentDateTime());
}

void WServerCacheSingle::setStatus(WEnum::ServerCacheStatus status)
{
    m_status = status;
}
