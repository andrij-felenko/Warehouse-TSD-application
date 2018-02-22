#include "wCurrentUser.h"
#include "wSingleton.h"

WCurrentUser::WCurrentUser(QObject *parent) : QObject(parent)
{
    m_current = new WEmployeeSingle(this);
}

void WCurrentUser::setUserInput(QString line)
{
    m_current->clear();
    m_current->setName(line);
}

void WCurrentUser::setUserList(QString id)
{
    auto single = WCache::get().employee()->getOne(id);
    if (single == nullptr)
        return;

    m_current->fromJson(single->toJson());
}

bool WCurrentUser::tryAuthorization(QString password)
{
    auto single = WCache::get().employee()->getOne(m_current->id());
    if (single == nullptr){
        WMessage::get().setErrorMessage(QObject::tr("Login not found"));
        return false;
    }
    if (not single->isCoincide(password)){
        WMessage::get().setErrorMessage(QObject::tr("Password incorrect"));
        return false;
    }
    return true;
}
