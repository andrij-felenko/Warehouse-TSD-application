#ifndef WWTUPLE_H
#define WWTUPLE_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include "enum/wEnum.h"
#include "wclass/wStatic.h"
#include "enum/wJsonEnum.h"

class WTuple : public QObject
{
    Q_OBJECT
    Q_PROPERTY(WJsonEnum::WJson_enum key MEMBER m_key)
    Q_PROPERTY(QString             value MEMBER m_value)

public:
    explicit WTuple(QObject *parent = nullptr) : QObject(parent){}

private:
    WJsonEnum::WJson_enum m_key;
    QString m_value;
};

#endif // WTUPLE_H
