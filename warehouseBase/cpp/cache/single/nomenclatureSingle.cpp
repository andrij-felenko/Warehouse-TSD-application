#include "nomenclatureSingle.h"

NomenclatureSingle::NomenclatureSingle(QObject *parent) : CacheSingle(parent)
{
    //
}

NomenclatureSingle::NomenclatureSingle(const QJsonObject &obj, QObject *parent) : NomenclatureSingle(parent)
{
    fromJson(obj);
}

QJsonObject NomenclatureSingle::toJson() const
{
    QJsonObject obj = CacheSingle::toJson();
    WJson::insert(obj, WJson::Folder, m_folder);
    WJson::insert(obj, WJson::ModelTypeId, m_modelTypeId);
    WJson::insert(obj, WJson::Consignment, m_consignment); // FIXME
    return obj;
}

void NomenclatureSingle::fromJson(const QJsonObject &obj)
{
    CacheSingle::fromJson(obj);

    if (WJson::contains(obj, WJson::Folder))
        setFolder(WJson::get(obj, WJson::Folder).toString());

    if (WJson::contains(obj, WJson::ModelTypeId))
        setModelTypeId(WJson::get(obj, WJson::ModelTypeId).toString());

    // FIXME consignment list
}

QString NomenclatureSingle::folder() const
{
    return m_folder;
}

QString NomenclatureSingle::modelTypeId() const
{
    return m_modelTypeId;
}

QString NomenclatureSingle::consignment() const
{
    return m_consignment;
}

void NomenclatureSingle::resetFolder()
{
    setFolder("");
}

void NomenclatureSingle::resetModelTypeId()
{
    setModelTypeId(WStatic::guidDefault());
}

void NomenclatureSingle::resetConsignment()
{
    setConsignment(WStatic::guidDefault());
}

void NomenclatureSingle::setFolder(QString folder)
{
    if (m_folder == folder)
        return;

    m_folder = folder;
    emit folderChanged(m_folder);
}

void NomenclatureSingle::setModelTypeId(QString modelTypeId)
{
    if (m_modelTypeId == modelTypeId)
        return;

    m_modelTypeId = modelTypeId;
    emit modelTypeIdChanged(m_modelTypeId);
}

void NomenclatureSingle::setConsignment(QString consignment)
{
    if (m_consignment == consignment)
        return;

    m_consignment = consignment;
    emit consignmentChanged(m_consignment);
}
