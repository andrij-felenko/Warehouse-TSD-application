#include "wEnum.h"
#include "wStatic.h"

QHash<int, QByteArray> WEnum::getModelHash()
{
    QHash <int, QByteArray> hash;
    hash[Model_barcode] = "m_barcode";
    hash[Model_id]      = "m_id";
    hash[Model_item]    = "m_item";
    hash[Model_name]    = "m_name";
    return hash;
}
