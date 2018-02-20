#ifndef TESTHANDLER_H
#define TESTHANDLER_H

#include "singleton.h"
#include "server/requestGenerate.h"
#include "QDebug"

void testVocabulary()
{
    QJsonArray array;
    for (int i = 0; i < 12; i++){
        QString id(WStatic::guidCreate());
        QJsonObject obj;
        WJson::insert(obj, WJson::Id, id);
        WJson::insert(obj, WJson::Password, "123");
        WJson::insert(obj, WJson::Name, id.left(6));
        array.push_back(QJsonValue(obj));
    }
    auto *req = new WJsonTemplate(WUrl::compareUrl({ WUrl::Get, WUrl::Employee, WUrl::List }),
                                  QJsonValue(array));
    Server::get().requestHandler()->sendRequest(WUrl::disunite(req->url()), req);
}

#endif // TESTHANDLER_H
