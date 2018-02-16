#include "documentPrototype.h"

DocumentPrototype::DocumentPrototype(QObject *parent) : QObject(parent)
{
    //
}

void DocumentPrototype::updateDocumentList(WJsonTemplate* json, WUrl::WUrl_enum key)
{
    for (auto it : m_list)
        if (it.key == key){
            bool isFound(false);
            for (auto subIt : json->json().toArray())
                if (WJson::contains(subIt, WJson::Id))
                    if (it.document->id() == WJson::get(subIt, WJson::Id).toString()){
                        // FIXME write header data to document
                        isFound = true;
                        break;
                    }
            if (not isFound){
                it.document->deleteLater();
                // FIXME cant remove, non copy
//                m_list.removeOne(it);
            }
        }
}

DocumentBase* DocumentPrototype::getDocument(QString id, WUrl::WUrl_enum key) const
{
    for (auto it : m_list)
        if (key == WUrl::___ or key == it.key)
            return it.document;
    return nullptr;
}
