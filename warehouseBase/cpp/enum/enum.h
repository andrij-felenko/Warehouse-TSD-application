#ifndef ERIDON_ENUM_H
#define ERIDON_ENUM_H

#include <QtCore/QObject>

/*! \brief Клас перечислений что используються в проэкте */
class Enum : public QObject
{
    Q_OBJECT
public:
    enum Side {
        Side_left = 0xE000, ///< Привязка к левой стороне
        Side_rigth,         ///< Привязка к правой стороне
        Side_top,           ///< Привязка к верху
        Side_bottom,        ///< Привязка к низу
    }; Q_ENUMS(Side)

    enum Priority {
        Priority_low = 0xE100,  ///< Низкий
        Priority_middle_bellow, ///< Ниже среднего
        Priority_middle,        ///< Средний
        Priority_middle_above,  ///< Выше среднего
        Priority_high,          ///< Высокий
    }; Q_ENUMS(Priority)

    enum Request_priority {
        Request_must_server = 0xE200, ///< Запрос требует соединение к серверу
        Request_can_cache,            ///< Запрос может быть кэширован для отправки потом
        Request_just_info,            ///< Запрос может быть проигнорирован
    }; Q_ENUMS(Request_priority)

    enum Msg_status {
        Msg_complete = 0xE300, ///< Выполненое сообщение
        Msg_error,             ///< Сообщение об ошибке
        Msg_progress,          ///< Сообщение о процесе запроса или работы с кэшем
    }; Q_ENUMS(Msg_status)

    enum Document_type {
        Document_receiving = 0xE400, ///< Приемка
        Document_allotted,           ///< Перемещение
        Document_picking,            ///< Отбор
        Document_purchase,           ///< Отгрузка
        Document_none,               ///< Документ отсутствует
    }; Q_ENUMS(Document_type)

    enum Version {
        Version_none = 0xE500, ///< Без версии
        Version_0_1,           ///< Версия 0.1 [1.02.2018]
    };

    enum CacheType {
        Cache_activityType = 0xE600, ///< Тип активности
        Cache_cell,                  ///< Ячейка
        Cache_consignment,           ///< Партия или серия
        Cache_container,             ///< Контейнер
        Cache_containerType,         ///< Тип контейнера
        Cache_employee,              ///< Пользователь
        Cache_error,                 ///< Ошибка
        Cache_modelType,             ///< Тип учета
        Cache_nomenclature,          ///< Номенклатура
        Cache_quality,               ///< Качество
        Cache_storageType,           ///< Тип хранения
        Cache_supplier,              ///< Поставщик
        Cache_unknown,               ///< Пустой кэш
    }; Q_ENUMS(CacheType)
};

#endif // ERIDON_ENUM_H
