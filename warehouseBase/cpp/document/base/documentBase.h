#ifndef DOCUMENTBASE_H
#define DOCUMENTBASE_H

#include <QtCore/QObject>
#include <QtCore/QVariantMap>
#include "documentHeader.h"
#include "document/line/lineActual.h"
#include "server/wjsonTemplate.h"

class DocumentBase : public DocumentHeader
{
    Q_OBJECT
    Q_PROPERTY(LineActual* currentActual READ currentActual)
    Q_PROPERTY(LinePlan*   currentPlan   READ currentPlan)

public:
    explicit DocumentBase(WUrl::WUrl_enum documentKey = WUrl::___, QObject *parent = nullptr);

    void writeHeader(QJsonValue value);
    void writeLines(QJsonValue value);

    LineActual* currentActual() const { return m_currentActual; }
    LinePlan*   currentPlan()   const { return m_currentPlan; }

    void acceptedUpdateLine(WJsonTemplate* json);
    void acceptedSetLine(WJsonTemplate* json);
    void acceptedRemoveLine(WJsonTemplate* json);
    void acceptedReserveContainer(WJsonTemplate* json, bool sender);
    void acceptedUnreserveContainer(WJsonTemplate* json, bool sender);

public slots:
    void chooseLine(QString id);
    bool chooseNextLine(QVariantMap map);
    void createLine(QVariantMap map);
    void saveLine(QObject* senderObj, QString funcName);
    void removeLine(QObject* senderObj, QString funcName);

signals:

protected:
    QList <LineActual*> actual;
    QList <LinePlan*> plan;
    LineActual* m_currentActual;
    LinePlan* m_currentPlan;

private:
    WUrl::WUrl_enum documentKey;
};

#endif // DOCUMENTBASE_H
