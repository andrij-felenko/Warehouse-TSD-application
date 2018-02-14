#ifndef WURL_H
#define WURL_H

#include <QtCore/QMap>
#include <QtCore/QObject>
#include "wenum.h"
#include "wstatic.h"

class WUrl;
extern WUrl _wurl;

class WUrl : public QObject
{
public:
    explicit WUrl(QObject* parent = nullptr);

    enum WUrl_enum {
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
        Cache,        ///< Кэш
        Line,         ///< Строка
        List,         ///< Список
        New,          ///< Новый элемент

        // other -----------------------------------------------------------------------------------
        Barcode = 0xB300, ///< Штрихкод
        Cell,             ///< Ячейка
        Consignment,      ///< Партия или серия
        Container,        ///< Контейнер
        Department,       ///< Отдел
        Document,         ///< Документ
        Employee,         ///< Работник
        Error,            ///< Ошибка
        Icon,             ///< Иконка
        Id,               ///< Идентификатор
        Image,            ///< Изображение
        Info,             ///< Информация
        Nomenclature,     ///< Номенклатура
        Quality,          ///< Качество
        Storage,          ///< StorageUnit - Единица хранения
        Transit,          ///< Транзитный товар
        Unit,             ///< Единица чего либо

        // error url
        ___ = 0xBFFF, ///< Ошибка, если не найден ключ
    }; Q_ENUMS(WUrl_enum)

    // static variable
    static WEnum::Version version () { return     WEnum::Version_0_1; }
    static WUrl_enum      errorKey() { return WUrl_enum::___;         }

    // static convert method
    static WUrl_enum fromString(QString name, WEnum::Version version_ = version());
    static QString    toString(WUrl_enum key, WEnum::Version version_ = version());

    // non static method
    WUrl_enum p_fromString(QString name, WEnum::Version version_ = version());
    QString    p_toString(WUrl_enum key, WEnum::Version version_ = version());

public slots:
    static QString toString(int key);
    static QString compareUrl(std::initializer_list <WUrl_enum> list, WEnum::Version version_ = version());
    static QString compareUrl(QList <int> list, WEnum::Version version_ = version());
    static QList <WUrl_enum> compareUrlList(std::initializer_list<WUrl_enum> list);
    static QList <WUrl_enum> disunite(const QString& url, WEnum::Version version_ = version());
    static bool isEqual(QList <WUrl_enum> url, std::initializer_list <WUrl_enum> list);

private:
    struct WUrl_single {
        WUrl_enum key;
        QString name;
        WEnum::Version version;
    };
    QList <WUrl_single> m_list;
};

#endif // WURL_H
