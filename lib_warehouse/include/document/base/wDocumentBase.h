#ifndef WDOCUMENTBASE_H
#define WDOCUMENTBASE_H

#include <QtCore/QObject>
#include <QtCore/QVariantMap>
#include "wDocumentHeader.h"
#include "document/line/wLineActual.h"
#include "wclass/wJson.h"
#include "enum/wUrlEnum.h"

class WDocumentBase : public WDocumentHeader
{
    Q_OBJECT
    Q_PROPERTY(WLineActual* currentActual READ currentActual CONSTANT)
    Q_PROPERTY(WLinePlan*   currentPlan   READ currentPlan   CONSTANT)

public:
    explicit WDocumentBase(WUrlEnum::WUrl_enum documentKey = WUrlEnum::___, QObject *parent = nullptr);

    void writeHeader(QJsonValue value);
    void writeLines(QJsonValue value);

    WLineActual* currentActual() const { return m_currentActual; }
    WLinePlan*   currentPlan()   const { return m_currentPlan; }

    void acceptedUpdateLine(WJson* json);
    void acceptedSetLine(WJson* json);
    void acceptedRemoveLine(WJson* json);
    void acceptedReserveContainer(WJson* json, bool sender);
    void acceptedUnreserveContainer(WJson* json, bool sender);

    QStringList getCacheList(WJsonEnum::WJson_enum type);
    QStringList getCacheListByParameters(WEnum::LineType type, WJsonEnum::WJson_enum key,
                                         QVariantMap map = QVariantMap());
    int getQuantity(WEnum::LineType type, QVariantMap map);

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
    WUrlEnum::WUrl_enum documentKey;
};

#endif // DOCUMENTBASE_H
