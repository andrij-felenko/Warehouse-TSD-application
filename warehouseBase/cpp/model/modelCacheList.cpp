#include "modelCacheList.h"

template<typename T>
ModelCacheList<T>::ModelCacheList(T* cache, QObject *parent)
    : QAbstractListModel(parent), cache(cache)
{
    roles[WEnum::Model_item] = "m_item";

    QObject::connect(cache, &CacheListObject::listPoped,   this, &ModelCacheList::removeLines);
    QObject::connect(cache, &CacheListObject::listPushed,  this, &ModelCacheList::insertLines);
    QObject::connect(cache, &CacheListObject::listUpdated, this, &ModelCacheList::updateLines);
}

template<typename T>
QHash<int, QByteArray> ModelCacheList<T>::rolesNames() const
{
    return roles;
}

template<typename T>
QVariant ModelCacheList<T>::data(const QModelIndex& index, int role) const
{
    if (index.row() < 0)
        return QVariant();

    switch(static_cast <WEnum::ModelItems> (role)) {
    case WEnum::Model_item: {
        auto item = cache->getOne(index.row());
        if (item != nullptr)
            return item;
    }
    default:;
    }
    return QVariant();
}

template<typename T>
int ModelCacheList<T>::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return cache->count();
}

template<typename T>
bool ModelCacheList<T>::containsBarcode(QString barcode)
{
    return cache->containsBarcode(barcode);
}

template<typename T>
bool ModelCacheList<T>::containsId(QString id)
{
    return cache->containsId(id);
}

template<typename T>
void ModelCacheList<T>::updateAll()
{
    //
}

template<typename T>
void ModelCacheList<T>::insertLines(QStringList list)
{
    //
}

template<typename T>
void ModelCacheList<T>::updateLines(QStringList list)
{
    //
}

template<typename T>
void ModelCacheList<T>::removeLines(QStringList list)
{
    //
}
