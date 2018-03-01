#ifndef WHANDLERTEMPLATE_H
#define WHANDLERTEMPLATE_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "wJsonTemplate.h"
#include "enum/wUrl.h"

class WHandlerTemplate : public QObject
{
    Q_OBJECT
public:
    explicit WHandlerTemplate(QObject *parent = nullptr);

    virtual bool handler(QList <WUrl::WUrl_enum> url, WJsonTemplate* json) = 0;
    virtual bool registrateUrl(QList <WUrl::WUrl_enum> url, WEnum::Request_priority priority) final;
    virtual bool registrateUrl(std::initializer_list <WUrl::WUrl_enum> url, WEnum::Request_priority priority) final;
    virtual bool isContains(QList <WUrl::WUrl_enum> url) const final;
    virtual bool isContains(QString url, WEnum::Version version = WUrl::version()) const final;
    virtual QList <QList <WUrl::WUrl_enum>> getList() const final;

private:
    QList <std::pair <QList <WUrl::WUrl_enum>, WEnum::Request_priority>> m_list;
};

#endif // HANDLERTEMPLATE_H
