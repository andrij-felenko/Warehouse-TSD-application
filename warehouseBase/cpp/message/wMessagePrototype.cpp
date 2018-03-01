#include "wMessagePrototype.h"
#include "QDebug"

WMessagePrototype::WMessagePrototype(QObject *parent) : QObject(parent)
{
    m_current = new WMessageSingle("", WEnum::Msg_complete, WEnum::Priority_low, 0, this);
    setShowingPriority(WEnum::Priority_high | WEnum::Priority_low | WEnum::Priority_middle
                       | WEnum::Priority_middle_above | WEnum::Priority_middle_bellow);
}

WMessageSingle* WMessagePrototype::current() const
{
    return m_current;
}

QString WMessagePrototype::setMessage(QString text, WEnum::Msg_type msgType, WEnum::Priority priority, int time_ms)
{
    qDebug() << "Message: " << text;
    auto msg = new WMessageSingle(text, msgType, priority, time_ms, this);
    m_list.push_back(msg);
    update();

    QObject::connect(msg, &WMessageSingle::removeMessage,
                     this, static_cast <bool (WMessagePrototype::*)(QString)> (&WMessagePrototype::removeMessage));
    return msg->id();
}

QString WMessagePrototype::setWarningMessage(QString text, WEnum::Priority priority)
{
    return setMessage(text, WEnum::Msg_warning, priority);
}

QString WMessagePrototype::setInformationMessage(QString text)
{
    return setMessage(text, WEnum::Msg_progress, WEnum::Priority_low, 1500);
}

QString WMessagePrototype::setErrorMessage(QString text)
{
    return setMessage(text, WEnum::Msg_error, WEnum::Priority_high);
}

QString WMessagePrototype::setWarningMessage(QString text, int priority)
{
    return setWarningMessage(text, static_cast <WEnum::Priority> (priority));
}

bool WMessagePrototype::removeMessage(QString msg_id_text)
{
    for (auto it : m_list)
        if (it->id() == msg_id_text){
            auto ret = m_list.removeOne(it);
            it->deleteLater();
            update();
            return ret;
        }
    for (auto it : m_list)
        if (it->text() == msg_id_text){
            auto ret = m_list.removeOne(it);
            it->deleteLater();
            update();
            return ret;
        }
    return false;
}

void WMessagePrototype::setShowingPriority(int priority)
{
    m_showPriority.clear();

    if ((priority & WEnum::Priority_high) == WEnum::Priority_high)
        m_showPriority.push_back(WEnum::Priority_high);

    if ((priority & WEnum::Priority_middle_above) == WEnum::Priority_middle_above)
        m_showPriority.push_back(WEnum::Priority_middle_above);

    if ((priority & WEnum::Priority_middle) == WEnum::Priority_middle)
        m_showPriority.push_back(WEnum::Priority_middle);

    if ((priority & WEnum::Priority_middle_bellow) == WEnum::Priority_middle_bellow)
        m_showPriority.push_back(WEnum::Priority_middle_bellow);

    if ((priority & WEnum::Priority_low) == WEnum::Priority_low)
        m_showPriority.push_back(WEnum::Priority_low);

    update();
}

void WMessagePrototype::setMessage(QString str, int msgType, int priority, int time_ms)
{
    setMessage(str, static_cast <WEnum::Msg_type> (msgType),
               static_cast <WEnum::Priority> (priority), time_ms);
}

void WMessagePrototype::removeMessage()
{
    removeMessage(m_current->id());
}

void WMessagePrototype::update()
{
    WMessageSingle* currentMsg = new WMessageSingle;
    for (auto it : m_list)
        if (it->status() != WEnum::Msg_close)
            if (currentMsg->priority() <= it->priority())
                if (m_showPriority.contains(it->priority()))
                    if (currentMsg->dateTimeCreate() >= it->dateTimeCreate())
                        if (m_current != it)
                            currentMsg->copy(it);

    m_current->copy(currentMsg);
    currentMsg->deleteLater();
}
