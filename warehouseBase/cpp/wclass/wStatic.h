#ifndef WWSTATIC_H
#define WWSTATIC_H

#include <QtCore/QDateTime>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUuid>
#include "enum/wEnum.h"
#include "wConverter.h"

class WStatic : public QObject
{
    Q_OBJECT
public:
    WStatic(QObject* parent = nullptr) : QObject(parent) {}

public slots:
    // guid ----------------------------------------------------------------------------------------
    static QString guidCreate () { return WConverter::guidCut(QUuid::createUuid().toString()); }
    static QString guidNull   () { return WConverter::guidCut(QUuid().toString()); }
    static QString guidDefault() { return "ffffffff-ffff-ffff-ffff-ffffffffffff"; }
    static QString idCreate () { return guidCreate(); }
    static QString idDefault() { return guidDefault(); }
    static QString idNull   () { return guidNull(); }

    // time & date ---------------------------------------------------------------------------------
    static QDate dateNull() { return QDate(1, 1, 1); }
    static QTime timeNull() { return QTime(0, 0, 0); }
    static QDateTime dateTimeNull(){ return QDateTime(QDate(1, 1, 1)); }

    // string --------------------------------------------------------------------------------------
    static QString undefined() { return QObject::tr("Не найден"); }

    // version -------------------------------------------------------------------------------------
    static WEnum::Version version() { return WEnum::Version_1_0; }
};

#endif // WSTATIC_H
