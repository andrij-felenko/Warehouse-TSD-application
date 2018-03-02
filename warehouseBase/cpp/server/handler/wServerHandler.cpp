#include "wServerHandler.h"
#include "wSingleton.h"

WServerHandler::WServerHandler(QObject *parent) : WHandlerTemplate(parent)
{
    typedef WUrlEnum WUE;
    registrateUrl({ WUE::Get, WUE::Employee, WUE::By, WUE::Id }, WEnum::Request_must_server);
    registrateUrl({ WUE::Get, WUE::Employee, WUE::List },        WEnum::Request_must_server);

    registrateUrl({ WUE::Get,    WUE::Cell, WUE::By, WUE::Id },      WEnum::Request_can_ignore);
    registrateUrl({ WUE::Get,    WUE::Cell, WUE::By, WUE::Barcode }, WEnum::Request_must_server);
    registrateUrl({ WUE::Update, WUE::Cell, WUE::Cache },            WEnum::Request_can_ignore);

    registrateUrl({ WUE::Get, WUE::Container, WUE::By, WUE::Barcode }, WEnum::Request_must_server);
    registrateUrl({ WUE::Get, WUE::Container, WUE::By, WUE::Id },      WEnum::Request_can_ignore);
    registrateUrl({ WUE::Update, WUE::Container, WUE::Cache },         WEnum::Request_can_ignore);

    registrateUrl({ WUE::Get,    WUE::Nomenclature, WUE::By, WUE::Id }, WEnum::Request_can_ignore);
    registrateUrl({ WUE::Update, WUE::Nomenclature, WUE::Cache },       WEnum::Request_can_ignore);

    registrateUrl({ WUE::Get,    WUE::Supplier, WUE::By, WUE::Id }, WEnum::Request_can_ignore);
    registrateUrl({ WUE::Update, WUE::Supplier, WUE::Cache },       WEnum::Request_can_ignore);

    registrateUrl({ WUE::Get,    WUE::Warehouse, WUE::By, WUE::Id }, WEnum::Request_can_ignore);
    registrateUrl({ WUE::Update, WUE::Warehouse, WUE::Cache },       WEnum::Request_can_ignore);

    registrateUrl({ WUE::Get,    WUE::Consignment, WUE::By, WUE::Nomenclature }, WEnum::Request_can_ignore);
    registrateUrl({ WUE::Get,    WUE::Consignment, WUE::By, WUE::Id },           WEnum::Request_can_ignore);
    registrateUrl({ WUE::Update, WUE::Consignment, WUE::Cache },                 WEnum::Request_can_ignore);

    registrateUrl({ WUE::Get, WUE::Quality, WUE::List },            WEnum::Request_can_ignore);
    registrateUrl({ WUE::Get, WUE::Storage, WUE::Unit, WUE::List }, WEnum::Request_can_ignore);

    registrateUrl({ WUE::Reserve,   WUE::Container }, WEnum::Request_must_server);
    registrateUrl({ WUE::Unreserve, WUE::Container }, WEnum::Request_must_server);

    registrateUrl({ WUE::Set, WUE::Allotted,  WUE::Line }, WEnum::Request_can_cache);
    registrateUrl({ WUE::Set, WUE::Picking,   WUE::Line }, WEnum::Request_can_cache);
    registrateUrl({ WUE::Set, WUE::Purchase,  WUE::Line }, WEnum::Request_can_cache);
    registrateUrl({ WUE::Set, WUE::Receiving, WUE::Line }, WEnum::Request_can_cache);

    registrateUrl({ WUE::Update, WUE::Allotted,  WUE::Line }, WEnum::Request_can_cache);
    registrateUrl({ WUE::Update, WUE::Picking,   WUE::Line }, WEnum::Request_can_cache);
    registrateUrl({ WUE::Update, WUE::Purchase,  WUE::Line }, WEnum::Request_can_cache);
    registrateUrl({ WUE::Update, WUE::Receiving, WUE::Line }, WEnum::Request_can_cache);

    registrateUrl({ WUE::Remove, WUE::Allotted,  WUE::Line }, WEnum::Request_can_cache);
    registrateUrl({ WUE::Remove, WUE::Picking,   WUE::Line }, WEnum::Request_can_cache);
    registrateUrl({ WUE::Remove, WUE::Purchase,  WUE::Line }, WEnum::Request_can_cache);
    registrateUrl({ WUE::Remove, WUE::Receiving, WUE::Line }, WEnum::Request_can_cache);

    registrateUrl({ WUE::Get, WUE::Allotted,  WUE::Document }, WEnum::Request_can_cache);
    registrateUrl({ WUE::Get, WUE::Picking,   WUE::Document }, WEnum::Request_can_cache);
    registrateUrl({ WUE::Get, WUE::Purchase,  WUE::Document }, WEnum::Request_can_cache);
    registrateUrl({ WUE::Get, WUE::Receiving, WUE::Document }, WEnum::Request_can_cache);

    registrateUrl({ WUE::Get, WUE::Allotted,  WUE::Document, WUE::List }, WEnum::Request_must_server);
    registrateUrl({ WUE::Get, WUE::Picking,   WUE::Document, WUE::List }, WEnum::Request_must_server);
    registrateUrl({ WUE::Get, WUE::Purchase,  WUE::Document, WUE::List }, WEnum::Request_must_server);
    registrateUrl({ WUE::Get, WUE::Receiving, WUE::Document, WUE::List }, WEnum::Request_must_server);
}

bool WServerHandler::handler(QList<WUrlEnum::WUrl_enum> url, WJson* json)
{
    typedef WUrlEnum WUE;

    if (not isContains(url)){
        WMessage::get().setWarningMessage(WUrlConverter::compareUrl(url)
                                          + QObject::tr(" не был обработан, не найден соответствующий метод."),
                                          WEnum::Priority_middle);
        return false;
    }

    // VOCABLURARY --------------------------------------------------------------------------------
    if (WUrlConverter::isEqual(url, { WUE::Get, WUE::Employee, WUE::By, WUE::Id }))
        getEmployee(json);
    else if (WUrlConverter::isEqual(url, { WUE::Get, WUE::Employee, WUE::List })){
        getEmployee(json);
        WCache::get().employee()->setUpdateDateTime();
    }

    if (url.first() == WUE::Update and url.at(2) == WUE::Cache)
        switch (url.at(1)){
        case WUE::Cell: WCache::get().cell()->setUpdateDateTime(); break;
        case WUE::Container: WCache::get().container()->setUpdateDateTime(); break;
        case WUE::Consignment: WCache::get().consignment()->setUpdateDateTime(); break;
        case WUE::Nomenclature: WCache::get().nomenclature()->setUpdateDateTime(); break;
        default:;
        }

    if (       WUrlConverter::isEqual(url, { WUE::Get,    WUE::Cell, WUE::By, WUE::Id })
            or WUrlConverter::isEqual(url, { WUE::Get,    WUE::Cell, WUE::By, WUE::Barcode })
            or WUrlConverter::isEqual(url, { WUE::Update, WUE::Cell, WUE::Cache }))
        getCell(json);

    else if (   WUrlConverter::isEqual(url, { WUE::Get,    WUE::Container, WUE::By, WUE::Barcode })
             or WUrlConverter::isEqual(url, { WUE::Get,    WUE::Container, WUE::By, WUE::Id })
             or WUrlConverter::isEqual(url, { WUE::Update, WUE::Container, WUE::Cache }))
        getContainer(json);

    else if (   WUrlConverter::isEqual(url, { WUE::Get,    WUE::Nomenclature, WUE::By, WUE::Id })
             or WUrlConverter::isEqual(url, { WUE::Update, WUE::Nomenclature, WUE::Cache }))
        getNomenclature(json);

    else if (   WUrlConverter::isEqual(url, { WUE::Get,    WUE::Supplier, WUE::By, WUE::Id })
             or WUrlConverter::isEqual(url, { WUE::Update, WUE::Supplier, WUE::Cache }))
        getSupplierList(json);

    else if (   WUrlConverter::isEqual(url, { WUE::Get,    WUE::Warehouse, WUE::By, WUE::Id })
             or WUrlConverter::isEqual(url, { WUE::Update, WUE::Warehouse, WUE::Cache }))
        getWarehouseList(json);

    else if (   WUrlConverter::isEqual(url, { WUE::Get,    WUE::Consignment, WUE::By, WUE::Nomenclature })
             or WUrlConverter::isEqual(url, { WUE::Get,    WUE::Consignment, WUE::By, WUE::Id })
             or WUrlConverter::isEqual(url, { WUE::Update, WUE::Consignment, WUE::Cache }))
        getConsignment(json);

    else if (WUrlConverter::isEqual(url, { WUE::Get, WUE::Quality, WUE::List }))
        getQualityList(json);

    else if (WUrlConverter::isEqual(url, { WUE::Get, WUE::Storage, WUE::Unit, WUE::List }))
        getStorageUnitList(json);

    // RESERVE - UNRESERVE CONTAINER --------------------------------------------------------------
    else if (WUrlConverter::isEqual(url, { WUE::Reserve, WUE::Container }))
        reserveContainer(json);

    else if (WUrlConverter::isEqual(url, { WUE::Unreserve, WUE::Container }))
        unreserveContainer(json);

    // DOCUMENT -----------------------------------------------------------------------------------
    else if (url.length() == 3 and url.at(0) == WUE::Set and url.at(2) == WUE::Line)
        setLine(json);

    else if (url.length() == 3 and url.at(0) == WUE::Update and url.at(2) == WUE::Line)
        updateLine(json);

    else if (url.length() == 3 and url.at(0) == WUE::Remove and url.at(2) == WUE::Line)
        removeLine(json);

    else if (url.length() == 3 and url.at(0) == WUE::Get and url.at(2) == WUE::Document)
        getDocument(json);

    else if (url.length() == 4 and url.at(0) == WUE::Get and url.at(2) == WUE::Document and url.at(3) == WUE::List)
        getDocumentList(json);

    else
        return false;

    return true;
}

void WServerHandler::getEmployee(WJson* json)
{
    WCache::get().employee()->update(json->json().toArray());
}

void WServerHandler::getCell(WJson* json)
{
    WCache::get().cell()->update(json->json().toArray());
}

void WServerHandler::getContainer(WJson* json)
{
    WCache::get().container()->update(json->json().toArray());
}

void WServerHandler::getNomenclature(WJson* json)
{
    WCache::get().nomenclature()->update(json->json().toArray());
}

void WServerHandler::getConsignment(WJson* json)
{
    WCache::get().consignment()->update(json->json().toArray());
}

void WServerHandler::getQualityList(WJson* json)
{
    WCache::get().quality()->update(json->json().toArray());
}

void WServerHandler::getStorageUnitList(WJson* json)
{
    WCache::get().storage_type()->update(json->json().toArray());
}

void WServerHandler::getSupplierList(WJson* json)
{
    WCache::get().supplier()->update(json->json().toArray());
}

void WServerHandler::getWarehouseList(WJson* json)
{
    WCache::get().warehouse()->update(json->json().toArray());
}

void WServerHandler::reserveContainer(WJson* json)
{
    if (testJsonDocumentResult(json))
        WDocument::get().getDocument(WJsonConverter::get(json->json(),
                                                         WJsonEnum::Document_id).toString())
                ->acceptedReserveContainer(json, false);
}

void WServerHandler::unreserveContainer(WJson* json)
{
    if (testJsonDocumentResult(json))
        WDocument::get().getDocument(WJsonConverter::get(json->json(),
                                                WJsonEnum::Document_id).toString())
                ->acceptedUnreserveContainer(json, false);
}

void WServerHandler::setLine(WJson* json)
{
    if (testJsonDocumentResult(json))
        WDocument::get().getDocument(WJsonConverter::get(json->json(), WJsonEnum::Document_id).toString())
                ->acceptedSetLine(json);
}

void WServerHandler::updateLine(WJson* json)
{
    if (testJsonDocumentResult(json))
        WDocument::get().getDocument(WJsonConverter::get(json->json(),
                                                WJsonEnum::Document_id).toString())->acceptedUpdateLine(json);
}

void WServerHandler::removeLine(WJson* json)
{
    if (testJsonDocumentResult(json))
        WDocument::get().getDocument(WJsonConverter::get(json->json(),
                                                WJsonEnum::Document_id).toString())->acceptedRemoveLine(json);
}

void WServerHandler::getDocument(WJson* json)
{
    if (testJsonDocumentResult(json))
        WDocument::get().getDocument(WJsonConverter::get(json->json(),
                                                WJsonEnum::Document_id).toString())->writeLines(json->json());
}

void WServerHandler::getDocumentList(WJson* json)
{
    WDocument::get().updateDocumentList(json, WUrlEnum::Receiving);
}

bool WServerHandler::testJsonDocumentResult(WJson* json)
{
    if (WServer::get().cache()->getOne(json->request()) == nullptr){
        WMessage::get().setWarningMessage("Url: " + json->url() + "\nЗапрос " + json->request()
                                         + QObject::tr(" не удалось найти в кеше."),
                                         WEnum::Priority_middle);
        return false;
    }

    if (WDocument::get().getDocument(WJsonConverter::get(json->json(),
                                                         WJsonEnum::Document_id).toString()) == nullptr){
        WMessage::get().setWarningMessage(QObject::tr("Error: ") + QObject::tr(" не найден document_id."),
                                         WEnum::Priority_middle);
        return false;
    }

    return true;
}
