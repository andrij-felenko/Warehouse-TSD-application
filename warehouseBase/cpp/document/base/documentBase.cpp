#include "documentBase.h"

DocumentBase::DocumentBase(WUrl::WUrl_enum documentKey, QObject *parent)
    : DocumentHeader(parent), documentKey(documentKey)
{
    m_currentActual = new LineActual(this);
    m_currentPlan = new LinePlan(this);
}

void DocumentBase::acceptedSaveLine(WJsonTemplate* json)
{
    //
}

void DocumentBase::acceptedCreateLine(WJsonTemplate* json)
{
    //
}

void DocumentBase::acceptedRemoveLine(WJsonTemplate* json)
{
    //
}

void DocumentBase::chooseLine(QString id, QVariantMap map)
{
    //
}

void DocumentBase::chooseNextLine(QVariantMap map)
{
    //
}

void DocumentBase::createLine(QVariantMap map)
{
    //
}

void DocumentBase::saveLine()
{
    //
}

void DocumentBase::removeLine()
{
    //
}
