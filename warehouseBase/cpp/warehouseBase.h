#ifndef WAREHOUSEBASE_H
#define WAREHOUSEBASE_H

#include "warehousebase_global.h"
#include "view/view.h"

class WAREHOUSEBASESHARED_EXPORT WarehouseBase : public QObject
{
public:
    WarehouseBase(QObject *parent = nullptr);

    static void registrateApp();

    void init();
    void loadQML(const QUrl& url);
    void registrateTypes();
    void start();

private:
    View *m_view;
};

#endif // WAREHOUSEBASE_H
