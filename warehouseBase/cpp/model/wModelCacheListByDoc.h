#ifndef WMODELCACHELISTBYDOC_H
#define WMODELCACHELISTBYDOC_H

#include <QtCore/QObject>
#include <QtCore/QAbstractListModel>
#include "enum/wUrl.h"
#include "document/base/wDocumentBase.h"
#include "cache/single/wContainerSingle.h"
#include "QtCore/QVariantMap"

class WModelCacheListByDoc : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit WModelCacheListByDoc(WDocumentBase *document, WJson::WJson_enum jsonKey, QVariantMap map = QVariantMap(),
                                  QObject *parent = nullptr);

    QHash <int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;
    void setSort(WEnum::Sort sort);

public slots:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool containsId(QString id);
    bool containsBarcode(QString barcode);
    WDocumentBase* document();

private:
    WDocumentBase *m_document;
    WEnum::Sort m_sort;
    WJson::WJson_enum m_jsonKey;
    QVariantMap m_map;
    QStringList m_list;

    void updateDocument();
};

#endif // WMODELCACHELISTBYDOC_H
