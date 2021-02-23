#ifndef WURLENUM_H
#define WURLENUM_H

#include <QtCore/QMap>
#include <QtCore/QObject>
#include "wEnum.h"
#include "wclass/wStatic.h"

class WUrlEnum;

class WUrlEnum : public QObject
{
    Q_OBJECT
public:
    explicit WUrlEnum(QObject* parent = nullptr);

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
        Model,            ///< ModelType - можель учета
        Nomenclature,     ///< Номенклатура
        Quality,          ///< Качество
        Storage,          ///< StorageUnit - Единица хранения
        Supplier,         ///< Поставщик
        Transit,          ///< Транзитный товар
        Type,             ///< Тип
        Unit,             ///< Единица чего либо
        Warehouse,        ///< Склад

        // error url
        ___ = 0xBFFF, ///< Ошибка, если не найден ключ
    }; Q_ENUM(WUrl_enum)

    // non static method
    WUrl_enum p_fromString(QString name, WEnum::Version version_ = WEnum::Version_1_0);
    QString    p_toString(WUrl_enum key, WEnum::Version version_ = WEnum::Version_1_0);
    bool p_contains(WUrl_enum key);
    WUrlEnum::WUrl_enum p_errorKey();

private:
    struct WUrlSingle {
        WUrlEnum::WUrl_enum key;
        QString name;
        WEnum::Version version;
    };

    QList <WUrlSingle> m_list;
};

#endif // WURL_H
