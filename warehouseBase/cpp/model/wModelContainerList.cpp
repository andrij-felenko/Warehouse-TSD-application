#include "wModelContainerList.h"
#include "wSingleton.h"

WModelContainerList::WModelContainerList(WDocumentBase* document, QObject *parent)
    : QAbstractListModel(parent), m_document(document), m_sort(WEnum::SortByAZ)
{
    auto cache = WCache::get().container();
    QObject::connect(cache, &WCacheListObject::listPoped,   this, &WModelContainerList::removeCache);
    QObject::connect(cache, &WCacheListObject::listPushed,  this, &WModelContainerList::insertCache);
    QObject::connect(cache, &WCacheListObject::listUpdated, this, &WModelContainerList::updateCache);

    QObject::connect(document, &WDocumentBase::documentLineUpdate, this, &WModelContainerList::updateDocument);
}

QHash<int, QByteArray> WModelContainerList::roleNames() const
{
    return WEnum::getModelHash();
}

QVariant WModelContainerList::data(const QModelIndex& index, int role) const
{
    // FIXME
}

int WModelContainerList::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_containerList.length();
}

bool WModelContainerList::containsId(QString id)
{
    for (auto it : m_containerList)
        if (it->id() == id)
            return true;
    return false;
}

bool WModelContainerList::containsBarcode(QString barcode)
{
    for (auto it : m_containerList)
        if (it->barcode() == barcode)
            return true;
    return false;
}

void WModelContainerList::updateDocument()
{
    //
}

void WModelContainerList::insertCache(QStringList list)
{
    //
}

void WModelContainerList::updateCache(QStringList list)
{
    for (auto it : m_containerList)
        if (list.contains(it->id())){
            it->fromJson(WCache::get().container()->getOne(it->id())->toJson());
            continue;
        }
}

void WModelContainerList::removeCache(QStringList list)
{
    for (auto it : m_containerList)
        if (list.contains(it->id())){
            auto position = m_containerList.indexOf(it);
            beginRemoveRows(this->index(0), position, position);
            m_containerList.removeOne(it);
            it->deleteLater();
            endRemoveRows();
        }
}
