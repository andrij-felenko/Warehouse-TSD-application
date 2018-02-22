#ifndef MESSAGEPROTOTYPE_H
#define MESSAGEPROTOTYPE_H

#include <QtCore/QObject>
#include "enum/wenum.h"
#include "wMessageSingle.h"

class WMessagePrototype : public QObject
{
    Q_OBJECT
    Q_PROPERTY(WMessageSingle* MsgCurrent READ MsgCurrent NOTIFY MsgCurrentChanged)

public:
    explicit WMessagePrototype(QObject *parent = nullptr);

    WMessageSingle* MsgCurrent() const;
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
    void MsgCurrentChanged(WMessageSingle* MsgCurrent);

private:
    QList <WMessageSingle*> m_list;
    QList <WEnum::Priority> m_showPriority;
    WMessageSingle* m_MsgCurrent;
    WMessageSingle* m_MsgEmpty;

    void update();
};

#endif // MESSAGEPROTOTYPE_H
