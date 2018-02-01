#ifndef CACHELISTOBJECT_H
#define CACHELISTOBJECT_H

#include <QtCore/QObject>

/*!
 * \brief Шаблон для сигнала listUpdate.
 * Класс создан по причине того, что шаблоны не могут напрямую участвовать в создании сигналов.
 */
class CacheListObject : public QObject
{
    Q_OBJECT
public:
    /*!
     * \param parent ссылка на родительский обьект
     */
    CacheListObject(QObject *parent = nullptr)
        : QObject(parent)
    {
        //
    }

signals:
    /*!
     * \brief Оповещение про изменение списка.
     * Вызываеться когда идет любое изменения в списке кэша.
     */
    void listPushed(QStringList idList);
    void listPoped(QStringList idList);
    void listUpdated(QStringList idList);
};

#endif // CACHELISTOBJECT_H
