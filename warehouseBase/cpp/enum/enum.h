#ifndef ERIDON_ENUM_H
#define ERIDON_ENUM_H

#include <QtCore/QObject>

class Enum : public QObject
{
    Q_OBJECT
public:
    Enum() = default;

    enum Side {
        Side_left = 0xA10,
        Side_rigth,
        Side_top,
        Side_bottom,
    }; Q_ENUMS(Side)

    enum Priority {
        Priority_low = 0xA20,
        Priority_middle_bellow,
        Priority_middle,
        Priority_middle_above,
        Priority_high,
    }; Q_ENUMS(Priority)

    enum Request_priority {
        Request_must_server = 0xA30,
        Request_can_cache,
        Request_just_info,
    }; Q_ENUMS(Request_priority)

    enum Msg_status {
        Msg_complete = 0xA40,
        Msg_error,
        Msg_progress,
    }; Q_ENUMS(Msg_status)

    enum Document_type {
        Document_acceptance = 0xA50,
        Document_movement,
        Document_selection,
        Document_shipment,
        Document_none,
    }; Q_ENUMS(Document_type)

    enum Version {
        Version_none = 0xA60,
        Version_0_1,
    };

    enum CacheType {
        Cache_activityType = 0xB00,
        Cache_cell,
        Cache_consignment,
        Cache_container,
        Cache_containerType,
        Cache_employee,
        Cache_error,
        Cache_modelType,
        Cache_nomenclature,
        Cache_quality,
        Cache_storageType,
        Cache_supplier,
        Cache_unknown,
    }; Q_ENUMS(CacheType)
};

#endif // ERIDON_ENUM_H