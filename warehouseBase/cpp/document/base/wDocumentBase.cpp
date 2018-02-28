#include "wDocumentBase.h"
#include "wSingleton.h"
#include "server/wRequestGenerate.h"

WDocumentBase::WDocumentBase(WUrl::WUrl_enum documentKey, QObject *parent)
    : WDocumentHeader(parent), documentKey(documentKey)
{
    m_currentActual = new WLineActual(this);
    m_currentPlan = new WLinePlan(this);
}

void WDocumentBase::writeHeader(QJsonValue value)
{
    WDocumentHeader::fromJson(value.toObject());
}

void WDocumentBase::writeLines(QJsonValue value)
{
    QJsonObject obj(value.toObject());

    if (not WJson::contains(obj, WJson::Document_header)){
        WMessage::get().setWarningMessage(QObject::tr("У документа отсутствует шапка, чтение невозможно"),
                                          WEnum::Priority_middle);
        return;
    }

    resetAll();
    writeHeader(WJson::get(obj, WJson::Document_header));
    for (auto it : WJson::get(obj, WJson::Plan).toArray())
        plan.push_back(new WLinePlan(it.toObject(), this));
    for (auto it : WJson::get(obj, WJson::Actual).toArray())
        actual.push_back(new WLineActual(it.toObject(), this));

    emit documentLineUpdate(this);
}

void WDocumentBase::acceptedUpdateLine(WJsonTemplate* json)
{
    auto line_id = WJson::get(json->json(), WJson::Line_id).toString();
    for (auto it : actual)
        if (it->lineId() == line_id){
            it->fromJson(json->json().toObject());
            break;
        }
}

void WDocumentBase::acceptedSetLine(WJsonTemplate* json)
{
    auto line_id = WJson::get(json->json(), WJson::Line_id).toString();
    for (auto it : actual)
        if (it->lineId() == line_id)
            return;
    actual.push_back(new WLineActual(json->json().toObject(), this));
}

void WDocumentBase::acceptedRemoveLine(WJsonTemplate* json)
{
    auto line_id = WJson::get(json->json(), WJson::Line_id).toString();
    for (auto it : actual)
        if (it->lineId() == line_id){
            actual.removeOne(it);
            it->deleteLater();
            return;
        }
}

void WDocumentBase::acceptedReserveContainer(WJsonTemplate* json, bool sender)
{
    auto container = WJson::get(json->json(), WJson::Container_id).toString();
    for (auto it : actual)
        if ((not sender and it->containerReceiverId() == container)
                or (sender and it->containerSenderId() == container))
            it->setEmployeeId(""); // FIXME
}

void WDocumentBase::acceptedUnreserveContainer(WJsonTemplate* json, bool sender)
{
    auto container = WJson::get(json->json(), WJson::Container_id).toString();
    for (auto it : actual)
        if ((not sender and it->containerReceiverId() == container)
                or (sender and it->containerSenderId() == container))
            it->resetEmployeeId();
}

QStringList WDocumentBase::getCacheList(WJson::WJson_enum type)
{
    QStringList list;

    for (auto it : actual)
        switch (type){
        case WJson::Cell_id:
            list.push_back(it->cellReceiverId());
            list.push_back(it->cellSenderId());
            break;
        case WJson::Consignment_id:
            list.push_back(it->consignmentId());
            break;
        case WJson::Container_id:
            list.push_back(it->containerReceiverId());
            list.push_back(it->containerSenderId());
            break;
        case WJson::Nomenclature_id:
            list.push_back(it->nomenclatureId());
            break;
        default:;
        }

    if (type == WJson::Cell_id)
        list.append(cellIdList());

    list.removeDuplicates();
    list.removeOne(WStatic::guidDefault());
    list.removeOne(WStatic::guidNull());

    return list;
}

QStringList WDocumentBase::getCacheListByParameters(WEnum::LineType type, WJson::WJson_enum key, QVariantMap map)
{
    QStringList list;

    if (type == WEnum::LineActual or WEnum::LineAll)
        for (auto it : actual)
            if (it->isConcordiaLineByParameter(map))
                list.push_back(it->getVariableByJsonKey(key));

    if (type == WEnum::LinePlan or WEnum::LineAll)
        for (auto it : plan)
            if (it->isConcordiaLineByParameter(map))
                list.push_back(it->getVariableByJsonKey(key));

    list.removeDuplicates();
    list.removeOne(WStatic::guidNull());
    list.removeOne(WStatic::guidDefault());

    return list;
}

int WDocumentBase::getQuantity(WEnum::LineType type, QVariantMap map)
{
    int quantity(0);
    if (type == WEnum::LineActual){
        for (auto it : actual)
            if (it->isConcordiaLineByParameter(map))
                quantity += it->quantity();
    }
    else if (type == WEnum::LinePlan){
        for (auto it : plan)
            if (it->isConcordiaLineByParameter(map))
                quantity += it->quantity();
    }
    return quantity;
}

void WDocumentBase::chooseLine(QString id)
{
    for (auto it : actual)
        if (it->lineId() == id){
            currentActual()->fromJson(it->toJson());
            break;
        }
}

bool WDocumentBase::chooseNextLine(QVariantMap map)
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

void WDocumentBase::createLine(QVariantMap map)
{
    currentActual()->clear();
    auto obj = currentActual()->toJson();
    for (auto it = map.begin(); it != map.end(); ++it)
        WJson::insert(obj, static_cast <WJson::WJson_enum> (it.value().toInt()), it.key());
    currentActual()->fromJson(obj);
}

void WDocumentBase::saveLine(QObject* senderObj, QString funcName)
{
    for (auto it : actual)
        if (it->lineId() == currentActual()->lineId()){
            WServer::get().request(WUrl::compareUrl({ WUrl::Update, documentKey, WUrl::Line }),
                                   QObject::tr("Обновить строку."),
                                   WRequestGenerate::actualLine(currentActual()->toJson(), this->id()),
                                   WEnum::Request_can_cache, senderObj, funcName);
            return;
        }
    WServer::get().request(WUrl::compareUrl({ WUrl::Set, documentKey, WUrl::Line }),
                           QObject::tr("Установить новую строку."),
                           WRequestGenerate::actualLine(currentActual()->toJson(), this->id()),
                           WEnum::Request_can_cache, senderObj, funcName);
}

void WDocumentBase::removeLine(QObject* senderObj, QString funcName)
{
    WServer::get().request(WUrl::compareUrl({ WUrl::Remove, documentKey, WUrl::Line }),
                           QObject::tr("Удаляем строку."),
                           WRequestGenerate::removeLine(currentActual()->lineId(), this->id()),
                           WEnum::Request_can_cache, senderObj, funcName);
}
