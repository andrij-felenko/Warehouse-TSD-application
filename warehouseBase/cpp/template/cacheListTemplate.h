#ifndef CACHELIST_TEMPLATE_H
#define CACHELIST_TEMPLATE_H

#include <QtCore/QDir>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QList>
#include <QtCore/QString>

#include "cacheListObject.h"
#include "cacheSingle.h"
#include "json.h"

/*!
 * \brief Шаблон для класов списков кэша.
 * \details Клас шаблон, включает в себя все стандартные функции
 * по работе со списками данных в кэше.\n
 * Контролирует удаление, добавление, редактирование и сохранение списков в памяти.
 */
template <typename T>
class CacheListTemplate : public CacheListObject
{
public:
    /*!
     * \param dir директория для хранения кэша
     * \param name наименование кэша
     * \param parent ссылка на родительский обьект
     * \warning Сохранение в на устройство отключено
     */
    CacheListTemplate(const QDir &dir, QString name, QObject *parent = nullptr)
        : CacheListObject(parent),
          m_local_dir(dir),
          m_local_file_name(name){
        // FIXME read uncomment
        //        readLocalCache();
    }

    /*!
     * \brief Возвращает один елемент со списка.
     * \details Функция возвращает один элемент по заданому идентификатору при условии
     * что он существует, иначе возвращает nullptr.
     * \param id - идентификатор обьекта в кэше
     * \return Возвращает ссылку на обьект при его наличии, иначе nullptr.
     */
    virtual T* getOne(const QString &id) const final
    {
        for (auto it : m_list)
            if (it->id() == id)
                return it;
        return nullptr;
    }

    /*!
     * \brief Проверка на наличие ключа в списке.
     * \details Функция проверяет есть ли заданый ключ в списке.
     * \param barcode - штрихкод обьекта
     * \return Возвращает результат есть ли в списке или нет.
     */
    virtual bool containsBarcode(const QString &barcode) const final
    {
        for (auto it : m_list)
            if (it->barcode() == barcode)
                return true;
        return false;
    }

    /*!
     * \brief Проверка на наличие ключа в списке.
     * \details Функция проверяет есть ли заданый ключ в списке.
     * \param id - идентификатор обьекта
     * \return Возвращает результат есть ли в списке или нет.
     */
    virtual bool containsId(const QString &id) const final
    {
        for (auto it : m_list)
            if (it->id() == id)
                return true;
        return false;
    }

    /*!
     * \brief Проверка на наличие ключа в списке.
     * \details Функция проверяет есть ли заданый ключ в списке.
     * \param name - имя обьекта
     * \return Возвращает результат есть ли в списке или нет.
     */
    virtual bool containsName(const QString &name) const final
    {
        for (auto it : m_list)
            if (it->name() == name)
                return true;
        return false;
    }

    virtual void add   (const QJsonArray& array) final
    {
        QStringList idList;

        for (auto it : array){
            T* single = new T(it.toObject(), this);
            p_addOne(single);
            idList.push_back(single->id());
        }

        emit listPushed(idList);
        saveLocalCache();
    }

    virtual void addOne(const QJsonObject& obj) final
    {
        T* single = new T(obj, this);
        p_addOne(single);

        emit listPushed(QStringList(single->id()));
        saveLocalCache();
    }

    virtual void addOne(const QJsonValue& value) final
    {
        T* single = new T(value.toObject(), this);
        p_addOne(single);

        emit listPushed(QStringList(single->id()));
        saveLocalCache();
    }

    virtual void addOne(T* const single) final
    {
        p_addOne(single);

        emit listPushed(QStringList(single->id()));
        saveLocalCache();
    }

    /*!
     * \brief Очищает список
     * \details Функция удаляет все обьекты списка, очищает список и оповещает систему про это.
     */
    virtual void removeAll() final
    {
        QStringList idList;
        for (auto it : m_list){
            idList.push_back(it->id());
            it->deleteLater();
        }
        m_list.clear();

        idList.removeDuplicates();
        if (! idList.isEmpty())
            emit listPoped(idList);
    }

    /*!
     * \brief Удаляет один элемент со списка по идентификатору.
     * \param id - идентификатор обьекта
     * \return Возвращает логический результат удаления.
     * \warning Сохранение в на устройство отключено
     */
    virtual bool removeById(const QString& id) final
    {
        bool ret(false);
        for (auto it : m_list)
            if (it->id() == id){
                it->deleteLater();
                m_list.removeOne(it);
                ret = true;
            }

        if (ret){
            emit listPoped(QStringList(id));
            saveLocalCache();
        }

        return ret;
    }

    virtual void update(const QJsonArray& array) final
    {
        QStringList idPushList;
        QStringList idUpdateList;
        for (auto it : array){
            QString id(Json::get(it, Json::Id).toString());
            T* single = getOne(id);
            if (p_update(single, it.toObject()))
                idPushList.push_back(id);
            else
                idUpdateList.push_back(single->id());
        }

        if (! idPushList.isEmpty())
            emit listPushed(idPushList);
        if (! idUpdateList.isEmpty())
            emit listUpdated(idUpdateList);
        saveLocalCache();
    }

    virtual void update(const QJsonObject& obj) final
    {
        QString id(Json::get(obj, Json::Id).toString());
        T* single = getOne(id);
        if (p_update(single, obj))
            emit listPushed(QStringList(id));
        else
            emit listUpdated(QStringList(single->id()));
        saveLocalCache();
    }

    virtual void update(const QJsonValue& value) final
    {
        QString id(Json::get(value, Json::Id).toString());
        T* single = getOne(id);
        if (p_update(single, value.toObject()))
            emit listPushed(QStringList(id));
        else
            emit listUpdated(QStringList(single->id()));
        saveLocalCache();
    }

    virtual const QString getBarcodeById(const QString& id) const final
    {
        for (auto it : m_list)
            if (it->id() == id)
                return it->barcode();
        return Static::undefined();
    }

    virtual const QString getBarcodeByName(const QString& name) const final
    {
        for (auto it : m_list)
            if (it->name() == name)
                return it->barcode();
        return Static::undefined();
    }

    virtual const QString getIdByBarcode(const QString& barcode) const final
    {
        for (auto it : m_list)
            if (it->barcode() == barcode)
                return it->id();
        return Static::guidDefault();
    }

    virtual const QString getIdByName(const QString& name) const final
    {
        for (auto it : m_list)
            if (it->name() == name)
                return it->id();
        return Static::guidDefault();
    }

    virtual const QString getNameByBarcode(const QString& barcode) const final
    {
        for (auto it : m_list)
            if (it->barcode() == barcode)
                return it->name();
        return Static::undefined();
    }

    virtual const QString getNameById(const QString& id) const final
    {
        for (auto it : m_list)
            if (it->id() == id)
                return it->name();
        return Static::undefined();
    }

protected:
    virtual bool readLocalCache() final
    {
        QFile file(m_local_dir.absoluteFilePath(m_local_file_name + ".cache"));
        if (file.open(QIODevice::ReadOnly)){
            QDataStream stream(&file);
            QStringList idList;
            removeAll();

            while (! stream.atEnd()){
                CacheSingle* single = new T(this);
                stream >> *single;
                m_list.push_back(single);
                idList.push_back(single->id());
            }
            file.close();
            emit listPushed(idList);
            return true;
        }
        return false;
    }

    /*!
     * \brief Сохраняет данные на дисковое хранилища.
     * \return Успешность записи данных.
     * \warning Запись на устройство отключено
     */
    virtual bool saveLocalCache() final
    {
        QFile file(m_local_dir.absoluteFilePath(m_local_file_name + ".cache"));
        if (file.open(QIODevice::Truncate | QIODevice::WriteOnly)){
            QDataStream stream(&file);
            for (auto it : m_list)
                stream << *it;
            file.close();
            return true;
        }
        return false;
    }

private:
    QDir m_local_dir;          ///< Директорию для хранения данных на диске.
    QList <T*> m_list;         ///< Список строк кэша.
    QString m_local_file_name; ///< Наименование кэша.


    virtual void p_addOne(T* const single) final
    {
        removeById(single->id());
        m_list.push_back(single);
    }

    virtual bool p_update(T* single, const QJsonObject& obj) final
    {
        if (single == nullptr)
            m_list.push_back(new T(obj, this));
        else
            single->fromJson(obj);

        return single == nullptr;
    }
};

#endif // CACHELIST_TEMPLATE_H
