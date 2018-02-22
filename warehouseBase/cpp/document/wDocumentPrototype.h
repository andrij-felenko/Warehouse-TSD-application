#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QJsonArray>
#include "enum/wenum.h"
#include "enum/wjson.h"
#include "enum/wstatic.h"
#include "enum/wurl.h"
#include "document/base/wDocumentBase.h"

class WDocumentPrototype : public QObject
{
    Q_OBJECT
public:
    explicit WDocumentPrototype(QObject *parent = nullptr);

    virtual void updateDocumentList(WJsonTemplate* json, WUrl::WUrl_enum key) final;
    virtual WDocumentBase* getDocument(QString id, WUrl::WUrl_enum key = WUrl::___) const final;
    virtual WDocumentBase* getDocument(WUrl::WUrl_enum key, int position) const final;
    virtual int getDocumentLengthByKey(WUrl::WUrl_enum key) const final;
    virtual bool containsId(WUrl::WUrl_enum key, QString id) const final;

signals:
    void documentListUpdate(WUrl::WUrl_enum key);

private:
    struct DocItem {
        WUrl::WUrl_enum key;
        WDocumentBase* document;
    };

    WDocumentBase* m_empty;
    QList <DocItem> m_list;
};

#endif // DOCUMENTMANAGER_H
