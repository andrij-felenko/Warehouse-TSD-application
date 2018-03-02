#include "wDocumentHeader.h"
#include "wSingleton.h"

WDocumentHeader::WDocumentHeader(QObject *parent) : QObject(parent)
{
    typedef WCacheListObject WCLO;
    QObject::connect(WCache::get().employee(), &WCLO::listPushed,  this, &WDocumentHeader::updateEmployee);
    QObject::connect(WCache::get().employee(), &WCLO::listUpdated, this, &WDocumentHeader::updateEmployee);
    QObject::connect(WCache::get().supplier(), &WCLO::listPushed,  this, &WDocumentHeader::updateSupplier);
    QObject::connect(WCache::get().supplier(), &WCLO::listUpdated, this, &WDocumentHeader::updateSupplier);

    resetAll();
}

WDocumentHeader::WDocumentHeader(const QJsonObject& obj, QObject* parent) : WDocumentHeader(parent)
{
    fromJson(obj);
}

QJsonObject WDocumentHeader::toJson() const
{
    QJsonArray array;
    for (auto it : m_cellIdList)
        array.push_back(it);
    auto obj = WJsonConverter::createObject({
            std::make_pair(WJsonEnum::Id, m_id),
            std::make_pair(WJsonEnum::Name, m_name),
            std::make_pair(WJsonEnum::Supplier_id, m_supplierId),
            std::make_pair(WJsonEnum::Supplier_name, m_supplierName),
            std::make_pair(WJsonEnum::Date_created,   m_dateCreated.toString  (WSetting::get().server()->dateFormat())),
            std::make_pair(WJsonEnum::Date_accepted,  m_dateAccepted.toString (WSetting::get().server()->dateFormat())),
            std::make_pair(WJsonEnum::Date_completed, m_dateCompleted.toString(WSetting::get().server()->dateFormat())),
            std::make_pair(WJsonEnum::IsStaticCellContains, m_isStaticCellContains),
            std::make_pair(WJsonEnum::IsCanChangeCell, m_isCanChangeCell),
            std::make_pair(WJsonEnum::IsTwoVerifyAccepted, m_isTwoVerifyAccepted),
            std::make_pair(WJsonEnum::IsGeoposition, m_isGeoposition),
            std::make_pair(WJsonEnum::Employee_receiver_id, m_employeeReceiverId),
            std::make_pair(WJsonEnum::Employee_receiver_name, m_employeeReceiverName),
            std::make_pair(WJsonEnum::Employee_sender_id, m_employeeSenderId),
            std::make_pair(WJsonEnum::Employee_sender_name, m_employeeSenderName),
            std::make_pair(WJsonEnum::Status, static_cast <int> (m_status) - +WEnum::Document_created)
    });
    WJsonConverter::insert(obj, WJsonEnum::Cell_id_list, QJsonValue(array));
    return obj;
}

void WDocumentHeader::fromJson(const QJsonObject& obj)
{
    if (WJsonConverter::contains(obj, WJsonEnum::Id))
        setId(WJsonConverter::get(obj, WJsonEnum::Id).toString());

    if (WJsonConverter::contains(obj, WJsonEnum::Name))
        setName(WJsonConverter::get(obj, WJsonEnum::Name).toString());

    if (WJsonConverter::contains(obj, WJsonEnum::Date_created))
        setDateCreated(QDateTime::fromString(WJsonConverter::get(obj, WJsonEnum::Date_created).toString(),
                                             WSetting::get().server()->dateFormat()));

    if (WJsonConverter::contains(obj, WJsonEnum::Date_accepted))
        setDateAccepted(QDateTime::fromString(WJsonConverter::get(obj, WJsonEnum::Date_accepted).toString(),
                                              WSetting::get().server()->dateFormat()));

    if (WJsonConverter::contains(obj, WJsonEnum::Date_completed))
        setDateCompleted(QDateTime::fromString(WJsonConverter::get(obj, WJsonEnum::Date_completed).toString(),
                                               WSetting::get().server()->dateFormat()));

    if (WJsonConverter::contains(obj, WJsonEnum::IsStaticCellContains))
        setIsStaticCellContains(WJsonConverter::get(obj, WJsonEnum::IsStaticCellContains).toBool());

    if (WJsonConverter::contains(obj, WJsonEnum::IsCanChangeCell))
        setIsCanChangeCell(WJsonConverter::get(obj, WJsonEnum::IsCanChangeCell).toBool());

    if (WJsonConverter::contains(obj, WJsonEnum::IsGeoposition))
        setIsGeoposition(WJsonConverter::get(obj, WJsonEnum::IsGeoposition).toBool());

    if (WJsonConverter::contains(obj, WJsonEnum::IsTwoVerifyAccepted))
        setIsTwoVerifyAccepted(WJsonConverter::get(obj, WJsonEnum::IsTwoVerifyAccepted).toBool());

    if (WJsonConverter::contains(obj, WJsonEnum::Cell_id_list)){
        QStringList list;
        for (auto it : WJsonConverter::get(obj, WJsonEnum::Line_number).toArray())
            list.push_back(it.toString());
        setCellIdList(list);
    }

    // sender
    if (WJsonConverter::contains(obj, WJsonEnum::Employee_sender_id))
        setEmployeeSenderId(WJsonConverter::get(obj, WJsonEnum::Employee_sender_id).toString());

    if (WJsonConverter::contains(obj, WJsonEnum::Employee_sender_name))
        setEmployeeSenderName(WJsonConverter::get(obj, WJsonEnum::Employee_sender_name).toString());
    else
        updateEmployeeSenderName();

    // receiver
    if (WJsonConverter::contains(obj, WJsonEnum::Employee_receiver_id))
        setEmployeeReceiverId(WJsonConverter::get(obj, WJsonEnum::Employee_receiver_id).toString());

    if (WJsonConverter::contains(obj, WJsonEnum::Employee_receiver_name))
        setEmployeeReceiverName(WJsonConverter::get(obj, WJsonEnum::Employee_receiver_name).toString());
    else
        updateEmployeeReceiverName();

    // supplier
    if (WJsonConverter::contains(obj, WJsonEnum::Supplier_id))
        setSupplierId(WJsonConverter::get(obj, WJsonEnum::Supplier_id).toString());

    if (WJsonConverter::contains(obj, WJsonEnum::Supplier_name))
        setSupplierName(WJsonConverter::get(obj, WJsonEnum::Supplier_name).toString());
    else
        updateSupplierName();

    // status
    if (WJsonConverter::contains(obj, WJsonEnum::Status))
        setStatus(static_cast <WEnum::DocumentStatus> (static_cast <int> (WEnum::Document_created)
                                                       + WJsonConverter::get(obj, WJsonEnum::Status).toInt()));
    else
        resetStatus();
}

void WDocumentHeader::setId(QString id)
{
    if (m_id != id){
        m_id = id;
        emit idChanged(m_id);
    }
}

void WDocumentHeader::setName(QString name)
{
    if (m_name != name){
        m_name = name;
        emit nameChanged(m_name);
    }
}

void WDocumentHeader::setSupplierId(QString supplierId)
{
    if (m_supplierId != supplierId){
        m_supplierId = supplierId;
        emit supplierIdChanged(m_supplierId);
    }
}

void WDocumentHeader::setDateCreated(QDateTime dateCreated)
{
    if (m_dateCreated != dateCreated){
        m_dateCreated = dateCreated;
        emit dateCreatedChanged(m_dateCreated);
    }
}

void WDocumentHeader::setDateAccepted(QDateTime dateAccepted)
{
    if (m_dateAccepted != dateAccepted){
        m_dateAccepted = dateAccepted;
        emit dateAcceptedChanged(m_dateAccepted);
    }
}

void WDocumentHeader::setDateCompleted(QDateTime dateCompleted)
{
    if (m_dateCompleted != dateCompleted){
        m_dateCompleted = dateCompleted;
        emit dateCompletedChanged(m_dateCompleted);
    }
}

void WDocumentHeader::setCellIdList(QStringList cellIdList)
{
    if (m_cellIdList != cellIdList){
        m_cellIdList = cellIdList;
        emit cellIdListChanged(m_cellIdList);
    }
}

void WDocumentHeader::setIsStaticCellContains(bool isStaticCellContains)
{
    if (m_isStaticCellContains != isStaticCellContains){
        m_isStaticCellContains = isStaticCellContains;
        emit isStaticCellContainsChanged(m_isStaticCellContains);
    }
}

void WDocumentHeader::setIsCanChangeCell(bool isCanChangeCell)
{
    if (m_isCanChangeCell != isCanChangeCell){
        m_isCanChangeCell = isCanChangeCell;
        emit isCanChangeCellChanged(m_isCanChangeCell);
    }
}

void WDocumentHeader::setIsTwoVerifyAccepted(bool isTwoVerifyAccepted)
{
    if (m_isTwoVerifyAccepted != isTwoVerifyAccepted){
        m_isTwoVerifyAccepted = isTwoVerifyAccepted;
        emit isTwoVerifyAcceptedChanged(m_isTwoVerifyAccepted);
    }
}

void WDocumentHeader::setIsGeoposition(bool isGeoposition)
{
    if (m_isGeoposition != isGeoposition){
        m_isGeoposition = isGeoposition;
        emit isGeopositionChanged(m_isGeoposition);
    }
}

void WDocumentHeader::setEmployeeSenderId(QString employeeSenderId)
{
    if (m_employeeSenderId != employeeSenderId){
        m_employeeSenderId = employeeSenderId;
        emit employeeSenderIdChanged(m_employeeSenderId);
        updateEmployeeSenderName();
    }
}

void WDocumentHeader::setEmployeeSenderName(QString employeeSenderName)
{
    if (m_employeeSenderName != employeeSenderName){
        m_employeeSenderName = employeeSenderName;
        emit employeeSenderNameChanged(m_employeeSenderName);
    }
}

void WDocumentHeader::setEmployeeReceiverId(QString employeeReceiverId)
{
    if (m_employeeReceiverId != employeeReceiverId){
        m_employeeReceiverId = employeeReceiverId;
        emit employeeReceiverIdChanged(m_employeeReceiverId);
        updateEmployeeReceiverName();
    }
}

void WDocumentHeader::setStatus(WEnum::DocumentStatus status)
{
    if (m_status == status)
        return;

    m_status = status;
    emit statusChanged(m_status);
}

void WDocumentHeader::setEmployeeReceiverName(QString employeeReceiverName)
{
    if (m_employeeReceiverName != employeeReceiverName){
        m_employeeReceiverName = employeeReceiverName;
        emit employeeReceiverNameChanged(m_employeeReceiverName);
    }
}

void WDocumentHeader::setSupplierName(QString supplierName)
{
    if (m_supplierName != supplierName){
        m_supplierName = supplierName;
        emit supplierNameChanged(m_supplierName);
    }
}

void WDocumentHeader::updateEmployee(QStringList list)
{
    if (list.contains(m_employeeReceiverId))
        updateEmployeeReceiverName();
    if (list.contains(m_employeeSenderId))
        updateEmployeeSenderName();
}

void WDocumentHeader::updateSupplier(QStringList list)
{
    if (list.contains(m_supplierId))
        updateSupplierName();
}

void WDocumentHeader::updateSupplierName()
{
    setSupplierName(WCache::get().supplier()->getNameById(m_supplierId));
}

void WDocumentHeader::updateEmployeeSenderName()
{
    setEmployeeSenderName(WCache::get().employee()->getNameById(m_employeeSenderId));
}

void WDocumentHeader::updateEmployeeReceiverName()
{
    setEmployeeReceiverName(WCache::get().employee()->getNameById(m_employeeReceiverId));
}

void WDocumentHeader::resetAll()
{
    resetCellIdList();
    resetDateAccepted();
    resetDateCompleted();
    resetDateCreated();
    resetId();
    resetIsStaticCellContains();
    resetName();
    resetSupplierName();
    resetSupplierId();
    resetEmployeeReceiverName();
    resetEmployeeReceiverId();
    resetEmployeeSenderName();
    resetEmployeeSenderId();
    resetIsTwoVerifyAccepted();
    resetIsCanChangeCell();
    resetIsGeoposition();
    resetStatus();
}
