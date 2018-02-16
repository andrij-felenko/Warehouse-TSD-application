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

    LineActual* currentActual() const { return m_currentActual; }
    LinePlan*   currentPlan()   const { return m_currentPlan; }

    void acceptedSaveLine  (WJsonTemplate* json);
    void acceptedCreateLine(WJsonTemplate* json);
    void acceptedRemoveLine(WJsonTemplate* json);

public slots:
    void chooseLine(QString id, QVariantMap map);
    void chooseNextLine(QVariantMap map);
    void createLine(QVariantMap map);
    void saveLine();
    void removeLine();

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
