#include "wDocumentPrototype.h"
#include "wSingleton.h"
#include "server/wRequestGenerate.h"

WDocumentPrototype::WDocumentPrototype(QObject *parent) : QObject(parent)
{
    m_empty = new WDocumentBase(WUrlEnum::WUrl_enum::___, this);
}

void WDocumentPrototype::updateDocumentList(WJson* json, WUrlEnum::WUrl_enum key)
{
    int i(0);
    QJsonArray array(json->json().toArray());
    for (auto it : m_list){
        if (it.key == key){
            bool isFound(false);
            for (auto subIt : array)
                if (WJsonConverter::contains(subIt, WJsonEnum::Id))
                    if (it.document->id() == WJsonConverter::get(subIt, WJsonEnum::Id).toString()){
                        it.document->writeHeader(subIt);
                        updateDocumentVocabulary(it.document);
                        isFound = true;
                        break;
                    }
            if (not isFound){
                it.document->deleteLater();
                m_list.removeAt(i);
                i--;
            }
        }
        i++;
    }
    for (auto it : array)
        if (WJsonConverter::contains(it, WJsonEnum::Id))
            if (not containsId(key, WJsonConverter::get(it, WJsonEnum::Id).toString())){
                auto document = new WDocumentBase(key, this);
                document->writeHeader(it);
                updateDocumentVocabulary(document);
                m_list.push_back(DocItem { key, document });
                QObject::connect(document, &WDocumentBase::documentLineUpdate,
                                 this, &WDocumentPrototype::updateDocumentVocabulary);
            }

    emit documentListUpdate(key);
}

WDocumentBase* WDocumentPrototype::getDocument(QString id, WUrlEnum::WUrl_enum key) const
{
    for (auto it : m_list)
        if ((key == WUrlEnum::___ and it.document->id() == id) or key == it.key)
            return it.document;
    return nullptr;
}

WDocumentBase* WDocumentPrototype::getDocument(WUrlEnum::WUrl_enum key, int position) const
{
    if (getDocumentLengthByKey(key) <= position)
        return m_empty;

    int current(0);
    for (auto it : m_list)
        if (it.key == key){
            if (current == position)
                return it.document;
            current++;
        }

    return m_empty;
}

QStringList WDocumentPrototype::getDocumentListByKey(WUrlEnum::WUrl_enum key) const
{
    QStringList list;
    for (auto it : m_list)
        if (it.key == key)
            list.push_back(it.document->id());
    return list;
}

QMultiMap <WEnum::DocumentStatus, QString> WDocumentPrototype::getDocumentMapByKey(WUrlEnum::WUrl_enum key) const
{
    QMultiMap < WEnum::DocumentStatus, QString> map;
    for (auto it : m_list)
        if (it.key == key)
            map.insert(it.document->status(), it.document->id());
    return map;
}

QList <WDocumentBase*> WDocumentPrototype::getDocumentPointListByKey(WUrlEnum::WUrl_enum key) const
{
    QList <WDocumentBase*> list;
    for (auto it : m_list)
        if (it.key == key)
            list.push_back(it.document);
    return list;
}

int WDocumentPrototype::getDocumentLengthByKey(WUrlEnum::WUrl_enum key) const
{
    int length(0);
    for (auto it : m_list)
        if (it.key == key)
            length++;
    return length;
}

bool WDocumentPrototype::containsId(WUrlEnum::WUrl_enum key, QString id) const
{
    for (auto it : m_list)
        if (it.key == key)
            if (it.document->id() == id)
                return true;
    return false;
}

void WDocumentPrototype::requestDocumentList(int key)
{
    WUrlEnum::WUrl_enum urlKey = static_cast <WUrlEnum::WUrl_enum> (key);
    if (not WUrlConverter::contains(urlKey)){
        WMessage::get().setErrorMessage(QObject::tr("Не удалось найти ключ в списке url: ") + QString::number(key));
        return;
    }
    WServer::get().request(WUrlConverter::compareUrl({ WUrlEnum::Get, urlKey, WUrlEnum::Document, WUrlEnum::List }),
                           QObject::tr("Запрос списка документов."), WRequestGenerate::empty());
}

void WDocumentPrototype::updateDocumentVocabulary(WDocumentBase* document)
{
    WCache::get().pushCacheToQueque(WUrlEnum::Cell,         document->getCacheList(WJsonEnum::Cell_id));
    WCache::get().pushCacheToQueque(WUrlEnum::Consignment,  document->getCacheList(WJsonEnum::Consignment_id));
    WCache::get().pushCacheToQueque(WUrlEnum::Container,    document->getCacheList(WJsonEnum::Container_id));
    WCache::get().pushCacheToQueque(WUrlEnum::Nomenclature, document->getCacheList(WJsonEnum::Nomenclature_id));
}
