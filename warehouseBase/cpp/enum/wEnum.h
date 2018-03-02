#ifndef WENUM_H
#define WENUM_H

#include <QtCore/QByteArray>
#include <QtCore/QObject>
#include <QtCore/QHash>

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
        Request_can_ignore,           ///< Запрос может быть проигнорирован
    }; Q_ENUMS(Request_priority)

    enum Msg_type {
        Msg_progress = 0xE300, ///< Сообщение о процесе запроса или работы с кэшем
        Msg_complete,          ///< Выполненое сообщение
        Msg_warning,           ///< Сообщение содержит предупреждение о возможных проблемах
        Msg_error,             ///< Сообщение об ошибке
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
        Version_1_0,           ///< Версия 1.0 [1.02.2018]
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

    enum Sort {
        SortByAZ = 0xE700,   ///< Сортировка по алфавиту
        SortByZA,            ///< Сортировку против алфавита
        SortByNewest,        ///< Сортировка, новые сначала
        SortByOldest,        ///< Сортировка, старые сначала
        SortByPushed,        ///< Сортировка по времени добавления
        SortByPushedReverse, ///< Сортировка по времени убывания
    }; Q_ENUMS(Sort)

    enum DocumentStatus {
        Document_created = 0xE800, ///< Документ создан
        Document_inWorking,        ///< Документ в работе
        Document_accepted,         ///< Документ выполнен
        Document_done,             ///< Документ подтвержден и закрыт
    }; Q_ENUMS(DocumentStatus)

    enum ModelItems {
        Model_item = Qt::DisplayRole, ///< Единица из списка в моделе
        Model_id   = Qt::UserRole,
        Model_name,
        Model_barcode,
        Model_actualQuantity,
        Model_planQuantity,
    }; Q_ENUMS(ModelItems)

    enum LineType {
        LineActual = 0xE900, ///< Актуальные строки
        LinePlan,            ///< Плановые строки
        LineDone,            ///< Все выполненные строки
        LineAll,             ///< Все строки
    }; Q_ENUMS(LineType)

    enum ServerCacheStatus {
        SCache_created = 0xEA00, ///< Создан
        SCache_send,             ///< Отправлен
        SCache_errorData,        ///< Ошибка получаемых данных
        SCache_errorNetwork,     ///< Ошибка сети или времени ожидания
        SCache_takeResult,       ///< Получен результат
        SCache_handlered,        ///< Обработан
        SCache_done,             ///< Выполнен
        SCache_canceled,         ///< Отменен
    }; Q_ENUMS(ServerCacheStatus)

public slots:
    static QHash <int, QByteArray> getModelHash();
//    static QString statusToString(WEnum::DocumentStatus status);
};

#endif // WENUM_H
