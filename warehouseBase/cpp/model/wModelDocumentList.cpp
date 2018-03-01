#include "wModelDocumentList.h"
#include "wSingleton.h"

WModelDocumentList::WModelDocumentList(WUrl::WUrl_enum key, QObject *parent)
    : QAbstractListModel(parent), key(key), m_sort(WEnum::SortByNewest)
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
    if (index.row() > rowCount() and index.row() < 0)
        return QVariant();

    auto document = WDocument::get().getDocument(m_list.at(index.row())->id());
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
    return m_list.length();
}

bool WModelDocumentList::containsId(QString id)
{
    return WDocument::get().containsId(key, id);
}

void WModelDocumentList::updateAll()
{
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    endRemoveRows();

    m_list = WDocument::get().getDocumentPointListByKey(key);

    std::sort(m_list.begin(), m_list.end(), [=](const WDocumentBase* f, const WDocumentBase* s){
        switch(m_sort) {
        case WEnum::SortByAZ: return f->name() > s->name();
        case WEnum::SortByZA: return f->name() < s->name();
        case WEnum::SortByNewest: return f->dateCreated() > s->dateCreated();
        case WEnum::SortByOldest: return f->dateCreated() < s->dateCreated();
        default:;
        }
        return false;
    });

    beginInsertRows(QModelIndex(), 0, rowCount() - 1);
    endInsertRows();

    emit dataChanged(this->index(0, 0), this->index(rowCount() - 1, 0));
}
