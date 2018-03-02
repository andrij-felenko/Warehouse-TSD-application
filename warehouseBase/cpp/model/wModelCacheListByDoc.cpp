#include "wModelCacheListByDoc.h"
#include "wSingleton.h"

WModelCacheListByDoc::WModelCacheListByDoc(QString name, WDocumentBase* document, WJson::WJson_enum jsonKey,
                                           QVariantMap map, QObject *parent)
    : WModelListTemplate(name, parent), m_document(document), m_jsonKey(jsonKey), m_map(map)
{
    update();

    QObject::connect(document, &WDocumentBase::documentLineUpdate, this, &WModelCacheListByDoc::update);
}

QVariant WModelCacheListByDoc::data(const QModelIndex& index, int role) const
{
    if (index.row() > m_list.length() and index.row() < 0)
        return QVariant();

    auto single = WCache::get().getOne(m_list.at(index.row()), m_jsonKey);
    if (single == nullptr)
        return QVariant();

    QVariantMap tempMap(m_map);
    tempMap.insert(single->id(), +m_jsonKey);

    switch (static_cast <WEnum::ModelItems> (role)) {
    case WEnum::Model_item: return QVariant::fromValue(single);
    case WEnum::Model_barcode: return single->barcode();
    case WEnum::Model_name: return single->name();
    case WEnum::Model_id: return single->id();
    case WEnum::Model_actualQuantity: return m_document->getQuantity(WEnum::LineActual, tempMap);
    case WEnum::Model_planQuantity: return m_document->getQuantity(WEnum::LinePlan, tempMap);
    default:;
    }

    return QVariant();
}

int WModelCacheListByDoc::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_list.length();
}

bool WModelCacheListByDoc::containsId(QString id)
{
    return m_list.contains(id);
}

bool WModelCacheListByDoc::containsBarcode(QString barcode)
{
    for (auto it : m_list)
        if (WCache::get().container()->getOne(it)->barcode() == barcode)
            return true;
    return false;
}

WDocumentBase*WModelCacheListByDoc::document()
{
    return m_document;
}

void WModelCacheListByDoc::update()
{
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    m_list.clear();
    endRemoveRows();

    if (m_document == nullptr)
        return;

    QStringList list(m_document->getCacheListByParameters(WEnum::LineActual, m_jsonKey, m_map));

    std::sort(list.begin(), list.end(), [=](QString f, QString s){
        switch (sort()) {
        case WEnum::SortByAZ: return f > s;
        case WEnum::SortByZA: return f < s;
        default:;
        return false;
        }
    });

    beginInsertRows(QModelIndex(), 0, list.length() - 1);
    m_list = list;
    endInsertRows();

    emit dataChanged(this->index(0), this->index(list.length() - 1));
}
