#include "documentHeader.h"
#include "singleton.h"

DocumentHeader::DocumentHeader(QObject *parent) : QObject(parent)
{
    QObject::connect(Cache::get().employee(), &CacheListObject::listPushed,  this, &DocumentHeader::updateEmployee);
    QObject::connect(Cache::get().employee(), &CacheListObject::listUpdated, this, &DocumentHeader::updateEmployee);

    resetAll();
}

DocumentHeader::DocumentHeader(const QJsonObject& obj, QObject* parent) : DocumentHeader(parent)
{
    fromJson(obj);
}

QJsonObject DocumentHeader::toJson() const
{
    QJsonArray array;
    for (auto it : m_cellIdList)
        array.push_back(it);
    auto obj = WJson::createObject({
            std::make_pair(WJson::Id, m_id),
            std::make_pair(WJson::Name, m_name),
            std::make_pair(WJson::Supplier, m_supplier),
            std::make_pair(WJson::Date_created,   m_dateCreated.toString  (Setting::get().server()->dateFormat())),
            std::make_pair(WJson::Date_accepted,  m_dateAccepted.toString (Setting::get().server()->dateFormat())),
            std::make_pair(WJson::Date_completed, m_dateCompleted.toString(Setting::get().server()->dateFormat())),
            std::make_pair(WJson::IsStaticCellContains, m_isStaticCellContains),
            std::make_pair(WJson::IsCanChangeCell, m_isCanChangeCell),
            std::make_pair(WJson::IsTwoVerifyAccepted, m_isTwoVerifyAccepted),
            std::make_pair(WJson::IsGeoposition, m_isGeoposition),
            std::make_pair(WJson::Employee_receiver_id, m_employeeReceiverId),
            std::make_pair(WJson::Employee_receiver_name, m_employeeReceiverName),
            std::make_pair(WJson::Employee_sender_id, m_employeeSenderId),
            std::make_pair(WJson::Employee_sender_name, m_employeeSenderName)
    });
    WJson::insert(obj, WJson::Cell_id_list, QJsonValue(array));
    return obj;
}

void DocumentHeader::fromJson(const QJsonObject& obj)
{
    if (WJson::contains(obj, WJson::Id))
        setId(WJson::get(obj, WJson::Id).toString());

    if (WJson::contains(obj, WJson::Name))
        setName(WJson::get(obj, WJson::Name).toString());

    if (WJson::contains(obj, WJson::Supplier))
        setSupplier(WJson::get(obj, WJson::Supplier).toString());

    if (WJson::contains(obj, WJson::Date_created))
        setDateCreated(QDateTime::fromString(WJson::get(obj, WJson::Date_created).toString(),
                                             Setting::get().server()->dateFormat()));

    if (WJson::contains(obj, WJson::Date_accepted))
        setDateAccepted(QDateTime::fromString(WJson::get(obj, WJson::Date_accepted).toString(),
                                              Setting::get().server()->dateFormat()));

    if (WJson::contains(obj, WJson::Date_completed))
        setDateCompleted(QDateTime::fromString(WJson::get(obj, WJson::Date_completed).toString(),
                                               Setting::get().server()->dateFormat()));

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
}

void DocumentHeader::setId(QString id)
{
    if (m_id != id){
        m_id = id;
        emit idChanged(m_id);
    }
}

void DocumentHeader::setName(QString name)
{
    if (m_name != name){
        m_name = name;
        emit nameChanged(m_name);
    }
}

void DocumentHeader::setSupplier(QString supplier)
{
    if (m_supplier != supplier){
        m_supplier = supplier;
        emit supplierChanged(m_supplier);
    }
}

void DocumentHeader::setDateCreated(QDateTime dateCreated)
{
    if (m_dateCreated != dateCreated){
        m_dateCreated = dateCreated;
        emit dateCreatedChanged(m_dateCreated);
    }
}

void DocumentHeader::setDateAccepted(QDateTime dateAccepted)
{
    if (m_dateAccepted != dateAccepted){
        m_dateAccepted = dateAccepted;
        emit dateAcceptedChanged(m_dateAccepted);
    }
}

void DocumentHeader::setDateCompleted(QDateTime dateCompleted)
{
    if (m_dateCompleted != dateCompleted){
        m_dateCompleted = dateCompleted;
        emit dateCompletedChanged(m_dateCompleted);
    }
}

void DocumentHeader::setCellIdList(QStringList cellIdList)
{
    if (m_cellIdList != cellIdList){
        m_cellIdList = cellIdList;
        emit cellIdListChanged(m_cellIdList);
    }
}

void DocumentHeader::setIsStaticCellContains(bool isStaticCellContains)
{
    if (m_isStaticCellContains != isStaticCellContains){
        m_isStaticCellContains = isStaticCellContains;
        emit isStaticCellContainsChanged(m_isStaticCellContains);
    }
}

void DocumentHeader::setIsCanChangeCell(bool isCanChangeCell)
{
    if (m_isCanChangeCell != isCanChangeCell){
        m_isCanChangeCell = isCanChangeCell;
        emit isCanChangeCellChanged(m_isCanChangeCell);
    }
}

void DocumentHeader::setIsTwoVerifyAccepted(bool isTwoVerifyAccepted)
{
    if (m_isTwoVerifyAccepted != isTwoVerifyAccepted){
        m_isTwoVerifyAccepted = isTwoVerifyAccepted;
        emit isTwoVerifyAcceptedChanged(m_isTwoVerifyAccepted);
    }
}

void DocumentHeader::setIsGeoposition(bool isGeoposition)
{
    if (m_isGeoposition != isGeoposition){
        m_isGeoposition = isGeoposition;
        emit isGeopositionChanged(m_isGeoposition);
    }
}

void DocumentHeader::setEmployeeSenderId(QString employeeSenderId)
{
    if (m_employeeSenderId != employeeSenderId){
        m_employeeSenderId = employeeSenderId;
        emit employeeSenderIdChanged(m_employeeSenderId);
        updateEmployeeSenderName();
    }
}

void DocumentHeader::setEmployeeSenderName(QString employeeSenderName)
{
    if (m_employeeSenderName != employeeSenderName){
        m_employeeSenderName = employeeSenderName;
        emit employeeSenderNameChanged(m_employeeSenderName);
    }
}

void DocumentHeader::setEmployeeReceiverId(QString employeeReceiverId)
{
    if (m_employeeReceiverId != employeeReceiverId){
        m_employeeReceiverId = employeeReceiverId;
        emit employeeReceiverIdChanged(m_employeeReceiverId);
        updateEmployeeReceiverName();
    }
}

void DocumentHeader::setEmployeeReceiverName(QString employeeReceiverName)
{
    if (m_employeeReceiverName != employeeReceiverName){
        m_employeeReceiverName = employeeReceiverName;
        emit employeeReceiverNameChanged(m_employeeReceiverName);
    }
}

void DocumentHeader::updateEmployee(QStringList list)
{
    if (list.contains(m_employeeReceiverId))
        updateEmployeeReceiverName();
    if (list.contains(m_employeeSenderId))
        updateEmployeeSenderName();
}

void DocumentHeader::updateEmployeeSenderName()
{
    setEmployeeSenderName(Cache::get().employee()->getNameById(m_employeeSenderId));
}

void DocumentHeader::updateEmployeeReceiverName()
{
    setEmployeeReceiverName(Cache::get().employee()->getNameById(m_employeeReceiverId));
}

void DocumentHeader::resetAll()
{
    resetCellIdList();
    resetDateAccepted();
    resetDateCompleted();
    resetDateCreated();
    resetId();
    resetIsStaticCellContains();
    resetName();
    resetSupplier();
    resetEmployeeReceiverName();
    resetEmployeeReceiverId();
    resetEmployeeSenderName();
    resetEmployeeSenderId();
    resetIsTwoVerifyAccepted();
    resetIsCanChangeCell();
    resetIsGeoposition();
}
