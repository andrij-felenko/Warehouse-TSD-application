#ifndef WMODELDOCUMENTLIST_H
#define WMODELDOCUMENTLIST_H

#include <QtCore/QMap>
#include "document/base/wDocumentBase.h"
#include "enum/wUrlEnum.h"
#include "template/wModelListTemplate.h"

class WModelDocumentList : public WModelListTemplate
{
    Q_OBJECT
public:
    explicit WModelDocumentList(QString name, WUrlEnum::WUrl_enum key, QObject *parent = nullptr);

    QVariant data(const QModelIndex &index, int role) const override;

public slots:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    bool containsId(QString id);

private:
    WUrlEnum::WUrl_enum key;
    QList <WDocumentBase*> m_list;

    void update() override;
};

#endif // MODELDOCUMENTLIST_H
