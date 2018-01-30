#include "view.h"

View::View() : isLoad(false)
{
    //
}

/*!
 * \brief View::quit - закрывает приложение
 * \details Метод вызываеться с qml части, и вызывает системный вызов. \code qApp->quit(); \endcode
 */
void View::quit()
{
    qApp->quit();
}

/*!
 * \brief View::load - производит загрузку интерфейса, если он еще не загружен.
 */
void View::load()
{
    if (isLoad)
        return;

    this->setSource(QUrl("qrc:/qml/qml/main.qml"));
#ifndef Q_OS_ANDROID
    this->resize(350, 550);
#endif
    this->show();
    isLoad = true;
}

/*!
 * \brief View::barcode_mode - говорит какой тип ввода ШК используеться.
 * \return При работе с сенсорных экранов возвращает истину, иначе ложь.
 */
bool View::barcode_mode()
{
#ifdef Q_OS_ANDROID
    return true;
#endif
#ifdef Q_OS_LINUX
    return false;
#endif
}

/*!
 * \brief View::event - отлавливает все системные события приложения.
 * \details Метод отлавливает нажатия на клавишу назад и блокирует ее использования, так как
 * это приводит к сворачиванию приложения, что усложняет работу.
 * \param event содержит детальную информацию по событию
 * \return Если это не события клавиши Назад , то возвращает тот же обьект что и принимает,
 * для каскадной системы событий.
 */
bool View::event(QEvent *event)
{
    if (event->type() == QEvent::Close)
       event->accept();
   else if (event->type() == QEvent::KeyPress){
       QKeyEvent *k = static_cast <QKeyEvent*> (event);
       if (k->key() == Qt::Key_Back or k->key() == Qt::Key_Menu or k->key() == Qt::Key_Home)
           return true;
   }
   else if (event->type() == QEvent::KeyRelease){
       QKeyEvent *k = static_cast <QKeyEvent*> (event);
       if (k->key() == Qt::Key_Back or k->key() == Qt::Key_Menu or k->key() == Qt::Key_Home){
           return true;
       }
   }

    return QQuickView::event(event);
}
