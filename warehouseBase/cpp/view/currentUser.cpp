#include "currentUser.h"
#include "singleton.h"

CurrentUser::CurrentUser(QObject *parent) : QObject(parent)
{
    m_current = new EmployeeSingle(this);
}

void CurrentUser::setUserInput(QString line)
{
    m_current->clear();
    m_current->setName(line);
}

void CurrentUser::setUserList(QString id)
{
    auto single = Cache::get().employee()->getOne(id);
    if (single == nullptr)
        return;

    m_current->fromJson(single->toJson());
}
