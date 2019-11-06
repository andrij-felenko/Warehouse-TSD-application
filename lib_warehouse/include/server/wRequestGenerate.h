#ifndef WREQUESTGENERATE_H
#define WREQUESTGENERATE_H

#include <QtCore/QJsonObject>
#include <QtCore/QJsonValue>
#include <QtCore/QObject>
#include "enum/wJsonEnum.h"
#include "enum/wUrlEnum.h"

class WRequestGenerate : public QObject
{
    Q_OBJECT
public:
    explicit WRequestGenerate(QObject *parent = nullptr);

signals:

public slots:
    static QJsonValue empty();
    static QJsonValue list(QStringList list);
    static QJsonValue date(QDateTime dateTime);
    static QJsonValue tuple(int key, QJsonValue value);
    static QJsonValue reserveContainer(QString container, QString document);
    static QJsonValue actualLine(QJsonObject obj, QString document);
    static QJsonValue removeLine(QString line, QString document);

private:
    //
};

#endif // REQUESTGENERATE_H
