#include "linePlan.h"
#include "singleton.h"

LinePlan::LinePlan(QObject *parent) : QObject(parent)
{
    QObject::connect(Cache::get().cell(), &CacheListObject::listPushed,  this, &LinePlan::updateCell);
    QObject::connect(Cache::get().cell(), &CacheListObject::listUpdated, this, &LinePlan::updateCell);
    QObject::connect(Cache::get().container(), &CacheListObject::listPushed,  this, &LinePlan::updateContainer);
    QObject::connect(Cache::get().container(), &CacheListObject::listUpdated, this, &LinePlan::updateContainer);
    QObject::connect(Cache::get().quality(), &CacheListObject::listPushed,  this, &LinePlan::updateQuality);
    QObject::connect(Cache::get().quality(), &CacheListObject::listUpdated, this, &LinePlan::updateQuality);
    QObject::connect(Cache::get().nomenclature(), &CacheListObject::listPushed,  this, &LinePlan::updateNomenclature);
    QObject::connect(Cache::get().nomenclature(), &CacheListObject::listUpdated, this, &LinePlan::updateNomenclature);
    QObject::connect(Cache::get().consignment(), &CacheListObject::listPushed,  this, &LinePlan::updateConsignment);
    QObject::connect(Cache::get().consignment(), &CacheListObject::listUpdated, this, &LinePlan::updateConsignment);

    resetAll();
}

LinePlan::LinePlan(const QJsonObject& obj, QObject* parent)
{
    fromJson(obj);
}

QJsonObject LinePlan::toJson() const
{
    return WJson::createObject({
        std::make_pair(WJson::Quantity, m_quantity),
        std::make_pair(WJson::Line_number, m_lineNumber),
        std::make_pair(WJson::Consignment_id,   m_consignmentId),
        std::make_pair(WJson::Consignment_name, m_consignmentName),
        std::make_pair(WJson::Nomenclature_id,   m_nomenclatureId),
        std::make_pair(WJson::Nomenclature_name, m_nomenclatureName),
        std::make_pair(WJson::Quality_id,   m_qualityId),
        std::make_pair(WJson::Quality_name, m_qualityName),
        std::make_pair(WJson::Container_receiver_id,   m_containerReceiverId),
        std::make_pair(WJson::Container_receiver_name, m_containerReceiverName),
        std::make_pair(WJson::Container_sender_id,   m_containerSenderId),
        std::make_pair(WJson::Container_sender_name, m_containerSenderName),
        std::make_pair(WJson::Cell_receiver_id,   m_cellReceiverId),
        std::make_pair(WJson::Cell_receiver_name, m_cellReceiverName),
        std::make_pair(WJson::Cell_sender_id,   m_cellSenderId),
        std::make_pair(WJson::Cell_sender_name, m_cellSenderName),
    });
}

void LinePlan::fromJson(const QJsonObject& obj)
{
    // Quantity
    if (WJson::contains(obj, WJson::Quantity))
        setQuantity(WJson::get(obj, WJson::Quantity).toInt());

    // Line number
    if (WJson::contains(obj, WJson::Line_number))
        setLineNumber(WJson::get(obj, WJson::Line_number).toInt());

    // Consignment
    if (WJson::contains(obj, WJson::Consignment_id))
        setConsignmentId(WJson::get(obj, WJson::Consignment_id).toString());

    if (WJson::contains(obj, WJson::Consignment_name))
        setConsignmentName(WJson::get(obj, WJson::Consignment_name).toString());
    else
        updateConsignmentName();

    // Nomenclature
    if (WJson::contains(obj, WJson::Nomenclature_id))
        setNomenclatureId(WJson::get(obj, WJson::Nomenclature_id).toString());

    if (WJson::contains(obj, WJson::Nomenclature_name))
        setNomenclatureName(WJson::get(obj, WJson::Nomenclature_name).toString());
    else
        updateNomenclatureName();

    // Quality
    if (WJson::contains(obj, WJson::Quality_id))
        setQualityId(WJson::get(obj, WJson::Quality_id).toString());

    if (WJson::contains(obj, WJson::Quality_name))
        setQualityName(WJson::get(obj, WJson::Quality_name).toString());
    else
        updateQualityName();

    // Container
    if (WJson::contains(obj, WJson::Container_receiver_id))
        setContainerReceiverId(WJson::get(obj, WJson::Container_receiver_id).toString());

    if (WJson::contains(obj, WJson::Container_receiver_name))
        setContainerReceiverName(WJson::get(obj, WJson::Container_receiver_name).toString());
    else
        updateContainerReceiverName();

    if (WJson::contains(obj, WJson::Container_sender_id))
        setContainerSenderId(WJson::get(obj, WJson::Container_sender_id).toString());

    if (WJson::contains(obj, WJson::Container_sender_name))
        setContainerSenderName(WJson::get(obj, WJson::Container_sender_name).toString());
    else
        updateContainerSenderName();

    // Cell
    if (WJson::contains(obj, WJson::Cell_receiver_id))
        setCellReceiverId(WJson::get(obj, WJson::Cell_receiver_id).toString());

    if (WJson::contains(obj, WJson::Cell_receiver_name))
        setCellReceiverName(WJson::get(obj, WJson::Cell_receiver_name).toString());
    else
        updateCellReceiverName();

    if (WJson::contains(obj, WJson::Cell_sender_id))
        setCellSenderId(WJson::get(obj, WJson::Cell_sender_id).toString());

    if (WJson::contains(obj, WJson::Cell_sender_name))
        setCellSenderName(WJson::get(obj, WJson::Cell_sender_name).toString());
    else
        updateCellSenderName();
}

void LinePlan::resetAll()
{
    resetCellReceiverId();
    resetCellSenderId();
    resetConsignmentId();
    resetContainerReceiverId();
    resetContainerSenderId();
    resetLineNumber();
    resetNomenclatureId();
    resetQualityId();
    resetQuantity();
}

void LinePlan::setConsignmentId(QString consignmentId)
{
    if (m_consignmentId != consignmentId){
        m_consignmentId = consignmentId;
        emit consignmentIdChanged(m_consignmentId);
        updateConsignmentName();
    }
}

void LinePlan::setNomenclatureId(QString nomenclatureId)
{
    if (m_nomenclatureId != nomenclatureId){
        m_nomenclatureId = nomenclatureId;
        emit nomenclatureIdChanged(m_nomenclatureId);
        updateNomenclatureName();
    }
}

void LinePlan::setQualityId(QString qualityId)
{
    if (m_qualityId != qualityId){
        m_qualityId = qualityId;
        emit qualityIdChanged(m_qualityId);
        updateQualityName();
    }
}

void LinePlan::setCellReceiverId(QString cellReceiverId)
{
    if (m_cellReceiverId != cellReceiverId){
        m_cellReceiverId = cellReceiverId;
        emit cellReceiverIdChanged(m_cellReceiverId);
        updateCellReceiverName();
    }
}

void LinePlan::setCellSenderId(QString cellSenderId)
{
    if (m_cellSenderId != cellSenderId){
        m_cellSenderId = cellSenderId;
        emit cellSenderIdChanged(m_cellSenderId);
        updateCellSenderName();
    }
}

void LinePlan::setContainerReceiverId(QString containerReceiverId)
{
    if (m_containerReceiverId != containerReceiverId){
        m_containerReceiverId = containerReceiverId;
        emit containerReceiverIdChanged(m_containerReceiverId);
        updateContainerReceiverName();
    }
}

void LinePlan::setContainerSenderId(QString containerSenderId)
{
    if (m_containerSenderId != containerSenderId){
        m_containerSenderId = containerSenderId;
        emit containerSenderIdChanged(m_containerSenderId);
        updateContainerSenderName();
    }
}

void LinePlan::setQuantity(int quantity)
{
    if (m_quantity != quantity){
        m_quantity = quantity;
        emit quantityChanged(m_quantity);
    }
}

void LinePlan::setLineNumber(int lineNumber)
{
    if (m_lineNumber != lineNumber){
        m_lineNumber = lineNumber;
        emit lineNumberChanged(m_lineNumber);
    }
}

void LinePlan::updateCell(QStringList list)
{
    if (list.contains(m_cellReceiverId))
        updateCellReceiverName();
    if (list.contains(m_cellSenderId))
        updateCellSenderName();
}

void LinePlan::updateContainer(QStringList list)
{
    if (list.contains(m_containerReceiverId))
        updateContainerReceiverName();
    if (list.contains(m_containerSenderId))
        updateContainerSenderName();
}

void LinePlan::updateQuality(QStringList list)
{
    if (list.contains(m_qualityId))
        updateQualityName();
}

void LinePlan::updateConsignment(QStringList list)
{
    if (list.contains(m_consignmentId))
        updateConsignmentName();
}

void LinePlan::updateNomenclature(QStringList list)
{
    if (list.contains(m_nomenclatureId))
        updateNomenclatureName();
}

void LinePlan::updateConsignmentName()
{
    setConsignmentName(Cache::get().consignment()->getNameById(m_consignmentId));
}

void LinePlan::updateQualityName()
{
    setQualityName(Cache::get().quality()->getNameById(m_qualityId));
}

void LinePlan::updateNomenclatureName()
{
    setNomenclatureName(Cache::get().nomenclature()->getNameById(m_nomenclatureId));
}

void LinePlan::updateContainerReceiverName()
{
    setContainerReceiverName(Cache::get().container()->getNameById(m_containerReceiverId));
}

void LinePlan::updateContainerSenderName()
{
    setContainerSenderName(Cache::get().container()->getNameById(m_containerSenderId));
}

void LinePlan::updateCellReceiverName()
{
    setCellReceiverName(Cache::get().cell()->getNameById(m_cellReceiverId));
}

void LinePlan::updateCellSenderName()
{
    setCellSenderName(Cache::get().cell()->getNameById(m_cellSenderId));
}

void LinePlan::setConsignmentName(QString consignmentName)
{
    if (m_consignmentName != consignmentName){
        m_consignmentName = consignmentName;
        emit consignmentNameChanged(m_consignmentName);
    }
}

void LinePlan::setNomenclatureName(QString nomenclatureName)
{
    if (m_nomenclatureName != nomenclatureName){
        m_nomenclatureName = nomenclatureName;
        emit nomenclatureNameChanged(m_nomenclatureName);
    }
}

void LinePlan::setQualityName(QString qualityName)
{
    if (m_qualityName != qualityName){
        m_qualityName = qualityName;
        emit qualityNameChanged(m_qualityName);
    }
}

void LinePlan::setCellReceiverName(QString cellReceiverName)
{
    if (m_cellReceiverName != cellReceiverName){
        m_cellReceiverName = cellReceiverName;
        emit cellReceiverNameChanged(m_cellReceiverName);
    }
}

void LinePlan::setCellSenderName(QString cellSenderName)
{
    if (m_cellSenderName != cellSenderName){
        m_cellSenderName = cellSenderName;
        emit cellSenderNameChanged(m_cellSenderName);
    }
}

void LinePlan::setContainerReceiverName(QString containerReceiverName)
{
    if (m_containerReceiverName != containerReceiverName){
        m_containerReceiverName = containerReceiverName;
        emit containerReceiverNameChanged(m_containerReceiverName);
    }
}

void LinePlan::setContainerSenderName(QString containerSenderName)
{
    if (m_containerSenderName != containerSenderName){
        m_containerSenderName = containerSenderName;
        emit containerSenderNameChanged(m_containerSenderName);
    }
}
