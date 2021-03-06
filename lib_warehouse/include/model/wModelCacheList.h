#ifndef WMODELCACHELIST_H
#define WMODELCACHELIST_H

#include "wclass/wStatic.h"
#include "cache/single/wCacheSingle.h"
#include "template/wCacheListTemplate.h"
#include "template/wModelListTemplate.h"

template <typename T>
class WModelCacheList : public WModelListTemplate
{
public:
    explicit WModelCacheList(QString name, T* cache, QObject *parent = nullptr)
        : WModelListTemplate(name, parent), cache(cache)
    {
        insertLines(cache->getIdList());

        QObject::connect(cache, &WCacheListObject::listPoped,   this, &WModelCacheList::removeLines);
        QObject::connect(cache, &WCacheListObject::listPushed,  this, &WModelCacheList::insertLines);
        QObject::connect(cache, &WCacheListObject::listUpdated, this, &WModelCacheList::updateLines);
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
    QStringList m_list;

    virtual void update() override
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
        for (const auto &sendIt : list){
            i = 0;
            for (const auto &it : m_list){
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
        for (const auto &sendIt : list){
            i = 0;
            for (const auto &it : m_list){
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
