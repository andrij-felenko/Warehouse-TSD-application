#ifndef WDOCUMENTMANAGER_H
#define WDOCUMENTMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QJsonArray>
#include "enum/wEnum.h"
#include "enum/wJsonEnum.h"
#include "wclass/wStatic.h"
#include "enum/wUrlEnum.h"
#include "document/base/wDocumentBase.h"

class WDocumentPrototype : public QObject
{
    Q_OBJECT
public:
    explicit WDocumentPrototype(QObject *parent = nullptr);

    virtual void updateDocumentList(WJson* json, WUrlEnum::WUrl_enum key) final;
    virtual WDocumentBase* getDocument(QString id, WUrlEnum::WUrl_enum key = WUrlEnum::___) const final;
    virtual WDocumentBase* getDocument(WUrlEnum::WUrl_enum key, int position) const final;
    virtual QStringList getDocumentListByKey(WUrlEnum::WUrl_enum key) const final;
    virtual QMultiMap <WEnum::DocumentStatus, QString> getDocumentMapByKey(WUrlEnum::WUrl_enum key) const final;
    virtual QList <WDocumentBase*> getDocumentPointListByKey(WUrlEnum::WUrl_enum key) const final;
    virtual int getDocumentLengthByKey(WUrlEnum::WUrl_enum key) const final;
    virtual bool containsId(WUrlEnum::WUrl_enum key, QString id) const final;

public slots:
    void requestDocumentList(int key);

signals:
    void documentListUpdate(WUrlEnum::WUrl_enum key);

private:
    struct DocItem {
        WUrlEnum::WUrl_enum key;
        WDocumentBase* document;
    };

    WDocumentBase* m_empty;
    QList <DocItem> m_list;

    void updateDocumentVocabulary(WDocumentBase* document);
};

#endif // DOCUMENTMANAGER_H
