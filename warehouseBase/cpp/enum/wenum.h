#ifndef WENUM_H
#define WENUM_H

#include <QtCore/QObject>

/*! \brief Клас перечислений что используються в проэкте */
class WEnum : public QObject
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
        Priority_low           = 0xE100 | (1 << 0), ///< Низкий
        Priority_middle_bellow = 0xE100 | (1 << 1), ///< Ниже среднего
        Priority_middle        = 0xE100 | (1 << 2), ///< Средний
        Priority_middle_above  = 0xE100 | (1 << 3), ///< Выше среднего
        Priority_high          = 0xE100 | (1 << 4), ///< Высокий
    }; Q_ENUMS(Priority)

    enum Request_priority {
        Request_must_server = 0xE200, ///< Запрос требует соединение к серверу
        Request_can_cache,            ///< Запрос может быть кэширован для отправки потом
        Request_just_info,            ///< Запрос может быть проигнорирован
    }; Q_ENUMS(Request_priority)

    enum Msg_type {
        Msg_error = 0xE300, ///< Сообщение об ошибке
        Msg_complete,       ///< Выполненое сообщение
        Msg_progress,       ///< Сообщение о процесе запроса или работы с кэшем
        Msg_warning,        ///< Сообщение содержит предупреждение о возможных проблемах
    }; Q_ENUMS(Msg_type)

    enum Msg_status {
        Msg_close = 0xE320, ///< Сообщение уже было показано
        Msg_show,           ///< Сообщение отображаеться в данный момент
        Msg_waiting,        ///< Сообщение в ожидании для отображения
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

#endif // WENUM_H