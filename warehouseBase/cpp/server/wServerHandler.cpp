#include "wServerHandler.h"
#include "wSingleton.h"

WServerHandler::WServerHandler(QObject *parent) : WHandlerTemplate(parent)
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

    registrateUrl({ WUrl::Set, WUrl::Allotted,  WUrl::Line });
    registrateUrl({ WUrl::Set, WUrl::Picking,   WUrl::Line });
    registrateUrl({ WUrl::Set, WUrl::Purchase,  WUrl::Line });
    registrateUrl({ WUrl::Set, WUrl::Receiving, WUrl::Line });

    registrateUrl({ WUrl::Update, WUrl::Allotted,  WUrl::Line });
    registrateUrl({ WUrl::Update, WUrl::Picking,   WUrl::Line });
    registrateUrl({ WUrl::Update, WUrl::Purchase,  WUrl::Line });
    registrateUrl({ WUrl::Update, WUrl::Receiving, WUrl::Line });

    registrateUrl({ WUrl::Remove, WUrl::Allotted,  WUrl::Line });
    registrateUrl({ WUrl::Remove, WUrl::Picking,   WUrl::Line });
    registrateUrl({ WUrl::Remove, WUrl::Purchase,  WUrl::Line });
    registrateUrl({ WUrl::Remove, WUrl::Receiving, WUrl::Line });

    registrateUrl({ WUrl::Get, WUrl::Allotted,  WUrl::Document });
    registrateUrl({ WUrl::Get, WUrl::Picking,   WUrl::Document });
    registrateUrl({ WUrl::Get, WUrl::Purchase,  WUrl::Document });
    registrateUrl({ WUrl::Get, WUrl::Receiving, WUrl::Document });

    registrateUrl({ WUrl::Get, WUrl::Allotted,  WUrl::Document, WUrl::List });
    registrateUrl({ WUrl::Get, WUrl::Picking,   WUrl::Document, WUrl::List });
    registrateUrl({ WUrl::Get, WUrl::Purchase,  WUrl::Document, WUrl::List });
    registrateUrl({ WUrl::Get, WUrl::Receiving, WUrl::Document, WUrl::List });
}

bool WServerHandler::handler(QList<WUrl::WUrl_enum> url, WJsonTemplate* json)
{
    if (not isContains(url)){
        WMessage::get().setWarningMessage(WUrl::compareUrl(url)
                                          + QObject::tr(" не был обработан, не найден соответствующий метод."),
                                          WEnum::Priority_middle);
        return false;
    }

    // VOCABLURARY --------------------------------------------------------------------------------
    if (WUrl::isEqual(url, { WUrl::Get, WUrl::Employee, WUrl::By, WUrl::Id }))
        getEmployee(json);
    else if (WUrl::isEqual(url, { WUrl::Get, WUrl::Employee, WUrl::List })){
        qDebug() << "WEEEEEE";
        getEmployee(json);
        WCache::get().employee()->setUpdateDateTime();
    }

    if (url.first() == WUrl::Update and url.at(2) == WUrl::Cache)
        switch (url.at(1)){
        case WUrl::Cell: WCache::get().cell()->setUpdateDateTime(); break;
        case WUrl::Container: WCache::get().container()->setUpdateDateTime(); break;
        case WUrl::Consignment: WCache::get().consignment()->setUpdateDateTime(); break;
        case WUrl::Nomenclature: WCache::get().nomenclature()->setUpdateDateTime(); break;
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

void WServerHandler::getEmployee(WJsonTemplate* json)
{
    WCache::get().employee()->update(json->json().toArray());
}

void WServerHandler::getCell(WJsonTemplate* json)
{
    WCache::get().cell()->update(json->json().toArray());
}

void WServerHandler::getContainer(WJsonTemplate* json)
{
    WCache::get().container()->update(json->json().toArray());
}

void WServerHandler::getNomenclature(WJsonTemplate* json)
{
    WCache::get().nomenclature()->update(json->json().toArray());
}

void WServerHandler::getConsignment(WJsonTemplate* json)
{
    WCache::get().consignment()->update(json->json().toArray());
}

void WServerHandler::getQualityList(WJsonTemplate* json)
{
    WCache::get().quality()->update(json->json().toArray());
}

void WServerHandler::getStorageUnitList(WJsonTemplate* json)
{
    WCache::get().storage_type()->update(json->json().toArray());
}

void WServerHandler::reserveContainer(WJsonTemplate* json)
{
    if (testJsonDocumentResult(json))
        WDocument::get().getDocument(WJson::get(json->json(),
                                                WJson::Document_id).toString())->acceptedReserveContainer(json, false);
}

void WServerHandler::unreserveContainer(WJsonTemplate* json)
{
    if (testJsonDocumentResult(json))
        WDocument::get().getDocument(WJson::get(json->json(),
                                                WJson::Document_id).toString())->acceptedUnreserveContainer(json, false);
}

void WServerHandler::setLine(WJsonTemplate* json)
{
    if (testJsonDocumentResult(json))
        WDocument::get().getDocument(WJson::get(json->json(), WJson::Document_id).toString())->acceptedSetLine(json);
}

void WServerHandler::updateLine(WJsonTemplate* json)
{
    if (testJsonDocumentResult(json))
        WDocument::get().getDocument(WJson::get(json->json(),
                                                WJson::Document_id).toString())->acceptedUpdateLine(json);
}

void WServerHandler::removeLine(WJsonTemplate* json)
{
    if (testJsonDocumentResult(json))
        WDocument::get().getDocument(WJson::get(json->json(),
                                                WJson::Document_id).toString())->acceptedRemoveLine(json);
}

void WServerHandler::getDocument(WJsonTemplate* json)
{
    if (testJsonDocumentResult(json))
        WDocument::get().getDocument(WJson::get(json->json(),
                                                WJson::Document_id).toString())->writeLines(json->json());
}

void WServerHandler::getDocumentList(WJsonTemplate* json)
{
    WDocument::get().updateDocumentList(json, WUrl::Receiving);
}

bool WServerHandler::testJsonDocumentResult(WJsonTemplate* json)
{
    if (WServer::get().cache()->getOne(json->request()) == nullptr){
        WMessage::get().setWarningMessage("Url: " + json->url() + "\nЗапрос " + json->request()
                                         + QObject::tr(" не удалось найти в кеше."),
                                         WEnum::Priority_middle);
        return false;
    }

    if (WDocument::get().getDocument(WJson::get(json->json(), WJson::Document_id).toString()) == nullptr){
        WMessage::get().setWarningMessage(QObject::tr("Error: ") + QObject::tr(" не найден document_id."),
                                         WEnum::Priority_middle);
        return false;
    }

    return true;
}
