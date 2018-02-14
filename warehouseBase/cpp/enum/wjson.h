#ifndef WJSON_H
#define WJSON_H

#include <QtCore/QJsonObject>
#include <QtCore/QList>
#include <QtCore/QObject>

#include "wenum.h"
#include "wstatic.h"

class WJson;
extern WJson _json;

class WJson : public QObject
{
public:
    explicit WJson(QObject* parent = nullptr);

    enum WJson_enum {
        // basic value -----------------------------------------------------------------------------
        Id = 0xA000, ///< Идентификатор
        Barcode,     ///< Штрихкод
        Guid,        ///< Идентификатор (второй вариант)
        Cargo,       ///< Груз, товар
        Key,         ///< Ключ
        Line,        ///< Строка
        List,        ///< Список
        Name,        ///< Наименование
        Parent,      ///< Родительский обьект (применяеться по ситуации)

        // warehouse value -------------------------------------------------------------------------
        // cell
        Cell_id = 0xA100,    ///< Идентфикатор ячейки
        Cell_name,           ///< Название ячейки
        Cell_reason_id,      ///< Идентификатор причины смены ячейки
        Cell_reason_name,    ///< Названия причины смены ячейки
        Cell_reason_comment, ///< Коментарий к смене ячейки
        Cell_sender_id,      ///< Идентификатор ячейки отправителя
        Cell_sender_name,    ///< Наименование ячейки отправителя
        Cell_receiver_id,    ///< Идентификатор ячейки получателя
        Cell_receiver_name,  ///< Наименование ячейки получателя
        // consignment
        Consignment = 0xA110, ///< Просто обозначение партии
        Consignment_id,       ///< Идентификатор партии
        Consignment_name,     ///< Наименование партии
        // container
        Container_id_list = 0xA120, ///< Список идентификаторов контейнеров
        Container_id,               ///< Идентификатор контейнера
        Container_name,             ///< Наименование контейнера
        Container_reason_id,        ///< Идентификатор причины смены контейнера
        Container_reason_name,      ///< Название причины смены контейнера
        Container_reason_comment,   ///< Коментарий к смене контейнера
        Container_sender_id,        ///< Идентификатор контейнера отправителя
        Container_sender_name,      ///< Наименование контейнера отправителя
        Container_receiver_id,      ///< Идентификатор контейнера получателя
        Container_receiver_name,    ///< Наименование контейнера получателя
        // dictionary
        ModelTypeId = 0xA130, ///< Идентификатор модели учета
        // nomenclature
        Nomenclature_id = 0xA140,   ///< Идентификатор номенклатуры
        Nomenclature_name,          ///< Наименование номенклатуры
        Nomenclature_group_id,      ///< Идентификатор папки куда относиться номенклатура
        // nomenclature by
        By_weight = 0xA150, ///< Учет по весу
        By_piece,           ///< Учет поштучно
        By_date,            ///< Учет по датам
        By_consignment,     ///< Учет по партиям
        By_serial,          ///< Учет по серийным номерам
        // quality
        Quality_id = 0xA160,    ///< Идентификатор качества
        Quality_name,           ///< Наименование качества
        Quality_reason_id,      ///< Идентификатор смены качества
        Quality_reason_name,    ///< Название причины смены качества
        Quality_reason_comment, ///< Коментарий к смене качества
        // warehouse
        Warehouse_id = 0xA170,   ///< Идентификатор склада
        Warehouse_name,          ///< Наименование склада
        Warehouse_sender_id,     ///< Идентификатор склада отправителя
        Warehouse_sender_name,   ///< Наименование склада отправителя
        Warehouse_receiver_id,   ///< Идентификатор склада получателя
        Warehouse_receiver_name, ///< Наименование склада получателя

        // date ------------------------------------------------------------------------------------
        Date = 0xA200,   ///< Дата
        Date_time,       ///< Дата и время
        Date_block,      ///< Дата резервирования контейнера и т.д.
        Date_packing,    ///< Дата пакования
        Date_production, ///< Дата производства
        ShelfLife,       ///< Срок годности

        // dimension -------------------------------------------------------------------------------
        Height = 0xA210, ///< Высота
        Length,          ///< Длина
        Weight,          ///< Вес
        Width,           ///< Ширина

        // document --------------------------------------------------------------------------------
        Document_id = 0xA300, ///< Идентификатор документа
        Document_date,        ///< Дата документа
        Document_name,        ///< Наименование документа (или его номер в строковом виде)
        Document_header,      ///< Общая информация про документа (его шапка)

        // document line ---------------------------------------------------------------------------
        Actual = 0xA400, ///< Фактические строки
        Line_id,         ///< Идентификатор строки
        Line_number,     ///< Порядковый номер строки на выполнение
        Plan,            ///< Плановые строки
        Status,          ///< Статус документа
        Transit,         ///< Транзитные строки
        // is
        Is_done = 0xA410, ///< Выполен или нет?
        Is_default,       ///< Это значение по умолчанию?
        Is_transit,       ///< Это транзит?
        // quantity
        Quantity = 0xA420, ///< Количество
        Quantity_pallet,   ///< Количество в палете
        Quantity_carton,   ///< Количество в коробке
        Quantity_packing,  ///< Количество в упаковке

        // employee --------------------------------------------------------------------------------
        Employee_id = 0xA500, ///< Идентификатор пользователя
        Employee_name,        ///< Имя пользователя
        Password,             ///< Пароль
        Provider_id,          ///< Идентификатор поставщика
        Provider_name,        ///< Имя поставщика

        // server key ------------------------------------------------------------------------------
        Code = 0xA600, ///< Код (не знаю зачем это)
        Data,          ///< Данные от сервера по запросу
        Error,         ///< Номер ошибки
        Meta,          ///< Данные о запросе
        Message,       ///< Сообщение ошибки
        Request,       ///< Уникальный код запроса
        Result,        ///< Результат ответа
        Text,          ///< Текст (например текст ошибки)
        Url,           ///< Адрес запроса

        // other ----------------------------------------------------------------------------------
        Folder = 0xA700, ///< Папка (директория)

    }; Q_ENUMS(Json_enum)

    static WEnum::Version version() { return WEnum::Version_0_1; }
    static bool insert(QJsonObject& obj, WJson_enum key, const QJsonValue& value_insert,
                       WEnum::Version version_ = version());
    QString value(WJson_enum key, QString default_ = WStatic::undefined(),
                  WEnum::Version version_ = version());

    static QJsonObject createObject(WJson_enum key, const QJsonValue& value_insert,
                                    WEnum::Version version_ = version());

    static QJsonObject createObject(std::initializer_list<std::pair<WJson_enum, QJsonValue> > list,
                                    WEnum::Version version_ = version());

    static QString toString(WJson_enum key, WEnum::Version version_ = version());
    static QJsonValue get(const QJsonObject& obj,  WJson_enum key, WEnum::Version version_ = version());
    static QJsonValue get(const QJsonValue& value, WJson_enum key, WEnum::Version version_ = version());
    static bool  contains(const QJsonObject& obj,  WJson_enum key, WEnum::Version version_ = version());
    static bool  contains(const QJsonValue& value, WJson_enum key, WEnum::Version version_ = version());

public slots:
    static QString toString(int key, int version_ = version());

private:
    struct WJson_single {
        WJson_enum key;
        QString name;
        WEnum::Version version;
    };

    QList <WJson_single> m_list;
};

#endif // WJSON_H
