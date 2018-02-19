#ifndef HANDLERTEMPLATE_H
#define HANDLERTEMPLATE_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "wjsonTemplate.h"
#include "enum/wurl.h"

class HandlerTemplate : public QObject
{
    Q_OBJECT
public:
    explicit HandlerTemplate(QObject *parent = nullptr);

    virtual bool handler(QList <WUrl::WUrl_enum> url, WJsonTemplate* json) = 0;
    virtual bool registrateUrl(QList <WUrl::WUrl_enum> url) final;
    virtual bool registrateUrl(std::initializer_list <WUrl::WUrl_enum> url) final;
    virtual bool isContains(QList <WUrl::WUrl_enum> url) final;
    virtual bool isContains(QString url, WEnum::Version version = WUrl::version()) final;
    virtual QList <QList <WUrl::WUrl_enum>> getList() const final;

private:
    QList <QList <WUrl::WUrl_enum>> m_list;
};

#endif // HANDLERTEMPLATE_H
