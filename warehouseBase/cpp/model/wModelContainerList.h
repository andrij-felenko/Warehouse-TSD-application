#ifndef WMODELCONTAINERLIST_H
#define WMODELCONTAINERLIST_H

#include <QtCore/QObject>
#include <QtCore/QAbstractListModel>
#include "enum/wUrl.h"
#include "document/base/wDocumentBase.h"
#include "cache/single/wContainerSingle.h"

class WModelContainerList : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit WModelContainerList(WDocumentBase *document, QObject *parent = nullptr);

    QHash <int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;

public slots:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool containsId(QString id);
    bool containsBarcode(QString barcode);

private:
    WDocumentBase *m_document;
    WEnum::Sort m_sort;
    QStringList m_containerList;

    void updateDocument();
    void insertCache(QStringList list);
    void updateCache(QStringList list);
    void removeCache(QStringList list);
};

#endif // WMODELCONTAINERLIST_H
