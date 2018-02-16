#ifndef DOCUMENTHEADER_H
#define DOCUMENTHEADER_H

#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>

#include "enum/wjson.h"
#include "enum/wstatic.h"

class DocumentHeader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id       READ id       WRITE setId       RESET resetId       NOTIFY idChanged)
    Q_PROPERTY(QString name     READ name     WRITE setName     RESET resetName     NOTIFY nameChanged)
    Q_PROPERTY(QString supplier READ supplier WRITE setSupplier RESET resetSupplier NOTIFY supplierChanged)

    Q_PROPERTY(QDateTime dateCreated READ       dateCreated WRITE setDateCreated
                                     RESET resetDateCreated NOTIFY   dateCreatedChanged)

    Q_PROPERTY(QDateTime dateAccepted READ       dateAccepted WRITE setDateAccepted
                                      RESET resetDateAccepted NOTIFY   dateAcceptedChanged)

    Q_PROPERTY(QDateTime dateCompleted READ       dateCompleted WRITE setDateCompleted
                                       RESET resetDateCompleted NOTIFY   dateCompletedChanged)

    Q_PROPERTY(QStringList cellIdList READ       cellIdList WRITE setCellIdList
                                      RESET resetCellIdList NOTIFY   cellIdListChanged)

    Q_PROPERTY(bool isStaticCellContains READ       isStaticCellContains WRITE setIsStaticCellContains
                                         RESET resetIsStaticCellContains NOTIFY   isStaticCellContainsChanged)

    Q_PROPERTY(bool isCanChangeCell READ       isCanChangeCell WRITE setIsCanChangeCell
                                    RESET resetIsCanChangeCell NOTIFY   isCanChangeCellChanged)

    Q_PROPERTY(bool isTwoVerifyAccepted READ       isTwoVerifyAccepted WRITE setIsTwoVerifyAccepted
                                        RESET resetIsTwoVerifyAccepted NOTIFY   isTwoVerifyAcceptedChanged)

    Q_PROPERTY(bool isGeoposition READ       isGeoposition WRITE setIsGeoposition
                                  RESET resetIsGeoposition NOTIFY   isGeopositionChanged)

    Q_PROPERTY(QString employeeSenderId READ       employeeSenderId WRITE setEmployeeSenderId
                                        RESET resetEmployeeSenderId NOTIFY   employeeSenderIdChanged)

    Q_PROPERTY(QString employeeSenderName READ       employeeSenderName WRITE setEmployeeSenderName
                                          RESET resetEmployeeSenderName NOTIFY   employeeSenderNameChanged)

    Q_PROPERTY(QString employeeReceiverId READ       employeeReceiverId WRITE setEmployeeReceiverId
                                          RESET resetEmployeeReceiverId NOTIFY   employeeReceiverIdChanged)

    Q_PROPERTY(QString employeeReceiverName READ       employeeReceiverName WRITE setEmployeeReceiverName
                                            RESET resetEmployeeReceiverName NOTIFY   employeeReceiverNameChanged)

public:
    explicit DocumentHeader(QObject *parent = nullptr);
    DocumentHeader(const QJsonObject& obj, QObject *parent = nullptr);

    // JSON ----------------------------------------------------------------------------------------
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& obj);

    // READ ---------------------------------------------------------------------------------------
    QString id()       const { return m_id; }
    QString name()     const { return m_name; }
    QString supplier() const { return m_supplier; }
    QDateTime dateCreated()   const { return m_dateCreated; }
    QDateTime dateAccepted()  const { return m_dateAccepted; }
    QDateTime dateCompleted() const { return m_dateCompleted; }
    QStringList cellIdList()  const { return m_cellIdList; } // FIXME cell list
    bool isStaticCellContains() const { return m_isStaticCellContains; }
    bool isCanChangeCell()      const { return m_isCanChangeCell; }
    bool isTwoVerifyAccepted()  const { return m_isTwoVerifyAccepted; }
    bool isGeoposition()        const { return m_isGeoposition; }
    QString employeeSenderId()     const { return m_employeeSenderId; }
    QString employeeSenderName()   const { return m_employeeSenderName; }
    QString employeeReceiverId()   const { return m_employeeReceiverId; }
    QString employeeReceiverName() const { return m_employeeReceiverName; }

    // RESET --------------------------------------------------------------------------------------
    void resetId()            { setId(WStatic::guidDefault()); }
    void resetName()          { setName(WStatic::undefined()); }
    void resetSupplier()      { setSupplier(WStatic::undefined()); }
    void resetDateCreated()   { setDateCreated  (WStatic::dateTimeNull()); }
    void resetDateAccepted()  { setDateAccepted (WStatic::dateTimeNull()); }
    void resetDateCompleted() { setDateCompleted(WStatic::dateTimeNull()); }
    void resetCellIdList()    { setCellIdList(QStringList()); }
    void resetIsStaticCellContains() { setIsStaticCellContains(false); }
    void resetIsCanChangeCell()      { setIsCanChangeCell(false); }
    void resetIsTwoVerifyAccepted()  { setIsTwoVerifyAccepted(false); }
    void resetIsGeoposition()        { setIsGeoposition(false); }
    void resetEmployeeSenderId()     { setEmployeeSenderId(WStatic::guidDefault()); }
    void resetEmployeeSenderName()   { setEmployeeSenderName(WStatic::undefined()); }
    void resetEmployeeReceiverId()   { setEmployeeReceiverId(WStatic::guidDefault()); }
    void resetEmployeeReceiverName() { setEmployeeReceiverName(WStatic::undefined()); }

signals:
    void idChanged(QString id);
    void nameChanged(QString name);
    void supplierChanged(QString supplier);
    void dateCreatedChanged(QDateTime dateCreated);
    void dateAcceptedChanged(QDateTime dateAccepted);
    void dateCompletedChanged(QDateTime dateCompleted);
    void cellIdListChanged(QStringList cellIdList);
    void isStaticCellContainsChanged(bool isStaticCellContains);
    void isCanChangeCellChanged(bool isCanChangeCell);
    void isTwoVerifyAcceptedChanged(bool isTwoVerifyAccepted);
    void isGeopositionChanged(bool isGeoposition);
    void employeeSenderIdChanged(QString employeeSenderId);
    void employeeSenderNameChanged(QString employeeSenderName);
    void employeeReceiverIdChanged(QString employeeReceiverId);
    void employeeReceiverNameChanged(QString employeeReceiverName);

public slots:
    void setId(QString id);
    void setName(QString name);
    void setSupplier(QString supplier);
    void setDateCreated(QDateTime dateCreated);
    void setDateAccepted(QDateTime dateAccepted);
    void setDateCompleted(QDateTime dateCompleted);
    void setCellIdList(QStringList cellIdList);
    void setIsStaticCellContains(bool isStaticCellContains);
    void setIsCanChangeCell(bool isCanChangeCell);
    void setIsTwoVerifyAccepted(bool isTwoVerifyAccepted);
    void setIsGeoposition(bool isGeoposition);
    void setEmployeeSenderId(QString employeeSenderId);
    void setEmployeeReceiverId(QString employeeReceiverId);

protected:
    void resetAll();

private:
    QString m_id;
    QString m_name;
    QString m_supplier;
    QDateTime m_dateCreated;
    QDateTime m_dateAccepted;
    QDateTime m_dateCompleted;
    QStringList m_cellIdList;
    bool m_isStaticCellContains;
    bool m_isCanChangeCell;
    bool m_isTwoVerifyAccepted;
    bool m_isGeoposition;
    QString m_employeeSenderId;
    QString m_employeeSenderName;
    QString m_employeeReceiverId;
    QString m_employeeReceiverName;

    // WRITE NAME PRIVATE -------------------------------------------------------------------------
    void setEmployeeSenderName(QString employeeSenderName);
    void setEmployeeReceiverName(QString employeeReceiverName);
    void updateEmployee(QStringList list);
    void updateEmployeeSenderName();
    void updateEmployeeReceiverName();
};

#endif // DOCUMENTHEADER_H
