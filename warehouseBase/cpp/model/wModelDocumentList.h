#ifndef WMODELDOCUMENTLIST_H
#define WMODELDOCUMENTLIST_H

#include <QtCore/QObject>
#include <QtCore/QAbstractListModel>
#include "document/base/wDocumentBase.h"
#include <QtCore/QMap>
#include "enum/wUrl.h"

class WModelDocumentList : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit WModelDocumentList(WUrl::WUrl_enum key, QObject *parent = nullptr);

    QHash <int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;

public slots:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool containsId(QString id);

private:
    WUrl::WUrl_enum key;
    WEnum::Sort m_sort;
    QList <WDocumentBase*> m_list;

    void updateAll();
};

#endif // MODELDOCUMENTLIST_H
