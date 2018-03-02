#ifndef WWSTATIC_H
#define WWSTATIC_H

#include <QtCore/QDateTime>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUuid>
#include "wEnum.h"

class WStatic : public QObject
{
    Q_OBJECT
public:
    WStatic(QObject* parent = nullptr) : QObject(parent) {}

    static QString guidCut(QString guid) { return guid.mid(1, guid.length() - 2); }
    static QString statusToString(WEnum::DocumentStatus status) { return WStatic::statusToString(+status); }

public slots:
    // guid ----------------------------------------------------------------------------------------
    static QString guidCreate () { return WStatic::guidCut(QUuid::createUuid().toString()); }
    static QString guidNull   () { return WStatic::guidCut(QUuid().toString()); }
    static QString guidDefault() { return "ffffffff-ffff-ffff-ffff-ffffffffffff"; }
    static QString idCreate () { return guidCreate(); }
    static QString idDefault() { return guidDefault(); }
    static QString idNull   () { return guidNull(); }

    // time & date ---------------------------------------------------------------------------------
    static QDate dateNull() { return QDate(1, 1, 1); }
    static QTime timeNull() { return QTime(0, 0, 0); }
    static QDateTime dateTimeNull(){ return QDateTime(QDate(1, 1, 1)); }
    static QString shortDateToString    (QDateTime dTime) { return dTime.toString("dd.MM"); }
    static QString  fullDateToString    (QDateTime dTime) { return dTime.toString("ddd dd MMMM yyyy"); }
    static QString shortDateTimeToString(QDateTime dTime) { return dTime.toString("dd.MM hh:mm"); }
    static QString  fullDateTimeToString(QDateTime dTime) { return dTime.toString("dddd dd.MM.yy hh:mm"); }
    static QString timeToString         (QDateTime dTime) { return dTime.toString("hh:mm"); }

    static QString dateTimeToString(QDateTime dTime, QString key) { return dTime.toString(key); }

    // string --------------------------------------------------------------------------------------
    static QString undefined() { return QObject::tr("Не найден"); }

    // version -------------------------------------------------------------------------------------
    static WEnum::Version version() { return WEnum::Version_1_0; }

    static QString statusToString(int status) {
        switch (static_cast <WEnum::DocumentStatus> (status)) {
        case WEnum::Document_created:   return QObject::tr("Created");
        case WEnum::Document_inWorking: return QObject::tr("In working");
        case WEnum::Document_accepted:  return QObject::tr("Accepted");
        case WEnum::Document_done:      return QObject::tr("Done");
        default:;
        }
        return WStatic::undefined();
    }
};

#endif // WSTATIC_H
