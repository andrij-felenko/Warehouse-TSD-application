#include "model/wModelDocumentList.h"
#include "wSingleton.h"

WModelDocumentList::WModelDocumentList(QString name, WUrlEnum::WUrl_enum key, QObject *parent)
    : WModelListTemplate(name, parent), key(key)
{
    QObject::connect(WDocument::registrate(), &WDocumentPrototype::documentListUpdate,
                     this, [=](WUrlEnum::WUrl_enum key)
    {
        if (key == this->key)
            update();
    });
    p_setSort(WEnum::SortByNewest);
    update();
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

void WModelDocumentList::update()
{
    beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
    endRemoveRows();

    m_list = WDocument::get().getDocumentPointListByKey(key);

    std::sort(m_list.begin(), m_list.end(), [=](const WDocumentBase* f, const WDocumentBase* s){
        switch(sort()) {
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
