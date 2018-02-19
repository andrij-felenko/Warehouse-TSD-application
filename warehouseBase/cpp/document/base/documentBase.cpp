#include "documentBase.h"
#include "singleton.h"
#include "server/requestGenerate.h"

DocumentBase::DocumentBase(WUrl::WUrl_enum documentKey, QObject *parent)
    : DocumentHeader(parent), documentKey(documentKey)
{
    m_currentActual = new LineActual(this);
    m_currentPlan = new LinePlan(this);
}

void DocumentBase::writeHeader(QJsonValue value)
{
    DocumentHeader::fromJson(value.toObject());
}

void DocumentBase::writeLines(QJsonValue value)
{
    QJsonObject obj(value.toObject());

    if (not WJson::contains(obj, WJson::Document_header)){
        Message::get().setWarningMessage(QObject::tr("У документа отсутствует шапка, чтение невозможно"),
                                         WEnum::Priority_middle);
        return;
    }

    resetAll();
    writeHeader(WJson::get(obj, WJson::Document_header));
    for (auto it : WJson::get(obj, WJson::Plan).toArray())
        plan.push_back(new LinePlan(it.toObject(), this));
    for (auto it : WJson::get(obj, WJson::Actual).toArray())
        actual.push_back(new LineActual(it.toObject(), this));
}

void DocumentBase::acceptedUpdateLine(WJsonTemplate* json)
{
    auto line_id = WJson::get(json->json(), WJson::Line_id).toString();
    for (auto it : actual)
        if (it->lineId() == line_id){
            it->fromJson(json->json().toObject());
            break;
        }
}

void DocumentBase::acceptedSetLine(WJsonTemplate* json)
{
    auto line_id = WJson::get(json->json(), WJson::Line_id).toString();
    for (auto it : actual)
        if (it->lineId() == line_id)
            return;
    actual.push_back(new LineActual(json->json().toObject(), this));
}

void DocumentBase::acceptedRemoveLine(WJsonTemplate* json)
{
    auto line_id = WJson::get(json->json(), WJson::Line_id).toString();
    for (auto it : actual)
        if (it->lineId() == line_id){
            actual.removeOne(it);
            it->deleteLater();
            return;
        }
}

void DocumentBase::acceptedReserveContainer(WJsonTemplate* json, bool sender)
{
    auto container = WJson::get(json->json(), WJson::Container_id).toString();
    for (auto it : actual)
        if ((not sender and it->containerReceiverId() == container)
                or (sender and it->containerSenderId() == container))
            it->setEmployeeId(""); // FIXME
}

void DocumentBase::acceptedUnreserveContainer(WJsonTemplate* json, bool sender)
{
    auto container = WJson::get(json->json(), WJson::Container_id).toString();
    for (auto it : actual)
        if ((not sender and it->containerReceiverId() == container)
                or (sender and it->containerSenderId() == container))
            it->resetEmployeeId();
}

void DocumentBase::chooseLine(QString id)
{
    for (auto it : actual)
        if (it->lineId() == id){
            currentActual()->fromJson(it->toJson());
            break;
        }
}

bool DocumentBase::chooseNextLine(QVariantMap map)
{
    QJsonObject obj;
    int line_number(-1);
    for (auto it : plan)
        if (not it->isDone())
            if (it->lineNumber() >= 0 and it->lineNumber() < line_number){
                bool isAcceptMap(true);
                QJsonObject tempJson(it->toJson());
                for (auto subIt = map.begin(); subIt != map.end(); ++subIt){
                    auto key = static_cast <WJson::WJson_enum> (subIt.value().toInt());
                    if (WJson::contains(tempJson, key))
                        if (WJson::get(tempJson, key).toString() != subIt.key()){
                            isAcceptMap = false;
                            break;
                        }
                }
                if (isAcceptMap){
                    obj = tempJson;
                    line_number = it->lineNumber();
                }
            }
    if (obj.isEmpty())
        return false;

    currentPlan()->fromJson(obj);
    return true;
}

void DocumentBase::createLine(QVariantMap map)
{
    currentActual()->clear();
    auto obj = currentActual()->toJson();
    for (auto it = map.begin(); it != map.end(); ++it)
        WJson::insert(obj, static_cast <WJson::WJson_enum> (it.value().toInt()), it.key());
    currentActual()->fromJson(obj);
}

void DocumentBase::saveLine(QObject* senderObj, QString funcName)
{
    for (auto it : actual)
        if (it->lineId() == currentActual()->lineId()){
            Server::get().request(WUrl::compareUrl({ WUrl::Update, documentKey, WUrl::Line }),
                                  QObject::tr("Обновить строку."),
                                  RequestGenerate::actualLine(currentActual()->toJson(), this->id()),
                                  WEnum::Request_can_cache, senderObj, funcName);
            return;
        }
    Server::get().request(WUrl::compareUrl({ WUrl::Set, documentKey, WUrl::Line }),
                          QObject::tr("Установить новую строку."),
                          RequestGenerate::actualLine(currentActual()->toJson(), this->id()),
                          WEnum::Request_can_cache, senderObj, funcName);
}

void DocumentBase::removeLine(QObject* senderObj, QString funcName)
{
    Server::get().request(WUrl::compareUrl({ WUrl::Remove, documentKey, WUrl::Line }),
                          QObject::tr("Удаляем строку."),
                          RequestGenerate::removeLine(currentActual()->lineId(), this->id()),
                          WEnum::Request_can_cache, senderObj, funcName);
}
