#include "wDocumentPrototype.h"

WDocumentPrototype::WDocumentPrototype(QObject *parent) : QObject(parent)
{
    m_empty = new WDocumentBase(WUrl::WUrl_enum::___, this);
}

void WDocumentPrototype::updateDocumentList(WJsonTemplate* json, WUrl::WUrl_enum key)
{
    qDebug() << WUrl::toString(key) << key << m_list.count();
    int i(0);
    QJsonArray array(json->json().toArray());
    for (auto it : m_list){
        if (it.key == key){
            bool isFound(false);
            for (auto subIt : array)
                if (WJson::contains(subIt, WJson::Id))
                    if (it.document->id() == WJson::get(subIt, WJson::Id).toString()){
                        it.document->writeHeader(subIt);
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
                m_list.push_back(DocItem { key, document });
            }
    qDebug() << WUrl::toString(key) << key << m_list.count();
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
