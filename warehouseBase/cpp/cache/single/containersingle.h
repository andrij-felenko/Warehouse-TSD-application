#ifndef CONTAINERSINGLE_H
#define CONTAINERSINGLE_H

#include <QtCore/QDataStream>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>

#include "enum/wjson.h"
#include "enum/wstatic.h"
#include "cacheSingle.h"

/*! \brief Информация про контейнер */
class ContainerSingle : public CacheSingle
{
    Q_OBJECT
    Q_PROPERTY(QString employee_id READ       employeeId WRITE setEmployeeId
                                   RESET resetEmployeeId NOTIFY   employeeIdChanged)

public:
    explicit ContainerSingle(QObject* parent = nullptr);
    ContainerSingle(const QJsonObject &obj, QObject* parent = nullptr);

    // Json ----------------------------------------------------------------------------------------
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& obj);

    // READ ----------------------------------------------------------------------------------------
    QString employeeId() const; ///< Возвращает ИД текущего владельца

    // RESET ---------------------------------------------------------------------------------------
    void resetEmployeeId();

signals:
    void employeeIdChanged(QString employee_id);

public slots:
    void setEmployeeId(QString employee_id);

private:
    QString m_employee_id;
};

#endif // CONTAINERSINGLE_H
