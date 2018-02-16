#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QJsonArray>
#include "enum/wenum.h"
#include "enum/wjson.h"
#include "enum/wstatic.h"
#include "enum/wurl.h"
#include "document/base/documentBase.h"

class DocumentPrototype : public QObject
{
    Q_OBJECT
public:
    explicit DocumentPrototype(QObject *parent = nullptr);

    void updateDocumentList(WJsonTemplate* json, WUrl::WUrl_enum key);
    DocumentBase* getDocument(QString id, WUrl::WUrl_enum key = WUrl::___) const;

private:
    struct docItem {
        WUrl::WUrl_enum key;
        DocumentBase* document;
    };

    QList <docItem> m_list;
};

#endif // DOCUMENTMANAGER_H
