#ifndef MODELCACHELIST_H
#define MODELCACHELIST_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QObject>
#include "enum/wenum.h"
#include "enum/wstatic.h"
#include "cache/single/cacheSingle.h"
#include "template/cacheListTemplate.h"
#include "QDebug"

template <typename T>
class ModelCacheList : public QAbstractListModel
{
public:
    explicit ModelCacheList(T* cache, QObject *parent = nullptr)
        : QAbstractListModel(parent), cache(cache)
    {
        roles[WEnum::Model_item] = "m_item";
        roles[WEnum::Model_id] = "m_id";
        roles[WEnum::Model_name] = "m_name";
        roles[WEnum::Model_barcode] = "m_barcode";
        insertLines(cache->getIdList());

        QObject::connect(cache, &CacheListObject::listPoped,   this, &ModelCacheList::removeLines);
        QObject::connect(cache, &CacheListObject::listPushed,  this, &ModelCacheList::insertLines);
        QObject::connect(cache, &CacheListObject::listUpdated, this, &ModelCacheList::updateLines);
    }

    QHash <int, QByteArray> roleNames() const override
    {
        return roles;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        if (index.row() < 0 and m_list.length() < index.row() + 1)
            return QVariant();

        auto item = cache->getOne(index.row());
        if (item == nullptr)
            return QVariant();

        switch(static_cast <WEnum::ModelItems> (role)) {
        case WEnum::Model_item: return QVariant::fromValue(item);
        case WEnum::Model_id: return item->id();
        case WEnum::Model_name: return item->name();
        case WEnum::Model_barcode: return item->barcode();
        default:;
        }
        return QVariant();
    }

public slots:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        Q_UNUSED(parent)
        return cache->count();
    }

    bool containsBarcode(QString barcode) { return cache->containsBarcode(barcode); }
    bool containsId(QString id) { return cache->containsId(id); }

private:
    T* cache;
    QHash <int, QByteArray> roles;
    QStringList m_list;

    void updateAll()
    {
        emit dataChanged(this->index(0, 0), this->index(rowCount() - 1, 0));
    }

    void insertLines(QStringList list)
    {
        m_list.append(list);
        emit dataChanged(this->index(rowCount() - 1), this->index(rowCount() - 1 + list.length()));
//        emit dataChanged(this->index(0, 0), this->index(rowCount() - 1, 0));
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
