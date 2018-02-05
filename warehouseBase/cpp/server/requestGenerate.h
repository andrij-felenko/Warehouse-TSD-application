#ifndef REQUESTGENERATE_H
#define REQUESTGENERATE_H

#include <QtCore/QObject>
#include "enum/wjson.h"
#include "enum/wurl.h"

class RequestGenerate : public QObject
{
    Q_OBJECT
public:
    explicit RequestGenerate(QObject *parent = nullptr);


signals:

public slots:

private:
    //
};

#endif // REQUESTGENERATE_H
