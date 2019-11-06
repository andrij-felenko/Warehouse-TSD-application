#ifndef WSERVERHANDLER_H
#define WSERVERHANDLER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "wHandlerTemplate.h"

class WServerHandler : public WHandlerTemplate
{
    Q_OBJECT
public:
    explicit WServerHandler(QObject *parent = nullptr);

    bool handler(QList <WUrlEnum::WUrl_enum> url, WJson* json) override;

private:
    void getEmployee(WJson* json);
    void getCell(WJson* json);
    void getContainer(WJson* json);
    void getConsignment(WJson* json);
    void getNomenclature(WJson* json);
    void getQualityList    (WJson* json);
    void getStorageUnitList(WJson* json);
    void getSupplierList(WJson* json);
    void getWarehouseList(WJson* json);

    void   reserveContainer(WJson* json);
    void unreserveContainer(WJson* json);

    void    setLine(WJson* json);
    void updateLine(WJson* json);
    void removeLine(WJson* json);
    void getDocument(WJson* json);
    void getDocumentList(WJson* json);

    inline bool testJsonDocumentResult(WJson* json);
};

#endif // SERVERHANDLER_H
