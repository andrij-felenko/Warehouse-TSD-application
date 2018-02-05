#ifndef MESSAGEPROTOTYPE_H
#define MESSAGEPROTOTYPE_H

#include <QtCore/QObject>
#include "enum/wenum.h"
#include "messageSingle.h"

class MessagePrototype : public QObject
{
    Q_OBJECT
    Q_PROPERTY(MessageSingle* MsgCurrent READ MsgCurrent NOTIFY MsgCurrentChanged)

public:
    explicit MessagePrototype(QObject *parent = nullptr);

    MessageSingle* MsgCurrent() const;
    QString setMessage(QString text, WEnum::Msg_type msgType,
                     WEnum::Priority priority, int time_ms = 0);
    QString setWarningMessage(QString text, WEnum::Priority priority);
    bool removeMessage(QString msg_id_text);
    void setShowingPriority(int priority);

public slots:
    QString setErrorMessage(QString text);
    QString setWarningMessage(QString text, int priority);
    void setMessage(QString str, int msgType, int priority, int time_ms = 0);
    void removeMessage();

signals:
    void MsgCurrentChanged(MessageSingle* MsgCurrent);

private:
    QList <MessageSingle*> m_list;
    QList <WEnum::Priority> m_showPriority;
    MessageSingle* m_MsgCurrent;
    MessageSingle* m_MsgEmpty;

    void update();
};

#endif // MESSAGEPROTOTYPE_H
