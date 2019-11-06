#include "view/wView.h"

WView::WView() : isLoad(false)
{
    resize(370, 550);
}

/*!
 * \brief View::load - производит загрузку интерфейса, если он еще не загружен.
 */
void WView::load(const QUrl& url)
{
    if (isLoad)
        return;

    setSource(url);
#ifndef WQ_OS_ANDROID
    this->resize(350, 550);
#endif
    this->show();
    isLoad = true;
}

/*!
 * \brief View::barcode_mode - говорит какой тип ввода ШК используеться.
 * \return При работе с сенсорных экранов возвращает истину, иначе ложь.
 */
bool WView::barcode_mode()
{
#if defined(Q_OS_ANDROID)
    return true;
#elif defined(Q_OS_LINUX)
    return false;
#endif

    return false;
}

/*!
 * \brief View::event - отлавливает все системные события приложения.
 * \details Метод отлавливает нажатия на клавишу назад и блокирует ее использования, так как
 * это приводит к сворачиванию приложения, что усложняет работу.
 * \param event содержит детальную информацию по событию
 * \return Если это не события клавиши Назад , то возвращает тот же обьект что и принимает,
 * для каскадной системы событий.
 */
bool WView::event(QEvent *event)
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
