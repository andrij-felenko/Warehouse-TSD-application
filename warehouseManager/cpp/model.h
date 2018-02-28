#ifndef WWHMODEL_H
#define WWHMODEL_H

#include <QtCore/QObject>
#include <QtCore/QVariantMap>
#include "enum/wStatic.h"

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

public slots:
    void employeeList(bool visible);
    void documentList(int key, bool visible);
    void cacheDocList(QString name, bool visible, QString id = WStatic::guidDefault(), int jsonKey = 0,
                      QVariantMap map = QVariantMap());
};

#endif // WHMODEL_H
