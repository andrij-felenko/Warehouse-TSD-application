#include "wModelDocumentList.h"
#include "wSingleton.h"

WModelDocumentList::WModelDocumentList(WUrl::WUrl_enum key, QObject *parent)
    : QAbstractListModel(parent), key(key), m_lastLength(0)
{
    QObject::connect(WDocument::registrate(), &WDocumentPrototype::documentListUpdate, this, [=](WUrl::WUrl_enum key)
    {
        if (key == this->key)
            updateAll();
    });
    updateAll();
}

QHash<int, QByteArray> WModelDocumentList::roleNames() const
{
    return WEnum::getModelHash();
}

QVariant WModelDocumentList::data(const QModelIndex& index, int role) const
{
    if (index.row() > m_lastLength and index.row() < 0)
        return QVariant();

    auto document = WDocument::get().getDocument(key, index.row());
    if (document->id() == WStatic::guidDefault())
        return QVariant();

    switch(static_cast <WEnum::ModelItems> (role)) {
    case WEnum::Model_item: return QVariant::fromValue(document);
    case WEnum::Model_id: return document->id();
    case WEnum::Model_name: return document->name();
    default:;
    }
    return QVariant();
}

int WModelDocumentList::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return m_lastLength;
}

bool WModelDocumentList::containsId(QString id)
{
    return WDocument::get().containsId(key, id);
}

void WModelDocumentList::updateAll()
{
    beginRemoveRows(QModelIndex(), 0, m_lastLength);
    endRemoveRows();

    m_lastLength = WDocument::get().getDocumentLengthByKey(key);
    beginInsertRows(QModelIndex(), 0, m_lastLength - 1);
    endInsertRows();

    emit dataChanged(this->index(0, 0), this->index(rowCount() - 1, 0));
}
