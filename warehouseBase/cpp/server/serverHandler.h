#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "handlerTemplate.h"

class ServerHandler : public HandlerTemplate
{
    Q_OBJECT
public:
    explicit ServerHandler(QObject *parent = nullptr);

    bool handler(QList <WUrl::WUrl_enum> url, WJsonTemplate* json) override;

private:
    void getEmployee(WJsonTemplate* json);
    void getCell(WJsonTemplate* json);
    void getContainer(WJsonTemplate* json);
    void getConsignment(WJsonTemplate* json);
    void getNomenclature(WJsonTemplate* json);
    void getQualityList    (WJsonTemplate* json);
    void getStorageUnitList(WJsonTemplate* json);

    void   reserveContainer(WJsonTemplate* json);
    void unreserveContainer(WJsonTemplate* json);

    void    setReceivingLine(WJsonTemplate* json);
    void updateReceivingLine(WJsonTemplate* json);
    void removeReceivingLine(WJsonTemplate* json);
    void getReceivingDocument(WJsonTemplate* json);
    void getReceivingDocumentList(WJsonTemplate* json);
};

#endif // SERVERHANDLER_H
