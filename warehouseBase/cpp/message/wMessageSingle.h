#ifndef MESSAGESINGLE_H
#define MESSAGESINGLE_H

#include <QtCore/QTimer>
#include "enum/wenum.h"
#include "enum/wstatic.h"

class WMessageSingle : public QObject
{
    Q_OBJECT
public:
    explicit WMessageSingle(QString text, WEnum::Msg_type type,
                           WEnum::Priority priority, int time_ms,
                           QObject *parent = nullptr)
        : QObject(parent),
          m_text(text), m_id(WStatic::guidCreate()),
          m_priority(priority), m_status(WEnum::Msg_waiting), m_type(type),
          m_time_ms(time_ms), m_dTime_create(QDateTime::currentDateTime())
    {
        if (m_time_ms > 100)
            QTimer::singleShot(m_time_ms, [=]() { emit removeMessage(m_id); });
    }

    QString id()   { return m_id; }
    QString text() { return m_text; }
    WEnum::Priority priority() { return m_priority; }
    WEnum::Msg_status status() { return m_status; }
    WEnum::Msg_type type()     { return m_type; }

    void setStatus(WEnum::Msg_status status){ m_status = status; }

signals:
    void removeMessage(QString msgId);
    void updateMessage(QString msgId);

private:
    QString m_text;
    QString m_id;
    WEnum::Priority m_priority;
    WEnum::Msg_status m_status;
    WEnum::Msg_type m_type;
    int m_time_ms;
    QDateTime m_dTime_create;
};

#endif // MESSAGESINGLE_H
