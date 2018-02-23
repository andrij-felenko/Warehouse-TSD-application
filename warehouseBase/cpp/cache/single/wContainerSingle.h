#ifndef WCONTAINERSINGLE_H
#define WCONTAINERSINGLE_H

#include <QtCore/QDataStream>
#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>

#include "enum/wJson.h"
#include "enum/wStatic.h"
#include "wCacheSingle.h"

/*! \brief Информация про контейнер */
// FIXME contains in container
class WContainerSingle : public WCacheSingle
{
    Q_OBJECT
    Q_PROPERTY(QString employee_id READ       employeeId WRITE setEmployeeId
                                   RESET resetEmployeeId NOTIFY   employeeIdChanged)

public:
    explicit WContainerSingle(QObject* parent = nullptr);
    WContainerSingle(const QJsonObject &obj, QObject* parent = nullptr);
    operator WCacheSingle* () { return reinterpret_cast <WCacheSingle*> (this); }

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

protected:
    friend QDataStream& operator << (QDataStream &s, WContainerSingle& d);
    friend QDataStream& operator >> (QDataStream &s, WContainerSingle& d);

private:
    QString m_employee_id;
};

#endif // CONTAINERSINGLE_H
