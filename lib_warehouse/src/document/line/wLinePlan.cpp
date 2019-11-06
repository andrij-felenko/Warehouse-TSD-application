#include "document/line/wLinePlan.h"
#include "wSingleton.h"

WLinePlan::WLinePlan(QObject *parent) : QObject(parent)
{
    typedef WCacheListObject WCLO;
    QObject::connect(WCache::get().cell(), &WCLO::listPushed,  this, &WLinePlan::updateCell);
    QObject::connect(WCache::get().cell(), &WCLO::listUpdated, this, &WLinePlan::updateCell);
    QObject::connect(WCache::get().container(), &WCLO::listPushed,  this, &WLinePlan::updateContainer);
    QObject::connect(WCache::get().container(), &WCLO::listUpdated, this, &WLinePlan::updateContainer);
    QObject::connect(WCache::get().quality(), &WCLO::listPushed,  this, &WLinePlan::updateQuality);
    QObject::connect(WCache::get().quality(), &WCLO::listUpdated, this, &WLinePlan::updateQuality);
    QObject::connect(WCache::get().nomenclature(), &WCLO::listPushed,  this, &WLinePlan::updateNomenclature);
    QObject::connect(WCache::get().nomenclature(), &WCLO::listUpdated, this, &WLinePlan::updateNomenclature);
    QObject::connect(WCache::get().consignment(), &WCLO::listPushed,  this, &WLinePlan::updateConsignment);
    QObject::connect(WCache::get().consignment(), &WCLO::listUpdated, this, &WLinePlan::updateConsignment);

    resetAll();
}

WLinePlan::WLinePlan(const QJsonObject& obj, QObject* parent) : WLinePlan(parent)
{
    fromJson(obj);
}

QJsonObject WLinePlan::toJson() const
{
    return WJsonConverter::createObject({
        std::make_pair(WJsonEnum::Is_done, m_isDone),
        std::make_pair(WJsonEnum::Quantity, m_quantity),
        std::make_pair(WJsonEnum::Line_number, m_lineNumber),
        std::make_pair(WJsonEnum::Consignment_id,   m_consignmentId),
        std::make_pair(WJsonEnum::Consignment_name, m_consignmentName),
        std::make_pair(WJsonEnum::Nomenclature_id,   m_nomenclatureId),
        std::make_pair(WJsonEnum::Nomenclature_name, m_nomenclatureName),
        std::make_pair(WJsonEnum::Quality_id,   m_qualityId),
        std::make_pair(WJsonEnum::Quality_name, m_qualityName),
        std::make_pair(WJsonEnum::Container_receiver_id,   m_containerReceiverId),
        std::make_pair(WJsonEnum::Container_receiver_name, m_containerReceiverName),
        std::make_pair(WJsonEnum::Container_sender_id,   m_containerSenderId),
        std::make_pair(WJsonEnum::Container_sender_name, m_containerSenderName),
        std::make_pair(WJsonEnum::Cell_receiver_id,   m_cellReceiverId),
        std::make_pair(WJsonEnum::Cell_receiver_name, m_cellReceiverName),
        std::make_pair(WJsonEnum::Cell_sender_id,   m_cellSenderId),
        std::make_pair(WJsonEnum::Cell_sender_name, m_cellSenderName),
    });
}

void WLinePlan::fromJson(const QJsonObject& obj)
{
    if (WJsonConverter::contains(obj, WJsonEnum::Is_done))
        setIsDone(WJsonConverter::get(obj, WJsonEnum::Is_done).toBool());

    // Quantity
    if (WJsonConverter::contains(obj, WJsonEnum::Quantity))
        setQuantity(WJsonConverter::get(obj, WJsonEnum::Quantity).toInt());

    // Line number
    if (WJsonConverter::contains(obj, WJsonEnum::Line_number))
        setLineNumber(WJsonConverter::get(obj, WJsonEnum::Line_number).toInt());

    // Consignment
    if (WJsonConverter::contains(obj, WJsonEnum::Consignment_id))
        setConsignmentId(WJsonConverter::get(obj, WJsonEnum::Consignment_id).toString());

    if (WJsonConverter::contains(obj, WJsonEnum::Consignment_name))
        setConsignmentName(WJsonConverter::get(obj, WJsonEnum::Consignment_name).toString());
    else
        updateConsignmentName();

    // Nomenclature
    if (WJsonConverter::contains(obj, WJsonEnum::Nomenclature_id))
        setNomenclatureId(WJsonConverter::get(obj, WJsonEnum::Nomenclature_id).toString());

    if (WJsonConverter::contains(obj, WJsonEnum::Nomenclature_name))
        setNomenclatureName(WJsonConverter::get(obj, WJsonEnum::Nomenclature_name).toString());
    else
        updateNomenclatureName();

    // Quality
    if (WJsonConverter::contains(obj, WJsonEnum::Quality_id))
        setQualityId(WJsonConverter::get(obj, WJsonEnum::Quality_id).toString());

    if (WJsonConverter::contains(obj, WJsonEnum::Quality_name))
        setQualityName(WJsonConverter::get(obj, WJsonEnum::Quality_name).toString());
    else
        updateQualityName();

    // Container
    if (WJsonConverter::contains(obj, WJsonEnum::Container_receiver_id))
        setContainerReceiverId(WJsonConverter::get(obj, WJsonEnum::Container_receiver_id).toString());

    if (WJsonConverter::contains(obj, WJsonEnum::Container_receiver_name))
        setContainerReceiverName(WJsonConverter::get(obj, WJsonEnum::Container_receiver_name).toString());
    else
        updateContainerReceiverName();

    if (WJsonConverter::contains(obj, WJsonEnum::Container_sender_id))
        setContainerSenderId(WJsonConverter::get(obj, WJsonEnum::Container_sender_id).toString());

    if (WJsonConverter::contains(obj, WJsonEnum::Container_sender_name))
        setContainerSenderName(WJsonConverter::get(obj, WJsonEnum::Container_sender_name).toString());
    else
        updateContainerSenderName();

    // Cell
    if (WJsonConverter::contains(obj, WJsonEnum::Cell_receiver_id))
        setCellReceiverId(WJsonConverter::get(obj, WJsonEnum::Cell_receiver_id).toString());

    if (WJsonConverter::contains(obj, WJsonEnum::Cell_receiver_name))
        setCellReceiverName(WJsonConverter::get(obj, WJsonEnum::Cell_receiver_name).toString());
    else
        updateCellReceiverName();

    if (WJsonConverter::contains(obj, WJsonEnum::Cell_sender_id))
        setCellSenderId(WJsonConverter::get(obj, WJsonEnum::Cell_sender_id).toString());

    if (WJsonConverter::contains(obj, WJsonEnum::Cell_sender_name))
        setCellSenderName(WJsonConverter::get(obj, WJsonEnum::Cell_sender_name).toString());
    else
        updateCellSenderName();
}

QString WLinePlan::getVariableByJsonKey(WJsonEnum::WJson_enum key) const
{
    switch (key) {
    case WJsonEnum::Container_receiver_id: return m_containerReceiverId;
    case WJsonEnum::Container_sender_id: return m_containerSenderId;
    case WJsonEnum::Cell_receiver_id: return m_cellReceiverId;
    case WJsonEnum::Cell_sender_id: return m_cellSenderId;
    case WJsonEnum::Consignment_id: return m_consignmentId;
    case WJsonEnum::Quality_id: return m_qualityId;
    case WJsonEnum::Nomenclature_id: return m_nomenclatureId;
    default:;
    }
    return WStatic::guidDefault();
}

bool WLinePlan::isConcordiaLineByParameter(QVariantMap map)
{
    for (auto it = map.begin(); it != map.end(); ++it){
        switch (static_cast <WJsonEnum::WJson_enum> (it.value().toInt())) {
        case WJsonEnum::Container_receiver_id:
            if (m_containerReceiverId != it.key())
                return false;
            break;
        case WJsonEnum::Container_sender_id:
            if (m_containerSenderId != it.key())
                return false;
            break;
        case WJsonEnum::Cell_receiver_id:
            if (m_cellReceiverId != it.key())
                return false;
            break;
        case WJsonEnum::Cell_sender_id:
            if (m_cellSenderId != it.key())
                return false;
            break;
        case WJsonEnum::Consignment_id:
            if (m_consignmentId != it.key())
                return false;
            break;
        case WJsonEnum::Quality_id:
            if (m_qualityId != it.key())
                return false;
            break;
        case WJsonEnum::Nomenclature_id:
            if (m_nomenclatureId != it.key())
                return false;
            break;
        default:
            return false;
        }
    }
    return true;
}

void WLinePlan::resetAll()
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

void WLinePlan::setConsignmentId(QString consignmentId)
{
    if (m_consignmentId != consignmentId){
        m_consignmentId = consignmentId;
        emit consignmentIdChanged(m_consignmentId);
        updateConsignmentName();
    }
}

void WLinePlan::setNomenclatureId(QString nomenclatureId)
{
    if (m_nomenclatureId != nomenclatureId){
        m_nomenclatureId = nomenclatureId;
        emit nomenclatureIdChanged(m_nomenclatureId);
        updateNomenclatureName();
    }
}

void WLinePlan::setIsDone(bool isDone)
{
    if (m_isDone != isDone){
        m_isDone = isDone;
        emit isDoneChanged(m_isDone);
    }
}

void WLinePlan::setQualityId(QString qualityId)
{
    if (m_qualityId != qualityId){
        m_qualityId = qualityId;
        emit qualityIdChanged(m_qualityId);
        updateQualityName();
    }
}

void WLinePlan::setCellReceiverId(QString cellReceiverId)
{
    if (m_cellReceiverId != cellReceiverId){
        m_cellReceiverId = cellReceiverId;
        emit cellReceiverIdChanged(m_cellReceiverId);
        updateCellReceiverName();
    }
}

void WLinePlan::setCellSenderId(QString cellSenderId)
{
    if (m_cellSenderId != cellSenderId){
        m_cellSenderId = cellSenderId;
        emit cellSenderIdChanged(m_cellSenderId);
        updateCellSenderName();
    }
}

void WLinePlan::setContainerReceiverId(QString containerReceiverId)
{
    if (m_containerReceiverId != containerReceiverId){
        m_containerReceiverId = containerReceiverId;
        emit containerReceiverIdChanged(m_containerReceiverId);
        updateContainerReceiverName();
    }
}

void WLinePlan::setContainerSenderId(QString containerSenderId)
{
    if (m_containerSenderId != containerSenderId){
        m_containerSenderId = containerSenderId;
        emit containerSenderIdChanged(m_containerSenderId);
        updateContainerSenderName();
    }
}

void WLinePlan::setQuantity(int quantity)
{
    if (m_quantity != quantity){
        m_quantity = quantity;
        emit quantityChanged(m_quantity);
    }
}

void WLinePlan::setLineNumber(int lineNumber)
{
    if (m_lineNumber != lineNumber){
        m_lineNumber = lineNumber;
        emit lineNumberChanged(m_lineNumber);
    }
}

void WLinePlan::updateCell(QStringList list)
{
    if (list.contains(m_cellReceiverId))
        updateCellReceiverName();
    if (list.contains(m_cellSenderId))
        updateCellSenderName();
}

void WLinePlan::updateContainer(QStringList list)
{
    if (list.contains(m_containerReceiverId))
        updateContainerReceiverName();
    if (list.contains(m_containerSenderId))
        updateContainerSenderName();
}

void WLinePlan::updateQuality(QStringList list)
{
    if (list.contains(m_qualityId))
        updateQualityName();
}

void WLinePlan::updateConsignment(QStringList list)
{
    if (list.contains(m_consignmentId))
        updateConsignmentName();
}

void WLinePlan::updateNomenclature(QStringList list)
{
    if (list.contains(m_nomenclatureId))
        updateNomenclatureName();
}

void WLinePlan::updateConsignmentName()
{
    setConsignmentName(WCache::get().consignment()->getNameById(m_consignmentId));
}

void WLinePlan::updateQualityName()
{
    setQualityName(WCache::get().quality()->getNameById(m_qualityId));
}

void WLinePlan::updateNomenclatureName()
{
    setNomenclatureName(WCache::get().nomenclature()->getNameById(m_nomenclatureId));
}

void WLinePlan::updateContainerReceiverName()
{
    setContainerReceiverName(WCache::get().container()->getNameById(m_containerReceiverId));
}

void WLinePlan::updateContainerSenderName()
{
    setContainerSenderName(WCache::get().container()->getNameById(m_containerSenderId));
}

void WLinePlan::updateCellReceiverName()
{
    setCellReceiverName(WCache::get().cell()->getNameById(m_cellReceiverId));
}

void WLinePlan::updateCellSenderName()
{
    setCellSenderName(WCache::get().cell()->getNameById(m_cellSenderId));
}

void WLinePlan::setConsignmentName(QString consignmentName)
{
    if (m_consignmentName != consignmentName){
        m_consignmentName = consignmentName;
        emit consignmentNameChanged(m_consignmentName);
    }
}

void WLinePlan::setNomenclatureName(QString nomenclatureName)
{
    if (m_nomenclatureName != nomenclatureName){
        m_nomenclatureName = nomenclatureName;
        emit nomenclatureNameChanged(m_nomenclatureName);
    }
}

void WLinePlan::setQualityName(QString qualityName)
{
    if (m_qualityName != qualityName){
        m_qualityName = qualityName;
        emit qualityNameChanged(m_qualityName);
    }
}

void WLinePlan::setCellReceiverName(QString cellReceiverName)
{
    if (m_cellReceiverName != cellReceiverName){
        m_cellReceiverName = cellReceiverName;
        emit cellReceiverNameChanged(m_cellReceiverName);
    }
}

void WLinePlan::setCellSenderName(QString cellSenderName)
{
    if (m_cellSenderName != cellSenderName){
        m_cellSenderName = cellSenderName;
        emit cellSenderNameChanged(m_cellSenderName);
    }
}

void WLinePlan::setContainerReceiverName(QString containerReceiverName)
{
    if (m_containerReceiverName != containerReceiverName){
        m_containerReceiverName = containerReceiverName;
        emit containerReceiverNameChanged(m_containerReceiverName);
    }
}

void WLinePlan::setContainerSenderName(QString containerSenderName)
{
    if (m_containerSenderName != containerSenderName){
        m_containerSenderName = containerSenderName;
        emit containerSenderNameChanged(m_containerSenderName);
    }
}
