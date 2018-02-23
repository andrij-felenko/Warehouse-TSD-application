#ifndef WCACHELIST_TEMPLATE_H
#define WCACHELIST_TEMPLATE_H

#include <QtCore/QDataStream>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonObject>
#include <QtCore/QList>
#include <QtCore/QString>

#include "cache/list/wCacheListObject.h"
#include "enum/wJson.h"

/*!
 * \brief Шаблон для класов списков кэша.
 * \details Клас шаблон, включает в себя все стандартные функции
 * по работе со списками данных в кэше.\n
 * Контролирует удаление, добавление, редактирование и сохранение списков в памяти.
 */
template <typename T>
class WCacheListTemplate : public WCacheListObject
{
public:
    /*!
     * \param dir директория для хранения кэша
     * \param name наименование кэша
     * \param parent ссылка на родительский обьект
     * \warning Сохранение в на устройство отключено
     */
    WCacheListTemplate(const QDir &dir, QString name, QObject *parent = nullptr)
        : WCacheListObject(parent),
          m_local_dir(dir),
          m_local_file_name(name){
        readLocalCache();
    }

    /*! \brief Возвращает количество элементов в списке */
    virtual int length() const final { return m_list.length(); }

    /*! \brief Возвращает количество элементов в списке */
    virtual int count() const final { return m_list.count(); }

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

    /*! \brief getIdList Запрос списка идентификаторов */
    virtual QStringList getIdList() const final
    {
        QStringList list;
        for (auto it : m_list)
            list.push_back(it->id());
        return list;
    }

    /*!
     * \brief Возвращает оидн элемент со списка
     * \param position - позиция в списке
     * \return Элемент со списка, если позиции не существует возвращает nullptr.
     */
    virtual T* getOne(int position) const final
    {
        if (position >= this->count())
            return nullptr;
        return m_list[position];
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

    /*!
     * \brief Добавление списка в кэш.
     * \param array масив json-обьектов для пополнение кэша
     */
    virtual void add(const QJsonArray& array) final
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

    /*!
     * \brief Добавление одного обьекта в кэш
     * \param obj json-обьект нового элемента кэша
     */
    virtual void addOne(const QJsonObject& obj) final
    {
        T* single = new T(obj, this);
        p_addOne(single);

        emit listPushed(QStringList(single->id()));
        saveLocalCache();
    }

    /*!
     * \brief Добавление одного обьекта в кэш по значению
     * \param value json-значение нового элемента кэша
     */
    virtual void addOne(const QJsonValue& value) final
    {
        T* single = new T(value.toObject(), this);
        p_addOne(single);

        emit listPushed(QStringList(single->id()));
        saveLocalCache();
    }

    /*!
     * \brief Добавление одного обьекта в кэш по ссылке
     * \param single Новый элемент кэша
     */
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

    /*!
     * \brief Обновление элементов кэша.
     * \details Обновление элемента кэша, если какого то єлемента нет, добавит его.
     * \param array масив json-обьектов
     */
    virtual void update(const QJsonArray& array) final
    {
        QStringList idPushList;
        QStringList idUpdateList;
        for (auto it : array){
            QString id(WJson::get(it, WJson::Id).toString());
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

    /*!
     * \brief Обновление элемента кэша.
     * \details Обновление элемента кэша, если его нет, добавляем его.
     * \param obj json-обьект
     */
    virtual void update(const QJsonObject& obj) final
    {
        QString id(WJson::get(obj, WJson::Id).toString());
        T* single = getOne(id);
        if (p_update(single, obj))
            emit listPushed(QStringList(id));
        else
            emit listUpdated(QStringList(single->id()));
        saveLocalCache();
    }

    /*!
     * \brief Обновление элемента кэша.
     * \details Обновление элемента кэша, если его нет, добавляем его.
     * \param value json-переменная (или список или обьект, иначе ничего не произойдет)
     */
    virtual void update(const QJsonValue& value) final
    {
        if (value.isArray())
            update(value.toArray());
        else if (value.isObject())
            update(value.toObject());
    }

    /*!
     * \brief Запрос штрихкода по идентификатору
     * \param id Идентификатор
     * \return Штрихкод элемента кеша по идентификатору.
     */
    virtual const QString getBarcodeById(const QString& id) const final
    {
        for (auto it : m_list)
            if (it->id() == id)
                return it->barcode();
        return WStatic::undefined();
    }

    /*!
     * \brief Запрос штрихкода по наименованию
     * \param name Наименование
     * \return Штрихкод элемента кеша по наименованию.
     */
    virtual const QString getBarcodeByName(const QString& name) const final
    {
        for (auto it : m_list)
            if (it->name() == name)
                return it->barcode();
        return WStatic::undefined();
    }

    /*!
     * \brief Запрос идентификатора по штрихкоду
     * \param barcode Штрихкод
     * \return Идентификатор элемента кеша по штрихкоду.
     */
    virtual const QString getIdByBarcode(const QString& barcode) const final
    {
        for (auto it : m_list)
            if (it->barcode() == barcode)
                return it->id();
        return WStatic::guidDefault();
    }

    /*!
     * \brief Запрос идентификатора по наименованию
     * \param name Наименование
     * \return Идентификатор элемента по имени.
     */
    virtual const QString getIdByName(const QString& name) const final
    {
        for (auto it : m_list)
            if (it->name() == name)
                return it->id();
        return WStatic::guidDefault();
    }

    /*!
     * \brief Запрос наименования по штрихкоду
     * \param barcode Штрихкод
     * \return Наименование элемента по штрихкоду.
     */
    virtual const QString getNameByBarcode(const QString& barcode) const final
    {
        for (auto it : m_list)
            if (it->barcode() == barcode)
                return it->name();
        return WStatic::undefined();
    }

    /*!
     * \brief Запрос наименования по идентификатору
     * \param id Идентификатор
     * \return Наименование элемента по идентифкатору.
     */
    virtual const QString getNameById(const QString& id) const final
    {
        for (auto it : m_list)
            if (it->id() == id)
                return it->name();
        return WStatic::undefined();
    }

    /*! \brief Обновить время полного обновления кэша */
    virtual void setUpdateDateTime() final
    {
        m_dateTime = QDateTime::currentDateTime();
        saveLocalCache();
    }

protected:
    /*!
     * \brief Чтение кэша с локального хранилища и загрузка его в операционную память
     * \return Удачность чтения.
     */
    virtual bool readLocalCache() final
    {
        QFile file(m_local_dir.absoluteFilePath(m_local_file_name + ".cache"));
        if (file.open(QIODevice::ReadOnly)){
            QDataStream stream(&file);
            QStringList idList;
            removeAll();
            stream >> m_dateTime;

            while (! stream.atEnd()){
                T* single = new T(this);
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
            stream << m_dateTime;
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
    QDateTime m_dateTime;      ///< Время последнего полного обновления

    /*!
     * \brief Внутренний метод для добавления элемента
     * \details Универсальный для всех остальных методов
     * \param single Элемент готовый для добавления в кэш.
     */
    virtual void p_addOne(T* const single) final
    {
        removeById(single->id());
        m_list.push_back(single);
    }

    /*!
     * \brief Функция обновления кэша.
     * \details Определяет есть ли в системе уже данный обьект, если нет, добавляет его,
     * если есть, обновляет и перезаписывает значение.
     * \param single Ссылка на обьект, или nullptr если обьекта еще нет в системе
     * \param obj json-обьект с новой ифнормацией про обьект
     * \return Истину если обьект перезаписан, или ложь если обьект был создан новый.
     */
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
