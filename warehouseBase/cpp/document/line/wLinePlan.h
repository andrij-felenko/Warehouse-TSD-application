#ifndef LINEPLAN_H
#define LINEPLAN_H

#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QString>

#include "enum/wjson.h"
#include "enum/wstatic.h"

class WLinePlan : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isDone READ isDone WRITE setIsDone RESET resetIsDone NOTIFY isDoneChanged)
    Q_PROPERTY(QString consignmentId READ       consignmentId WRITE setConsignmentId
                                     RESET resetConsignmentId NOTIFY   consignmentIdChanged)

    Q_PROPERTY(QString nomenclatureId READ       nomenclatureId WRITE setNomenclatureId
                                      RESET resetNomenclatureId NOTIFY   nomenclatureIdChanged)

    Q_PROPERTY(QString qualityId READ       qualityId WRITE setQualityId
                                 RESET resetQualityId NOTIFY   qualityIdChanged)

    Q_PROPERTY(QString cellReceiverId READ       cellReceiverId WRITE setCellReceiverId
                                      RESET resetCellReceiverId NOTIFY   cellReceiverIdChanged)

    Q_PROPERTY(QString cellSenderId READ       cellSenderId WRITE setCellSenderId
                                    RESET resetCellSenderId NOTIFY   cellSenderIdChanged)

    Q_PROPERTY(QString containerReceiverId READ       containerReceiverId WRITE setContainerReceiverId
                                           RESET resetContainerReceiverId NOTIFY   containerReceiverIdChanged)

    Q_PROPERTY(QString containerSenderId READ     containerSenderId WRITE setContainerSenderId
                                       RESET resetContainerSenderId NOTIFY   containerSenderIdChanged)

    Q_PROPERTY(int quantity READ       quantity WRITE setQuantity
                            RESET resetQuantity NOTIFY   quantityChanged)

    Q_PROPERTY(int lineNumber READ       lineNumber WRITE setLineNumber
                              RESET resetLineNumber NOTIFY   lineNumberChanged)

    Q_PROPERTY(QString consignmentName       READ consignmentName       NOTIFY consignmentNameChanged)
    Q_PROPERTY(QString nomenclatureName      READ nomenclatureName      NOTIFY nomenclatureNameChanged)
    Q_PROPERTY(QString qualityName           READ qualityName           NOTIFY qualityNameChanged)
    Q_PROPERTY(QString containerReceiverName READ containerReceiverName NOTIFY containerReceiverNameChanged)
    Q_PROPERTY(QString containerSenderName   READ containerSenderName   NOTIFY containerSenderNameChanged)
    Q_PROPERTY(QString cellReceiverName      READ cellReceiverName      NOTIFY cellReceiverNameChanged)
    Q_PROPERTY(QString cellSenderName        READ cellSenderName        NOTIFY cellSenderNameChanged)

public:
    explicit WLinePlan(QObject *parent = nullptr);
     WLinePlan(const QJsonObject& obj, QObject *parent = nullptr);

    // JSON ----------------------------------------------------------------------------------------
    QJsonObject toJson() const;
    void fromJson(const QJsonObject& obj);

    // READ ----------------------------------------------------------------------------------------
    bool    isDone()                const { return m_isDone; }
    QString consignmentId()         const { return m_consignmentId; }
    QString nomenclatureId()        const { return m_nomenclatureId; }
    QString qualityId()             const { return m_qualityId; }
    QString cellReceiverId()        const { return m_cellReceiverId; }
    QString cellSenderId()          const { return m_cellSenderId; }
    QString containerReceiverId()   const { return m_containerReceiverId; }
    QString containerSenderId()     const { return m_containerSenderId; }
    int quantity()                  const { return m_quantity; }
    int lineNumber()                const { return m_lineNumber; }
    QString consignmentName()       const { return m_consignmentName; }
    QString nomenclatureName()      const { return m_nomenclatureName; }
    QString qualityName()           const { return m_qualityName; }
    QString containerReceiverName() const { return m_containerReceiverName; }
    QString containerSenderName()   const { return m_containerSenderName; }
    QString cellReceiverName()      const { return m_cellReceiverName; }
    QString cellSenderName()        const { return m_cellSenderName; }

    // RESET ---------------------------------------------------------------------------------------
    void resetIsDone()              { setIsDone(false); }
    void resetConsignmentId()       { setConsignmentId      (WStatic::guidDefault()); }
    void resetNomenclatureId()      { setNomenclatureId     (WStatic::guidDefault()); }
    void resetQualityId()           { setQualityId          (WStatic::guidDefault()); }
    void resetCellReceiverId()      { setCellReceiverId     (WStatic::guidDefault()); }
    void resetCellSenderId()        { setCellSenderId       (WStatic::guidDefault()); }
    void resetContainerReceiverId() { setContainerReceiverId(WStatic::guidDefault()); }
    void resetContainerSenderId()   { setContainerSenderId  (WStatic::guidDefault()); }
    void resetLineNumber()          { setLineNumber(-1); }
    void resetQuantity()            { setQuantity(0); }
    void clear()                    { resetAll(); }

protected:
    void resetAll();

signals:
    void isDoneChanged(bool isDone);
    void consignmentIdChanged(QString consignmentId);
    void nomenclatureIdChanged(QString nomenclatureId);
    void qualityIdChanged(QString qualityId);
    void cellReceiverIdChanged(QString cellReceiverId);
    void cellSenderIdChanged(QString cellSenderId);
    void containerReceiverIdChanged(QString containerReceiverId);
    void containerSenderIdChanged(QString containerSenderId);
    void quantityChanged(int quantity);
    void lineNumberChanged(int lineNumber);
    void consignmentNameChanged(QString consignmentName);
    void nomenclatureNameChanged(QString nomenclatureName);
    void qualityNameChanged(QString qualityName);
    void containerReceiverNameChanged(QString containerReceiverName);
    void containerSenderNameChanged(QString containerSenderName);
    void cellReceiverNameChanged(QString cellReceiverName);
    void cellSenderNameChanged(QString cellSenderName);

public slots:
    void setIsDone(bool isDone);
    void setConsignmentId(QString consignmentId);
    void setNomenclatureId(QString nomenclatureId);
    void setQualityId(QString qualityId);
    void setCellReceiverId(QString cellReceiverId);
    void setCellSenderId(QString cellSenderId);
    void setContainerReceiverId(QString containerReceiverId);
    void setContainerSenderId(QString containerSenderId);
    void setQuantity(int quantity);
    void setLineNumber(int lineNumber);

private:
    bool m_isDone;
    QString m_consignmentId;
    QString m_nomenclatureId;
    QString m_qualityId;
    QString m_cellReceiverId;
    QString m_cellSenderId;
    QString m_containerReceiverId;
    QString m_containerSenderId;
    int m_quantity;
    int m_lineNumber;
    QString m_consignmentName;
    QString m_nomenclatureName;
    QString m_qualityName;
    QString m_containerReceiverName;
    QString m_containerSenderName;
    QString m_cellReceiverName;
    QString m_cellSenderName;

    // UPDATE -------------------------------------------------------------------------------------
    void updateCell(QStringList list);
    void updateContainer(QStringList list);
    void updateQuality(QStringList list);
    void updateConsignment(QStringList list);
    void updateNomenclature(QStringList list);

    void updateConsignmentName();
    void updateQualityName();
    void updateNomenclatureName();
    void updateContainerReceiverName();
    void updateContainerSenderName();
    void updateCellReceiverName();
    void updateCellSenderName();

    // WRITE NAME PRIVATE -------------------------------------------------------------------------
    void setConsignmentName(QString consignmentName);
    void setNomenclatureName(QString nomenclatureName);
    void setQualityName(QString qualityName);
    void setCellReceiverName(QString cellReceiverName);
    void setCellSenderName(QString cellSenderName);
    void setContainerReceiverName(QString containerReceiverName);
    void setContainerSenderName(QString containerSenderName);
};

#endif // LINEPLAN_H
