#ifndef WDOCUMENTBASE_H
#define WDOCUMENTBASE_H

#include <QtCore/QObject>
#include <QtCore/QVariantMap>
#include "wDocumentHeader.h"
#include "document/line/wLineActual.h"
#include "server/wJsonTemplate.h"

class WDocumentBase : public WDocumentHeader
{
    Q_OBJECT
    Q_PROPERTY(WLineActual* currentActual READ currentActual)
    Q_PROPERTY(WLinePlan*   currentPlan   READ currentPlan)

public:
    explicit WDocumentBase(WUrl::WUrl_enum documentKey = WUrl::___, QObject *parent = nullptr);

    void writeHeader(QJsonValue value);
    void writeLines(QJsonValue value);

    WLineActual* currentActual() const { return m_currentActual; }
    WLinePlan*   currentPlan()   const { return m_currentPlan; }

    void acceptedUpdateLine(WJsonTemplate* json);
    void acceptedSetLine(WJsonTemplate* json);
    void acceptedRemoveLine(WJsonTemplate* json);
    void acceptedReserveContainer(WJsonTemplate* json, bool sender);
    void acceptedUnreserveContainer(WJsonTemplate* json, bool sender);

    QStringList getCacheList(WJson::WJson_enum type);

public slots:
    void chooseLine(QString id);
    bool chooseNextLine(QVariantMap map);
    void createLine(QVariantMap map);
    void saveLine(QObject* senderObj, QString funcName);
    void removeLine(QObject* senderObj, QString funcName);

signals:
    void documentLineUpdate(WDocumentBase* document);

protected:
    QList <WLineActual*> actual;
    QList <WLinePlan*> plan;
    WLineActual* m_currentActual;
    WLinePlan* m_currentPlan;

private:
    WUrl::WUrl_enum documentKey;
};

#endif // DOCUMENTBASE_H
