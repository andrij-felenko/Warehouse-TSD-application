#ifndef WCONVERTER_H
#define WCONVERTER_H

#include <QtCore/QDateTime>
#include <QtCore/QObject>
#include <QtCore/QString>
#include "enum/wEnum.h"

class WConverter : public QObject
{
    Q_OBJECT
public:
    explicit WConverter(QObject *parent = nullptr);

    static QString guidCut(QString guid);
    static QString statusToString(WEnum::DocumentStatus status);

public slots:
    // time & date ---------------------------------------------------------------------------------
    static QString shortDateToString(QDate date);
    static QString  fullDateToString(QDate date);

    static QDate dateTimeToDate(QDateTime dTime);
    static QTime dateTimeToTime(QDateTime dTime);

    static QString shortDateTimeToString(QDateTime dTime);
    static QString  fullDateTimeToString(QDateTime dTime);

    static QString timeToString    (QDateTime dTime);
    static QString dateTimeToString(QDateTime dTime, QString key);

    static QString statusToString(int status);
};

#endif // WCONVERTER_H
