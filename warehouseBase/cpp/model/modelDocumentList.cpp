#include "modelDocumentList.h"
#include "singleton.h"

ModelDocumentList::ModelDocumentList(WUrl::WUrl_enum key, QObject *parent)
    : QAbstractListModel(parent), key(key)
{
    // FIXME
}

QHash<int, QByteArray> ModelDocumentList::roleNames() const
{
    return roles;
}

QVariant ModelDocumentList::data(const QModelIndex& index, int role) const
{
    // FIXME
}

int ModelDocumentList::rowCount(const QModelIndex& parent) const
{
    // FIXME
}

bool ModelDocumentList::containsId(QString id)
{
    // FIXME
}

