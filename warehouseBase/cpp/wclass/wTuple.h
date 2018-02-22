#ifndef WTUPLE_H
#define WTUPLE_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include "enum/wenum.h"
#include "enum/wstatic.h"
#include "enum/wjson.h"

class WTuple : public QObject
{
    Q_OBJECT
    Q_PROPERTY(WJson::WJson_enum key MEMBER m_key)
    Q_PROPERTY(QString         value MEMBER m_value)

public:
    explicit WTuple(QObject *parent = nullptr) : QObject(parent){}

private:
    WJson::WJson_enum m_key;
    QString m_value;
};

#endif // WTUPLE_H
