#ifndef VIEW_H
#define VIEW_H

#include <QtGui/QGuiApplication>
#include <QtCore/QEvent>
#include <QtQuick/QQuickView>

/*!
 * \brief The View class
 * \details Клас отвечает за роботу с интерфейсом приложения и связи его с остальными модулями.
 * \warning Родительский клас для всего проэкта, его удаление приведет к краху приложения.
 */
class WView : public QQuickView
{
    Q_OBJECT
public:
    explicit WView();

    void load(const QUrl& url);

public slots:
    bool barcode_mode();

signals:

protected:
    bool event(QEvent *event);

private:
    /*! \brief isLoad - загружен ли интерфейс или нет.*/
    bool isLoad;
};

#endif // VIEW_H
