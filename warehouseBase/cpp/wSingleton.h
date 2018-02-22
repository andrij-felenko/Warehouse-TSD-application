#ifndef SINGLETON_H
#define SINGLETON_H

#include "template/wTemplateSingleton.h"

#include "cache/wCachePrototype.h"
#include "document/wDocumentPrototype.h"
#include "message/wMessagePrototype.h"
#include "model/wModelPrototype.h"
#include "server/wServerPrototype.h"
#include "setting/wSettingPrototype.h"
#include "view/wCurrentUser.h"

/*! \brief Singleton обьект для работы с кэшем */
class WCache : public WTemplateSingleton <WCachePrototype> {};

class WUser : public WTemplateSingleton <WCurrentUser> {};

/*! \brief Singleton обьект управления документами */
class WDocument : public WTemplateSingleton <WDocumentPrototype> {};

/*! \brief Singleton обьект управления сообщениями */
class WMessage : public WTemplateSingleton <WMessagePrototype> {};

/*! \brief Singleton обьект управления моделями данных */
class WModel : public WTemplateSingleton <WModelPrototype> {};

/*! \brief Singleton обьект работы для работы с сервером */
class WServer : public WTemplateSingleton <WServerPrototype> {};

/*! \brief Singleton обьект для работы с настройками приложения */
class WSetting : public WTemplateSingleton <WSettingPrototype> {};

#endif // SINGLETON_H
