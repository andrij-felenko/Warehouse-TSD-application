#include "wclass/wConverter.h"
#include "wclass/wStatic.h"
#include <QDebug>

WConverter::WConverter(QObject *parent) : QObject(parent)
{
    //
}

QString WConverter::guidCut(QString guid)
{
    return guid.mid(1, guid.length() - 2);
}

QString WConverter::statusToString(WEnum::DocumentStatus status)
{
    return WConverter::statusToString(+status);
}

QString WConverter::shortDateToString(QDate date)
{
    return date.toString("dd.MM");
}

QString WConverter::fullDateToString(QDate date)
{
    qDebug() << date << date.toString("ddd dd MMM yyyy");
    return date.toString("ddd dd MMMM yyyy");
}

QDate WConverter::dateTimeToDate(QDateTime dTime)
{
    return dTime.date();
}

QTime WConverter::dateTimeToTime(QDateTime dTime)
{
    return dTime.time();
}

QString WConverter::shortDateTimeToString(QDateTime dTime)
{
    return dTime.toString("dd.MM hh:mm");
}

QString WConverter::fullDateTimeToString(QDateTime dTime)
{
    return dTime.toString("dddd dd.MM.yy hh:mm");
}

QString WConverter::timeToString(QDateTime dTime)
{
    return dTime.toString("hh:mm");
}

QString WConverter::dateTimeToString(QDateTime dTime, QString key)
{
    return dTime.toString(key);
}

QString WConverter::statusToString(int status) {
    switch (static_cast <WEnum::DocumentStatus> (status)) {
    case WEnum::Document_created:   return QObject::tr("Created");
    case WEnum::Document_inWorking: return QObject::tr("In working");
    case WEnum::Document_accepted:  return QObject::tr("Accepted");
    case WEnum::Document_done:      return QObject::tr("Done");
    default:;
    }
    return WStatic::undefined();
}
