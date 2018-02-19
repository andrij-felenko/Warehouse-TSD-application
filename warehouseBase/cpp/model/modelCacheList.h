#ifndef MODELCACHELIST_H
#define MODELCACHELIST_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QObject>
#include "enum/wenum.h"
#include "enum/wstatic.h"
#include "template/cacheListTemplate.h"

template <typename T>
class ModelCacheList : public QAbstractListModel
{
//    Q_OBJECT
public:
    explicit ModelCacheList(T* cache, QObject *parent = nullptr): QAbstractListModel(parent), cache(cache)
    {
        roles[WEnum::Model_item] = "m_item";
        insertLines(cache->getIdList());

        QObject::connect(cache, &CacheListObject::listPoped,   this, &ModelCacheList::removeLines);
        QObject::connect(cache, &CacheListObject::listPushed,  this, &ModelCacheList::insertLines);
        QObject::connect(cache, &CacheListObject::listUpdated, this, &ModelCacheList::updateLines);
    }

    QHash <int, QByteArray> rolesNames() const { return roles; }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        if (index.row() < 0)
            return QVariant();

        switch(static_cast <WEnum::ModelItems> (role)) {
        case WEnum::Model_item: {
            auto item = cache->getOne(index.row());
            if (item != nullptr)
                return QVariant::fromValue(item);
        }
        default:;
        }
        return QVariant();
    }

    int rowCount(const QModelIndex &parent) const override
    {
        Q_UNUSED(parent)
        return cache->count();
    }

    Q_INVOKABLE bool containsBarcode(QString barcode) { return cache->containsBarcode(barcode); }
    Q_INVOKABLE bool containsId(QString id) { return cache->containsId(id); }

private:
    T* cache;
    QHash <int, QByteArray> roles;
    QStringList m_list;

    void updateAll()
    {
        emit dataChanged(this->index(0), this->index(rowCount() - 1));
    }

    void insertLines(QStringList list)
    {
        m_list.append(list);
        emit dataChanged(/*QModelIndex(), */this->index(0)/*rowCount() - 1*/, this->index(1)/*rowCount() - 1 + list.length()*/);
//        int i(0);
//        for (auto sendIt : list){
//            i = 0;
//            for (auto it : m_list){
//                i++;
//                if (it > sendIt){
//                    beginInsertRows(QModelIndex(), --i, i);
//                    m_list.push_back(sendIt);
//                    endInsertRows();
//                    break;
//                }
//            }
//        }
    }

    void updateLines(QStringList list)
    {
        int i(0);
        for (auto sendIt : list){
            i = 0;
            for (auto it : m_list){
                if (it == sendIt){
                    emit dataChanged(this->index(i - 1), this->index(i));
                    break;
                }
                i++;
            }
        }
    }

    void removeLines(QStringList list)
    {
        int i(0);
        for (auto sendIt : list){
            i = 0;
            for (auto it : m_list){
                i++;
                if (it == sendIt){
                    beginRemoveRows(QModelIndex(), i - 1, i);
                    m_list.removeOne(sendIt);
                    endRemoveRows();
                    break;
                }
            }
        }
    }
};

#endif // MODELCACHELIST_H
