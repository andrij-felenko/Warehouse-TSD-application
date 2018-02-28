#ifndef WTESTHANDLER_H
#define WTESTHANDLER_H

#include "wSingleton.h"
#include "server/wRequestGenerate.h"
#include "QDebug"

void testVocabulary()
{
    QJsonArray array;
    for (int i = 0; i < 3; i++){
        QString id(WStatic::guidCreate());
        QJsonObject obj;
        WJson::insert(obj, WJson::Id, id);
        WJson::insert(obj, WJson::Password, "123");
        WJson::insert(obj, WJson::Name, id.left(6));
        array.push_back(QJsonValue(obj));
    }
    auto *req = new WJsonTemplate(WUrl::compareUrl({ WUrl::Get, WUrl::Employee, WUrl::List }),
                                  QJsonValue(array));
    WServer::get().requestHandler()->sendRequest(WUrl::disunite(req->url()), req);
}

void testDocumentReceivingList()
{
    QJsonArray array;
    for (int i = 0; i < 12; i++){
        WDocumentHeader header;
        header.setId(WStatic::guidCreate());
        header.setName("name:" + header.id().left(6));
        header.setSupplier("supplier:" + header.id().right(3));
        header.setStatus(static_cast <WEnum::DocumentStatus> (+WEnum::Document_created + rand()%4));
        array.push_back(header.toJson());
    }
    auto *req = new WJsonTemplate(WUrl::compareUrl({ WUrl::Get, WUrl::Receiving, WUrl::Document, WUrl::List }),
                                  QJsonValue(array));
    WServer::get().requestHandler()->sendRequest(WUrl::disunite(req->url()), req);
}

#endif // TESTHANDLER_H
