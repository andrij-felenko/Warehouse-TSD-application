#ifndef MODELCACHELIST_H
#define MODELCACHELIST_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QObject>
#include "enum/wenum.h"
#include "enum/wstatic.h"
#include "template/cacheListTemplate.h"

template <typename T> //FIXME add current choose item and write sey, update and other
class ModelCacheList : public QAbstractListModel
{
public:
    explicit ModelCacheList(T* cache, QObject *parent = nullptr);

    QHash <int, QByteArray> rolesNames() const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent) const override;

    Q_INVOKABLE bool containsBarcode(QString barcode);
    Q_INVOKABLE bool containsId(QString id);

private:
    CacheListTemplate <T>* cache;
    QHash <int, QByteArray> roles;

    void updateAll();
    void insertLines(QStringList list);
    void updateLines(QStringList list);
    void removeLines(QStringList list);
};

#endif // MODELCACHELIST_H
