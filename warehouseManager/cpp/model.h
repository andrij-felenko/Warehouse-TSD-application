#ifndef WWHMODEL_H
#define WWHMODEL_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

signals:

public slots:
    void employeeList(bool visible);
    void documentList(int key, bool visible);
};

#endif // WHMODEL_H
