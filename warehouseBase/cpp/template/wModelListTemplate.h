#ifndef WMODELLISTTEMPLATE_H
#define WMODELLISTTEMPLATE_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QObject>
#include <QtCore/QSettings>
#include <QtCore/QString>
#include "enum/wEnum.h"

class WModelListTemplate : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit WModelListTemplate(QString name, QObject *parent = nullptr);

    virtual QHash <int, QByteArray> roleNames() const override final;
    virtual QString name() const final;
    virtual WEnum::Sort sort() final;
    virtual void p_setSort(WEnum::Sort sort_) final;

public slots:
    virtual void update() = 0;
    virtual void setSort(int sort_) final;
    virtual QString settingModelPath(QString nameValue) final;

protected:
    QSettings m_setting;

private:
    QString m_name;
};

#endif // WMODELLISTTEMPLATE_H
