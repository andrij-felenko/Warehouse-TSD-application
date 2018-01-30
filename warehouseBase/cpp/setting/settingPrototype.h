#ifndef SETTINGPROTOTYPE_H
#define SETTINGPROTOTYPE_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class SettingPrototype : public QObject
{
    Q_OBJECT
public:
    explicit SettingPrototype(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SETTINGPROTOTYPE_H