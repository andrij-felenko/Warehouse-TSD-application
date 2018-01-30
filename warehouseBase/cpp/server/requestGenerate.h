#ifndef REQUESTGENERATE_H
#define REQUESTGENERATE_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class RequestGenerate : public QObject
{
    Q_OBJECT
public:
    explicit RequestGenerate(QObject *parent = nullptr);

signals:

public slots:
};

#endif // REQUESTGENERATE_H