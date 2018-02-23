#ifndef WMESSAGESINGLE_H
#define WMESSAGESINGLE_H

#include <QtCore/QTimer>
#include "enum/wEnum.h"
#include "enum/wStatic.h"

class WMessageSingle : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id   READ id   NOTIFY idChanged)
    Q_PROPERTY(QString text READ text NOTIFY textChanged)
    Q_PROPERTY(WEnum::Priority priority READ priority       NOTIFY priorityChanged)
    Q_PROPERTY(WEnum::Msg_status status READ status         NOTIFY statusChanged)
    Q_PROPERTY(WEnum::Msg_type type     READ type           NOTIFY typeChanged)
    Q_PROPERTY(QDateTime dateTimeCreate READ dateTimeCreate NOTIFY dateTimeCreateChanged)

public:
    explicit WMessageSingle(QString text = QString(""), WEnum::Msg_type type = WEnum::Msg_progress,
                           WEnum::Priority priority = WEnum::Priority_low, int time_ms = 0,
                           QObject *parent = nullptr)
        : QObject(parent),
          m_text(text), m_id(WStatic::guidCreate()), m_priority(priority), m_status(WEnum::Msg_waiting),
          m_type(type), m_time_ms(time_ms), m_dateTimeCreate(QDateTime::currentDateTime())
    {
        if (m_time_ms > 100)
            QTimer::singleShot(m_time_ms, [=]() { emit removeMessage(m_id); });
        QObject::connect(this, &WMessageSingle::dateTimeCreateChanged, [=]() { emit updateMessage(m_id); });
        QObject::connect(this, &WMessageSingle::idChanged,             [=]() { emit updateMessage(m_id); });
        QObject::connect(this, &WMessageSingle::priorityChanged,       [=]() { emit updateMessage(m_id); });
        QObject::connect(this, &WMessageSingle::textChanged,           [=]() { emit updateMessage(m_id); });
        QObject::connect(this, &WMessageSingle::statusChanged,         [=]() { emit updateMessage(m_id); });
    }

    QString id()   { return m_id; }
    QString text() { return m_text; }
    WEnum::Priority priority() { return m_priority; }
    WEnum::Msg_status status() { return m_status; }
    WEnum::Msg_type type()     { return m_type; }
    QDateTime dateTimeCreate() { return m_dateTimeCreate; }

    void setStatus(WEnum::Msg_status status){ m_status = status; }

    void copy(WMessageSingle* obj)
    {
        setId(obj->id());
        setDateTimeCreate(obj->dateTimeCreate());
        setPriority(obj->priority());
        setStatus(obj->status());
        setText(obj->text());
    }

public slots:
    void setId(QString id)
    {
        if (m_id != id){
            m_id = id;
            emit idChanged(m_id);
        }
    }

    void setPriority(WEnum::Priority priority)
    {
        if (m_priority != priority){
            m_priority = priority;
            emit priorityChanged(m_priority);
        }
    }

    void setType(WEnum::Msg_type type)
    {
        if (m_type != type){
            m_type = type;
            emit typeChanged(m_type);
        }
    }

    void setDateTimeCreate(QDateTime dateTimeCreate)
    {
        if (m_dateTimeCreate != dateTimeCreate){
            m_dateTimeCreate = dateTimeCreate;
            emit dateTimeCreateChanged(m_dateTimeCreate);
        }
    }

    void setText(QString text)
    {
        if (m_text != text){
            m_text = text;
            emit textChanged(m_text);
        }
    }

signals:
    void removeMessage(QString msgId);
    void updateMessage(QString msgId);

    void idChanged(QString id);
    void priorityChanged(WEnum::Priority priority);
    void statusChanged(WEnum::Msg_status status);
    void typeChanged(WEnum::Msg_type type);
    void dateTimeCreateChanged(QDateTime dateTimeCreate);
    void textChanged(QString text);

private:
    QString m_text;
    QString m_id;
    WEnum::Priority m_priority;
    WEnum::Msg_status m_status;
    WEnum::Msg_type m_type;
    int m_time_ms;
    QDateTime m_dateTimeCreate;
};

#endif // MESSAGESINGLE_H
