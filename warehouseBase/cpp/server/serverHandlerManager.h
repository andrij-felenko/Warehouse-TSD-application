#ifndef SERVERHANDLERMANAGER_H
#define SERVERHANDLERMANAGER_H

#include <QtCore/QObject>
#include "handlerTemplate.h"
#include "serverHandler.h"

class ServerHandlerManager : public QObject
{
public:
    explicit ServerHandlerManager(QObject *parent = nullptr);

    bool isUrlContains(QList <WUrl::WUrl_enum> url);
    bool isUrlContains(QString url);
    bool registrate(HandlerTemplate* handler);
    void sendRequest(QList<WUrl::WUrl_enum> url, WJsonTemplate* json);

private:
    ServerHandler* m_baseHandler;
    QList <HandlerTemplate*> m_list;
};

#endif // SERVERHANDLERMANAGER_H
