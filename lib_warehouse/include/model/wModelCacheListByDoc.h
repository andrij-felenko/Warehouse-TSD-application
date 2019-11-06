#ifndef WMODELCACHELISTBYDOC_H
#define WMODELCACHELISTBYDOC_H

#include "QtCore/QVariantMap"
#include "cache/single/wContainerSingle.h"
#include "document/base/wDocumentBase.h"
#include "template/wModelListTemplate.h"

class WModelCacheListByDoc : public WModelListTemplate
{
    Q_OBJECT
public:
    explicit WModelCacheListByDoc(QString name, WDocumentBase *document, WJsonEnum::WJson_enum jsonKey,
                                  QVariantMap map = QVariantMap(), QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const override;

public slots:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool containsId(QString id);
    bool containsBarcode(QString barcode);
    WDocumentBase* document();

private:
    WDocumentBase *m_document;
    WJsonEnum::WJson_enum m_jsonKey;
    QVariantMap m_map;
    QStringList m_list;

    void update() override;
};

#endif // WMODELCACHELISTBYDOC_H
