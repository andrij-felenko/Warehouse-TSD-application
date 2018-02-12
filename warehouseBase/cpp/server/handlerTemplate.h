#ifndef HANDLERTEMPLATE_H
#define HANDLERTEMPLATE_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include "wjsonTemplate.h"

typedef void (*fp)(WJsonTemplate*);

class HandlerTemplate : public QObject
{
    Q_OBJECT
public:
    explicit HandlerTemplate(QObject *parent = nullptr);

    bool registrate(QString key, fp function);

    void getUserList(WJsonTemplate* temp) {}

signals:

public slots:

private:
    struct FP {
        QString key;
        fp function;
    };

    QList <FP> m_list;
};

#endif // HANDLERTEMPLATE_H
