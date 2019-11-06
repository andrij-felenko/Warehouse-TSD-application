#ifndef WTESTHANDLER_H
#define WTESTHANDLER_H

#include "wSingleton.h"
#include "server/wRequestGenerate.h"
#include "QDebug"

void testVocabulary()
{
    QJsonArray array;
    for (int i = 0; i < 6; i++){
        QString id(WStatic::guidCreate());
        QJsonObject obj;
        WJsonConverter::insert(obj, WJsonEnum::Id, id);
        WJsonConverter::insert(obj, WJsonEnum::Password, "123");
        WJsonConverter::insert(obj, WJsonEnum::Name, id.left(6));
        array.push_back(QJsonValue(obj));
    }
    auto *req = new WJson(WUrlConverter::compareUrl({ WUrlEnum::Get, WUrlEnum::Employee, WUrlEnum::List }),
                          QJsonValue(array));
    WServer::get().requestHandler()->sendRequest(WUrlConverter::disunite(req->url()), req);
}

void testDocumentReceivingList()
{
    QJsonArray array;
    for (int i = 0; i < 25; i++){
        WDocumentHeader header;
        header.setId(WStatic::guidCreate());
        header.setName("name:" + header.id().left(6));
        header.setDateCreated(QDateTime(QDate(2000 + rand()%18, rand()%12 + 1, rand()%28 + 1)));
        header.setSupplierId("supplier:" + header.id().right(3));
        header.setStatus(static_cast <WEnum::DocumentStatus> (+WEnum::Document_created + rand()%4));
        array.push_back(header.toJson());
    }
    auto *req = new WJson(WUrlConverter::compareUrl({ WUrlEnum::Get, WUrlEnum::Receiving,
                                                      WUrlEnum::Document, WUrlEnum::List }),
                          QJsonValue(array));
    WServer::get().requestHandler()->sendRequest(WUrlConverter::disunite(req->url()), req);
}

#endif // TESTHANDLER_H
