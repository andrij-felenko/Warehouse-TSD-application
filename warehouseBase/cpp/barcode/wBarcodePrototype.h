#ifndef BARCODEPROTOTYPE_H
#define BARCODEPROTOTYPE_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class WBarcodePrototype : public QObject
{
    Q_OBJECT
public:
    explicit WBarcodePrototype(QObject *parent = nullptr);

signals:

public slots:
};

#endif // BARCODEPROTOTYPE_H
