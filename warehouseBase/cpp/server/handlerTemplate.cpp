#include "handlerTemplate.h"

HandlerTemplate::HandlerTemplate(QObject *parent) : QObject(parent)
{
//    registrate("fdd", &getUserList);
}

bool HandlerTemplate::registrate(QString key, fp function){
    m_list.push_back({ key, function });
}
