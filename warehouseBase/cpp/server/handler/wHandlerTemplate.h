#ifndef WHANDLERTEMPLATE_H
#define WHANDLERTEMPLATE_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "wclass/wJson.h"
#include "enum/wUrlEnum.h"

class WHandlerTemplate : public QObject
{
    Q_OBJECT
public:
    explicit WHandlerTemplate(QObject *parent = nullptr);

    virtual bool handler(QList <WUrlEnum::WUrl_enum> url, WJson* json) = 0;
    virtual bool registrateUrl(QList <WUrlEnum::WUrl_enum> url, WEnum::Request_priority priority) final;
    virtual bool registrateUrl(std::initializer_list <WUrlEnum::WUrl_enum> url, WEnum::Request_priority priority) final;
    virtual bool isContains(QList <WUrlEnum::WUrl_enum> url) const final;
    virtual bool isContains(QString url, WEnum::Version version = WEnum::Version_1_0) const final;
    virtual QList <QList <WUrlEnum::WUrl_enum>> getList() const final;

private:
    QList <std::pair <QList <WUrlEnum::WUrl_enum>, WEnum::Request_priority>> m_list;
};

#endif // HANDLERTEMPLATE_H
