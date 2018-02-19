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
    registrateUrl({ WUrl::Update, WUrl::Nomenclature, WUrl::Cache });

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
    if (not isContains(url)){
        Message::get().setWarningMessage(WUrl::compareUrl(url)
                                         + QObject::tr(" не был обработан, не найден соответствующий метод."),
                                         WEnum::Priority_middle);
        return false;
    }

    // VOCABLURARY --------------------------------------------------------------------------------
    if (WUrl::isEqual(url, { WUrl::Get, WUrl::Employee, WUrl::By, WUrl::Id }))
        getEmployee(json);
    else if (WUrl::isEqual(url, { WUrl::Get, WUrl::Employee, WUrl::List })){
        getEmployee(json);
        Cache::get().employee()->setUpdateDateTime();
    }

    if (url.first() == WUrl::Update and url.at(2) == WUrl::Cache)
        switch (url.at(1)){
        case WUrl::Cell: Cache::get().cell()->setUpdateDateTime(); break;
        case WUrl::Container: Cache::get().container()->setUpdateDateTime(); break;
        case WUrl::Consignment: Cache::get().consignment()->setUpdateDateTime(); break;
        case WUrl::Nomenclature: Cache::get().nomenclature()->setUpdateDateTime(); break;
        default:;
        }

    if (       WUrl::isEqual(url, { WUrl::Get,    WUrl::Cell, WUrl::By, WUrl::Id })
            or WUrl::isEqual(url, { WUrl::Get,    WUrl::Cell, WUrl::By, WUrl::Barcode })
            or WUrl::isEqual(url, { WUrl::Update, WUrl::Cell, WUrl::Cache }))
        getCell(json);

    else if (   WUrl::isEqual(url, { WUrl::Get,    WUrl::Container, WUrl::By, WUrl::Barcode })
             or WUrl::isEqual(url, { WUrl::Get,    WUrl::Container, WUrl::By, WUrl::Id })
             or WUrl::isEqual(url, { WUrl::Update, WUrl::Container, WUrl::Cache }))
        getContainer(json);

    else if (   WUrl::isEqual(url, { WUrl::Get,    WUrl::Nomenclature, WUrl::By, WUrl::Id })
             or WUrl::isEqual(url, { WUrl::Update, WUrl::Nomenclature, WUrl::Cache }))
        getNomenclature(json);

    else if (   WUrl::isEqual(url, { WUrl::Get,    WUrl::Consignment, WUrl::By, WUrl::Nomenclature })
             or WUrl::isEqual(url, { WUrl::Get,    WUrl::Consignment, WUrl::By, WUrl::Id })
             or WUrl::isEqual(url, { WUrl::Update, WUrl::Consignment, WUrl::Cache }))
        getConsignment(json);

    else if (WUrl::isEqual(url, { WUrl::Get, WUrl::Quality, WUrl::List }))
        getQualityList(json);

    else if (WUrl::isEqual(url, { WUrl::Get, WUrl::Storage, WUrl::Unit, WUrl::List }))
        getStorageUnitList(json);

    // RESERVE - UNRESERVE CONTAINER --------------------------------------------------------------
    else if (WUrl::isEqual(url, { WUrl::Reserve, WUrl::Container }))
        reserveContainer(json);

    else if (WUrl::isEqual(url, { WUrl::Unreserve, WUrl::Container }))
        unreserveContainer(json);

    // DOCUMENT -----------------------------------------------------------------------------------
    else if (url.length() == 3 and url.at(0) == WUrl::Set and url.at(2) == WUrl::Line)
        setLine(json);

    else if (url.length() == 3 and url.at(0) == WUrl::Update and url.at(2) == WUrl::Line)
        updateLine(json);

    else if (url.length() == 3 and url.at(0) == WUrl::Remove and url.at(2) == WUrl::Line)
        removeLine(json);

    else if (url.length() == 3 and url.at(0) == WUrl::Get and url.at(2) == WUrl::Document)
        getDocument(json);

    else if (url.length() == 4 and url.at(0) == WUrl::Get and url.at(2) == WUrl::Document and url.at(3) == WUrl::List)
        getDocumentList(json);

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
    if (testJsonDocumentResult(json))
        Document::get().getDocument(WJson::get(json->json(),
                                               WJson::Document_id).toString())->acceptedReserveContainer(json, false);
}

void ServerHandler::unreserveContainer(WJsonTemplate* json)
{
    if (testJsonDocumentResult(json))
        Document::get().getDocument(WJson::get(json->json(),
                                               WJson::Document_id).toString())->acceptedUnreserveContainer(json, false);
}

void ServerHandler::setLine(WJsonTemplate* json)
{
    if (testJsonDocumentResult(json))
        Document::get().getDocument(WJson::get(json->json(), WJson::Document_id).toString())->acceptedSetLine(json);
}

void ServerHandler::updateLine(WJsonTemplate* json)
{
    if (testJsonDocumentResult(json))
        Document::get().getDocument(WJson::get(json->json(),
                                               WJson::Document_id).toString())->acceptedUpdateLine(json);
}

void ServerHandler::removeLine(WJsonTemplate* json)
{
    if (testJsonDocumentResult(json))
        Document::get().getDocument(WJson::get(json->json(),
                                               WJson::Document_id).toString())->acceptedRemoveLine(json);
}

void ServerHandler::getDocument(WJsonTemplate* json)
{
    if (testJsonDocumentResult(json))
        Document::get().getDocument(WJson::get(json->json(),
                                               WJson::Document_id).toString())->writeLines(json->json());
}

void ServerHandler::getDocumentList(WJsonTemplate* json)
{
    Document::get().updateDocumentList(json, WUrl::Receiving);
}

bool ServerHandler::testJsonDocumentResult(WJsonTemplate* json)
{
    auto cache = Server::get().cache()->getOne(json->request());
    if (cache == nullptr)
        return false; //FIXME error

    if (Document::get().getDocument(WJson::get(json->json(), WJson::Document_id).toString()) == nullptr)
        return false; // FIXME error
    return true;
}
