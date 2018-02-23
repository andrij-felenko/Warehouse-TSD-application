#ifndef WWAREHOUSEBASE_GLOBAL_H
#define WWAREHOUSEBASE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(WAREHOUSEBASE_LIBRARY)
#  define WAREHOUSEBASESHARED_EXPORT Q_DECL_EXPORT
#else
#  define WAREHOUSEBASESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // WAREHOUSEBASE_GLOBAL_H
