#include "serverHandler.h"
#include "singleton.h"

ServerHandler::ServerHandler(QObject *parent) : HandlerTemplate(parent)
{
    registrateUrl({ WUrl::Get, WUrl::Employee, WUrl::By, WUrl::Id });
    registrateUrl({ WUrl::Get, WUrl::Employee, WUrl::List });

    registrateUrl({ WUrl::Get,    WUrl::Cell, WUrl::By, WUrl::Id });
    registrateUrl({ WUrl::Get,    WUrl::Cell, WUrl::By, WUrl::Barcode });
    registrateUrl({ WUrl::Update, WUrl::Cell, WUrl::Cache });

    registrateUrl({ WUrl::Get,    WUrl::Container, WUrl::By, WUrl::Barcode });
    registrateUrl({ WUrl::Get,    WUrl::Container, WUrl::By, WUrl::Id });
    registrateUrl({ WUrl::Update, WUrl::Container, WUrl::Cache });

    registrateUrl({ WUrl::Get, WUrl::Nomenclature, WUrl::By, WUrl::Id });
    registrateUrl({ WUrl::Get, WUrl::Nomenclature, WUrl::Cache });

    registrateUrl({ WUrl::Get,    WUrl::Consignment, WUrl::By, WUrl::Nomenclature });
    registrateUrl({ WUrl::Get,    WUrl::Consignment, WUrl::By, WUrl::Id });
    registrateUrl({ WUrl::Update, WUrl::Consignment, WUrl::Cache });

    registrateUrl({ WUrl::Get, WUrl::Quality, WUrl::List });
    registrateUrl({ WUrl::Get, WUrl::Storage, WUrl::Unit, WUrl::List });

    registrateUrl({ WUrl::Reserve,   WUrl::Container });
    registrateUrl({ WUrl::Unreserve, WUrl::Container });

    registrateUrl({ WUrl::Set,    WUrl::Receiving, WUrl::Line });
    registrateUrl({ WUrl::Update, WUrl::Receiving, WUrl::Line });
    registrateUrl({ WUrl::Remove, WUrl::Receiving, WUrl::Line });
    registrateUrl({ WUrl::Get,    WUrl::Receiving, WUrl::Document });
    registrateUrl({ WUrl::Get,    WUrl::Receiving, WUrl::Document, WUrl::List });
}

bool ServerHandler::handler(QList<WUrl::WUrl_enum> url, WJsonTemplate* json)
{
    if (not isContains(url))
        return false;

    if (   WUrl::isEqual(url, { WUrl::Get, WUrl::Employee, WUrl::By, WUrl::Id })
        or WUrl::isEqual(url, { WUrl::Get, WUrl::Employee, WUrl::List }))
        getEmployee(json);

    else if (   WUrl::isEqual(url, { WUrl::Get,    WUrl::Cell, WUrl::By, WUrl::Id })
             or WUrl::isEqual(url, { WUrl::Get,    WUrl::Cell, WUrl::By, WUrl::Barcode })
             or WUrl::isEqual(url, { WUrl::Update, WUrl::Cell, WUrl::Cache }))
        getCell(json);

    else if (   WUrl::isEqual(url, { WUrl::Get,    WUrl::Container, WUrl::By, WUrl::Barcode })
             or WUrl::isEqual(url, { WUrl::Get,    WUrl::Container, WUrl::By, WUrl::Id })
             or WUrl::isEqual(url, { WUrl::Update, WUrl::Container, WUrl::Cache }))
        getContainer(json);

    else if (   WUrl::isEqual(url, { WUrl::Get, WUrl::Nomenclature, WUrl::By, WUrl::Id })
             or WUrl::isEqual(url, { WUrl::Get, WUrl::Nomenclature, WUrl::Cache }))
        getNomenclature(json);

    else if (   WUrl::isEqual(url, { WUrl::Get,    WUrl::Consignment, WUrl::By, WUrl::Nomenclature })
             or WUrl::isEqual(url, { WUrl::Get,    WUrl::Consignment, WUrl::By, WUrl::Id })
             or WUrl::isEqual(url, { WUrl::Update, WUrl::Consignment, WUrl::Cache }))
        getConsignment(json);

    else if (WUrl::isEqual(url, { WUrl::Get, WUrl::Quality, WUrl::List }))
        getQualityList(json);

    else if (WUrl::isEqual(url, { WUrl::Get, WUrl::Storage, WUrl::Unit, WUrl::List }))
        getStorageUnitList(json);

    else if (WUrl::isEqual(url, { WUrl::Reserve, WUrl::Container }))
        reserveContainer(json);

    else if (WUrl::isEqual(url, { WUrl::Unreserve, WUrl::Container }))
        unreserveContainer(json);

    else if (WUrl::isEqual(url, { WUrl::Set, WUrl::Receiving, WUrl::Line }))
        setReceivingLine(json);

    else if (WUrl::isEqual(url, { WUrl::Update, WUrl::Receiving, WUrl::Line }))
        updateReceivingLine(json);

    else if (WUrl::isEqual(url, { WUrl::Remove, WUrl::Receiving, WUrl::Line }))
        removeReceivingLine(json);

    else if (WUrl::isEqual(url, { WUrl::Get, WUrl::Receiving, WUrl::Document }))
        getReceivingDocument(json);

    else if (WUrl::isEqual(url, { WUrl::Get, WUrl::Receiving, WUrl::Document, WUrl::List }))
        getReceivingDocumentList(json);

    else
        return false;

    return true;
}

void ServerHandler::getEmployee(WJsonTemplate* json)
{
    Cache::get().employee()->update(json->json().toArray());
}

void ServerHandler::getCell(WJsonTemplate* json)
{
    Cache::get().cell()->update(json->json().toArray());
}

void ServerHandler::getContainer(WJsonTemplate* json)
{
    Cache::get().container()->update(json->json().toArray());
}

void ServerHandler::getNomenclature(WJsonTemplate* json)
{
    Cache::get().nomenclature()->update(json->json().toArray());
}

void ServerHandler::getConsignment(WJsonTemplate* json)
{
    Cache::get().consignment()->update(json->json().toArray());
}

void ServerHandler::getQualityList(WJsonTemplate* json)
{
    Cache::get().quality()->update(json->json().toArray());
}

void ServerHandler::getStorageUnitList(WJsonTemplate* json)
{
    Cache::get().storage_type()->update(json->json().toArray());
}

void ServerHandler::reserveContainer(WJsonTemplate* json)
{
    //
}

void ServerHandler::unreserveContainer(WJsonTemplate* json)
{
    //
}

void ServerHandler::setReceivingLine(WJsonTemplate* json)
{
    //
}

void ServerHandler::updateReceivingLine(WJsonTemplate* json)
{
    //
}

void ServerHandler::removeReceivingLine(WJsonTemplate* json)
{
    //
}

void ServerHandler::getReceivingDocument(WJsonTemplate* json)
{
    //
}

void ServerHandler::getReceivingDocumentList(WJsonTemplate* json)
{
    Document::get().updateDocumentList(json, WUrl::Receiving);
}
