#ifndef SINGLETON_H
#define SINGLETON_H

#include "template/templateSingleton.h"

#include "cache/cachePrototype.h"

class Cache : public TemplateSingleton <CachePrototype> {};

class Singleton {
public:
    static void instance(QObject* parent = nullptr){
        Cache::instance(parent);
    }
};

#endif // SINGLETON_H
