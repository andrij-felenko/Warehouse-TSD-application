#include "modelCacheList.h"

//template<typename T>
//ModelCacheList<T>::ModelCacheList(T* cache, QObject *parent)
//    : QAbstractListModel(parent), cache(cache)
//{
//    roles[WEnum::Model_item] = "m_item";
//    insertLines(cache->getIdList());

//    QObject::connect(cache, &CacheListObject::listPoped,   this, &ModelCacheList::removeLines);
//    QObject::connect(cache, &CacheListObject::listPushed,  this, &ModelCacheList::insertLines);
//    QObject::connect(cache, &CacheListObject::listUpdated, this, &ModelCacheList::updateLines);
//}

//template<typename T>
//QHash<int, QByteArray> ModelCacheList<T>::rolesNames() const
//{

//}

//template<typename T>
//QVariant ModelCacheList<T>::data(const QModelIndex& index, int role) const
//{
//    if (index.row() < 0)
//        return QVariant();

//    switch(static_cast <WEnum::ModelItems> (role)) {
//    case WEnum::Model_item: {
//        auto item = cache->getOne(index.row());
//        if (item != nullptr)
//            return item;
//    }
//    default:;
//    }
//    return QVariant();
//}

//template<typename T>
//int ModelCacheList<T>::rowCount(const QModelIndex& parent) const
//{
//    Q_UNUSED(parent)
//    return cache->count();
//}

//template<typename T>
//bool ModelCacheList<T>::containsBarcode(QString barcode)
//{
//    return cache->containsBarcode(barcode);
//}

//template<typename T>
//bool ModelCacheList<T>::containsId(QString id)
//{
//    return cache->containsId(id);
//}

//template<typename T>
//void ModelCacheList<T>::updateAll()
//{
//    emit dataChanged(this->index(0), this->index(rowCount() - 1));
//}

//template<typename T>
//void ModelCacheList<T>::insertLines(QStringList list)
//{
//    m_list.append(list);
//    emit dataChanged(QModelIndex(), rowCount() - 1, rowCount() - 1 + list.length());
//    //    int i(0);
//    //    for (auto sendIt : list){
//    //        i = 0;
//    //        for (auto it : m_list){
//    //            i++;
//    //            if (it > sendIt){
//    //                beginInsertRows(QModelIndex(), --i, i);
//    //                m_list.push_back(sendIt);
//    //                endInsertRows();
//    //                break;
//    //            }
//    //        }
//    //    }
//}

//template<typename T>
//void ModelCacheList<T>::updateLines(QStringList list)
//{
//    int i(0);
//    for (auto sendIt : list){
//        i = 0;
//        for (auto it : m_list){
//            if (it == sendIt){
//                emit dataChanged(this->index(--i), this->index(i));
//                break;
//            }
//            i++;
//        }
//    }
//}

//template<typename T>
//void ModelCacheList<T>::removeLines(QStringList list)
//{
//    int i(0);
//    for (auto sendIt : list){
//        i = 0;
//        for (auto it : m_list){
//            i++;
//            if (it == sendIt){
//                beginRemoveRows(QModelIndex(), --i, i);
//                m_list.removeOne(sendIt);
//                endRemoveRows();
//                break;
//            }
//        }
//    }
//}
