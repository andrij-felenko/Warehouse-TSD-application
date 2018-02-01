#ifndef SINGLETON_H
#define SINGLETON_H

#include "template/templateSingleton.h"

#include "cache/cachePrototype.h"
#include "model/modelPrototype.h"
#include "server/serverPrototype.h"
#include "setting/settingPrototype.h"

/*! \brief Singleton обьект для работы с кэшем */
class Cache : public TemplateSingleton <CachePrototype> {};

/*! \brief Singleton обьект управления моделями данных */
class Model : public TemplateSingleton <ModelPrototype> {};

/*! \brief Singleton обьект работы для работы с сервером */
class Server : public TemplateSingleton <ServerPrototype> {};

/*! \brief Singleton обьект для работы с настройками приложения */
class Settings : public TemplateSingleton <SettingPrototype> {};

#endif // SINGLETON_H
