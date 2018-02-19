#ifndef MODEL_H
#define MODEL_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class ModelApp : public QObject
{
    Q_OBJECT
public:
    explicit ModelApp(QObject *parent = nullptr);

signals:

public slots:
};

#endif // MODEL_H
