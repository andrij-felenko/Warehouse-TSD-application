#include "messagePrototype.h"
#include "QDebug"

MessagePrototype::MessagePrototype(QObject *parent) : QObject(parent)
{
    m_MsgEmpty = new MessageSingle("", WEnum::Msg_complete, WEnum::Priority_low, 0, this);
    m_MsgCurrent = m_MsgEmpty;
    setShowingPriority(WEnum::Priority_high | WEnum::Priority_low | WEnum::Priority_middle
                       | WEnum::Priority_middle_above | WEnum::Priority_middle_bellow);
}

MessageSingle*MessagePrototype::MsgCurrent() const
{
    return m_MsgCurrent;
}

QString MessagePrototype::setMessage(QString text, WEnum::Msg_type msgType, WEnum::Priority priority, int time_ms)
{
    qDebug() << "Message: " << text;
    auto msg = new MessageSingle(text, msgType, priority,time_ms, this);
    m_list.push_back(msg);
    update();

    QObject::connect(msg, &MessageSingle::removeMessage,
                     this, static_cast <bool (MessagePrototype::*)(QString)> (&MessagePrototype::removeMessage));
    return msg->id();
}

QString MessagePrototype::setWarningMessage(QString text, WEnum::Priority priority)
{
    return setMessage(text, WEnum::Msg_warning, priority);
}

QString MessagePrototype::setErrorMessage(QString text)
{
    return setMessage(text, WEnum::Msg_error, WEnum::Priority_high);
}

QString MessagePrototype::setWarningMessage(QString text, int priority)
{
    return setWarningMessage(text, static_cast <WEnum::Priority> (priority));
}

bool MessagePrototype::removeMessage(QString msg_id_text)
{
    for (auto it : m_list)
        if (it->id() == msg_id_text){
            auto ret = m_list.removeOne(it);
            update();
            return ret;
        }
    for (auto it : m_list)
        if (it->text() == msg_id_text){
            auto ret = m_list.removeOne(it);
            update();
            return ret;
        }
    return false;
}

void MessagePrototype::setShowingPriority(int priority)
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

void MessagePrototype::setMessage(QString str, int msgType, int priority, int time_ms)
{
    setMessage(str, static_cast <WEnum::Msg_type> (msgType),
               static_cast <WEnum::Priority> (priority), time_ms);
}

void MessagePrototype::removeMessage()
{
    removeMessage(m_MsgCurrent->id());
}

// FIXME
void MessagePrototype::update()
{
    //
}
