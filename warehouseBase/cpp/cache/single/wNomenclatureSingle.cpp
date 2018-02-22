#include "wNomenclatureSingle.h"

WNomenclatureSingle::WNomenclatureSingle(QObject *parent) : WCacheSingle(parent)
{
    //
}

WNomenclatureSingle::WNomenclatureSingle(const QJsonObject &obj, QObject *parent)
    : WNomenclatureSingle(parent)
{
    fromJson(obj);
}

QJsonObject WNomenclatureSingle::toJson() const
{
    QJsonObject obj = WCacheSingle::toJson();
    WJson::insert(obj, WJson::Folder, m_folder);
    WJson::insert(obj, WJson::ModelTypeId, m_modelTypeId);
    WJson::insert(obj, WJson::Consignment, m_consignment); // FIXME
    return obj;
}

void WNomenclatureSingle::fromJson(const QJsonObject &obj)
{
    WCacheSingle::fromJson(obj);

    if (WJson::contains(obj, WJson::Folder))
        setFolder(WJson::get(obj, WJson::Folder).toString());

    if (WJson::contains(obj, WJson::ModelTypeId))
        setModelTypeId(WJson::get(obj, WJson::ModelTypeId).toString());

    // FIXME consignment list
}

QString WNomenclatureSingle::folder() const
{
    return m_folder;
}

QString WNomenclatureSingle::modelTypeId() const
{
    return m_modelTypeId;
}

QString WNomenclatureSingle::consignment() const
{
    return m_consignment;
}

void WNomenclatureSingle::resetFolder()
{
    setFolder("");
}

void WNomenclatureSingle::resetModelTypeId()
{
    setModelTypeId(WStatic::guidDefault());
}

void WNomenclatureSingle::resetConsignment()
{
    setConsignment(WStatic::guidDefault());
}

void WNomenclatureSingle::setFolder(QString folder)
{
    if (m_folder == folder)
        return;

    m_folder = folder;
    emit folderChanged(m_folder);
}

void WNomenclatureSingle::setModelTypeId(QString modelTypeId)
{
    if (m_modelTypeId == modelTypeId)
        return;

    m_modelTypeId = modelTypeId;
    emit modelTypeIdChanged(m_modelTypeId);
}

void WNomenclatureSingle::setConsignment(QString consignment)
{
    if (m_consignment == consignment)
        return;

    m_consignment = consignment;
    emit consignmentChanged(m_consignment);
}

QDataStream& operator << (QDataStream& s, WNomenclatureSingle& d)
{
    return s << static_cast <WCacheSingle&> (d) << d.m_consignment << d.m_folder << d.m_modelTypeId;
}

QDataStream& operator >> (QDataStream& s, WNomenclatureSingle& d)
{
    return s >> static_cast <WCacheSingle&> (d) >> d.m_consignment >> d.m_folder >> d.m_modelTypeId;
}
