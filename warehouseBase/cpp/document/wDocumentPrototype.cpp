#include "wDocumentPrototype.h"
#include "wSingleton.h"
#include "server/wRequestGenerate.h"

WDocumentPrototype::WDocumentPrototype(QObject *parent) : QObject(parent)
{
    m_empty = new WDocumentBase(WUrl::WUrl_enum::___, this);
}

void WDocumentPrototype::updateDocumentList(WJsonTemplate* json, WUrl::WUrl_enum key)
{
    int i(0);
    QJsonArray array(json->json().toArray());
    for (auto it : m_list){
        if (it.key == key){
            bool isFound(false);
            for (auto subIt : array)
                if (WJson::contains(subIt, WJson::Id))
                    if (it.document->id() == WJson::get(subIt, WJson::Id).toString()){
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
        if (WJson::contains(it, WJson::Id))
            if (not containsId(key, WJson::get(it, WJson::Id).toString())){
                auto document = new WDocumentBase(key, this);
                document->writeHeader(it);
                updateDocumentVocabulary(document);
                m_list.push_back(DocItem { key, document });
                QObject::connect(document, &WDocumentBase::documentLineUpdate,
                                 this, &WDocumentPrototype::updateDocumentVocabulary);
            }

    emit documentListUpdate(key);
}

WDocumentBase* WDocumentPrototype::getDocument(QString id, WUrl::WUrl_enum key) const
{
    for (auto it : m_list)
        if ((key == WUrl::___ and it.document->id() == id) or key == it.key)
            return it.document;
    return nullptr;
}

WDocumentBase* WDocumentPrototype::getDocument(WUrl::WUrl_enum key, int position) const
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

int WDocumentPrototype::getDocumentLengthByKey(WUrl::WUrl_enum key) const
{
    int length(0);
    for (auto it : m_list)
        if (it.key == key)
            length++;
    return length;
}

bool WDocumentPrototype::containsId(WUrl::WUrl_enum key, QString id) const
{
    for (auto it : m_list)
        if (it.key == key)
            if (it.document->id() == id)
                return true;
    return false;
}

void WDocumentPrototype::requestDocumentList(int key)
{
    WUrl::WUrl_enum urlKey = static_cast <WUrl::WUrl_enum> (key);
    if (not WUrl::contains(urlKey)){
        WMessage::get().setErrorMessage(QObject::tr("Не удалось найти ключ в списке url: ") + QString::number(key));
        return;
    }
    WServer::get().request(WUrl::compareUrl({ WUrl::Get, urlKey, WUrl::Document, WUrl::List }),
                           QObject::tr("Запрос списка документов."), WRequestGenerate::empty());
}

void WDocumentPrototype::updateDocumentVocabulary(WDocumentBase* document)
{
    WCache::get().pushCacheToQueque(WUrl::Cell,         document->getCacheList(WJson::Cell_id));
    WCache::get().pushCacheToQueque(WUrl::Consignment,  document->getCacheList(WJson::Consignment_id));
    WCache::get().pushCacheToQueque(WUrl::Container,    document->getCacheList(WJson::Container_id));
    WCache::get().pushCacheToQueque(WUrl::Nomenclature, document->getCacheList(WJson::Nomenclature_id));
}
