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
    auto obj = WJson::createObject({
            std::make_pair(WJson::Id, m_id),
            std::make_pair(WJson::Name, m_name),
            std::make_pair(WJson::Supplier_id, m_supplierId),
            std::make_pair(WJson::Supplier_name, m_supplierName),
            std::make_pair(WJson::Date_created,   m_dateCreated.toString  (WSetting::get().server()->dateFormat())),
            std::make_pair(WJson::Date_accepted,  m_dateAccepted.toString (WSetting::get().server()->dateFormat())),
            std::make_pair(WJson::Date_completed, m_dateCompleted.toString(WSetting::get().server()->dateFormat())),
            std::make_pair(WJson::IsStaticCellContains, m_isStaticCellContains),
            std::make_pair(WJson::IsCanChangeCell, m_isCanChangeCell),
            std::make_pair(WJson::IsTwoVerifyAccepted, m_isTwoVerifyAccepted),
            std::make_pair(WJson::IsGeoposition, m_isGeoposition),
            std::make_pair(WJson::Employee_receiver_id, m_employeeReceiverId),
            std::make_pair(WJson::Employee_receiver_name, m_employeeReceiverName),
            std::make_pair(WJson::Employee_sender_id, m_employeeSenderId),
            std::make_pair(WJson::Employee_sender_name, m_employeeSenderName),
            std::make_pair(WJson::Status, static_cast <int> (m_status) - +WEnum::Document_created)
    });
    WJson::insert(obj, WJson::Cell_id_list, QJsonValue(array));
    return obj;
}

void WDocumentHeader::fromJson(const QJsonObject& obj)
{
    if (WJson::contains(obj, WJson::Id))
        setId(WJson::get(obj, WJson::Id).toString());

    if (WJson::contains(obj, WJson::Name))
        setName(WJson::get(obj, WJson::Name).toString());

    if (WJson::contains(obj, WJson::Date_created))
        setDateCreated(QDateTime::fromString(WJson::get(obj, WJson::Date_created).toString(),
                                             WSetting::get().server()->dateFormat()));

    if (WJson::contains(obj, WJson::Date_accepted))
        setDateAccepted(QDateTime::fromString(WJson::get(obj, WJson::Date_accepted).toString(),
                                              WSetting::get().server()->dateFormat()));

    if (WJson::contains(obj, WJson::Date_completed))
        setDateCompleted(QDateTime::fromString(WJson::get(obj, WJson::Date_completed).toString(),
                                               WSetting::get().server()->dateFormat()));

    if (WJson::contains(obj, WJson::IsStaticCellContains))
        setIsStaticCellContains(WJson::get(obj, WJson::IsStaticCellContains).toBool());

    if (WJson::contains(obj, WJson::IsCanChangeCell))
        setIsCanChangeCell(WJson::get(obj, WJson::IsCanChangeCell).toBool());

    if (WJson::contains(obj, WJson::IsGeoposition))
        setIsGeoposition(WJson::get(obj, WJson::IsGeoposition).toBool());

    if (WJson::contains(obj, WJson::IsTwoVerifyAccepted))
        setIsTwoVerifyAccepted(WJson::get(obj, WJson::IsTwoVerifyAccepted).toBool());

    if (WJson::contains(obj, WJson::Cell_id_list)){
        QStringList list;
        for (auto it : WJson::get(obj, WJson::Line_number).toArray())
            list.push_back(it.toString());
        setCellIdList(list);
    }

    // sender
    if (WJson::contains(obj, WJson::Employee_sender_id))
        setEmployeeSenderId(WJson::get(obj, WJson::Employee_sender_id).toString());

    if (WJson::contains(obj, WJson::Employee_sender_name))
        setEmployeeSenderName(WJson::get(obj, WJson::Employee_sender_name).toString());
    else
        updateEmployeeSenderName();

    // receiver
    if (WJson::contains(obj, WJson::Employee_receiver_id))
        setEmployeeReceiverId(WJson::get(obj, WJson::Employee_receiver_id).toString());

    if (WJson::contains(obj, WJson::Employee_receiver_name))
        setEmployeeReceiverName(WJson::get(obj, WJson::Employee_receiver_name).toString());
    else
        updateEmployeeReceiverName();

    // supplier
    if (WJson::contains(obj, WJson::Supplier_id))
        setSupplierId(WJson::get(obj, WJson::Supplier_id).toString());

    if (WJson::contains(obj, WJson::Supplier_name))
        setSupplierName(WJson::get(obj, WJson::Supplier_name).toString());
    else
        updateSupplierName();

    // status
    if (WJson::contains(obj, WJson::Status))
        setStatus(static_cast <WEnum::DocumentStatus> (static_cast <int> (WEnum::Document_created)
                                                       + WJson::get(obj, WJson::Status).toInt()));
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
