#ifndef URL_H
#define URL_H

#include <QtCore/QMap>
#include <QtCore/QObject>
#include "enum.h"
#include "static.h"

class Url;
extern Url _url;

class Url : public QObject
{
public:
    explicit Url(QObject* parent = nullptr);

    enum Url_enum {
        // first word to request -------------------------------------------------------------------
        Get = 0xB000, ///< Запрос на получение
        Set,          ///< Отправка информации на сервер
        Accept,       ///< Принять
        Remove,       ///< Удалить
        Update,       ///< Внесение изменений
        Reserve,      ///< Резервирование
        Unreserve,    ///< Отмена резервирования

        // type of document ------------------------------------------------------------------------
        Allotted = 0xB100, ///< Перемещение
        Delivery,          ///< Доставка
        Inventory,         ///< Инвентаризация
        Picking,           ///< Отбор
        Purchase,          ///< Отгрузка
        Receiving,         ///< Приемка

        // optional words --------------------------------------------------------------------------
        All = 0xB200, ///< Всё
        By,           ///< Поиск по чему то *
        Line,         ///< Строка
        List,         ///< Список
        New,          ///< Новый элемент

        // other -----------------------------------------------------------------------------------
        Cell = 0xB300, ///< Ячейка
        Consignment,   ///< Партия или серия
        Container,     ///< Контейнер
        Department,    ///< Отдел
        Document,      ///< Документ
        Employee,      ///< Работник
        Error,         ///< Ошибка
        Icon,          ///< Иконка
        Id,            ///< Идентификатор
        Image,         ///< Изображение
        Info,          ///< Информация
        Transit,       ///< Транзитный товар

        // error url
        ___ = 0xBFFF, ///< Ошибка, если не найден ключ
    }; Q_ENUMS(Url_enum)

    // static variable
    static Enum::Version version () { return     Enum::Version_0_1; }
    static Url_enum      errorKey() { return Url_enum::___;         }

    // static convert method
    static Url_enum fromString(QString name, Enum::Version version_ = version());
    static QString    toString(Url_enum key, Enum::Version version_ = version());

    // non static method
    Url_enum p_fromString(QString name, Enum::Version version_ = version());
    QString    p_toString(Url_enum key, Enum::Version version_ = version());

public slots:
    static QString toString(int key);
    static QString compareUrl(std::initializer_list <Url_enum> list, Enum::Version version_ = version());
    static QList <Url_enum> disunite(const QString& url, Enum::Version version_ = version());

private:
    struct Url_single {
        Url_enum key;
        QString name;
        Enum::Version version;
    };
    QList <Url_single> m_list;
};

#endif // URL_H
