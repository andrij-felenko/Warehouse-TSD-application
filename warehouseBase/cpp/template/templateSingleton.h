#ifndef TEMPLATESINGLETON_H
#define TEMPLATESINGLETON_H

#include <stdlib.h>
#include <QtCore/QObject>

template <typename T>
class TemplateSingleton
{
public:
    static void instance(QObject* parent = nullptr)
    {
        if (TemplateSingleton::_instance == nullptr) {
            TemplateSingleton::_instance = CreateInstance(parent);
        }
    }

    static T& get()        { return *(TemplateSingleton::_instance); }
    static T* registrate() { return _instance; }

protected:
    virtual ~TemplateSingleton()
    {
        if (TemplateSingleton::_instance != nullptr) {
            delete TemplateSingleton::_instance;
        }
        TemplateSingleton::_instance = nullptr;
    }

    inline explicit TemplateSingleton() { TemplateSingleton::_instance = static_cast <T*> (this); }

private:
    static T* _instance;
    static T* CreateInstance(QObject* parent) { return new T(parent); }
};

template<typename T>
T* TemplateSingleton < T >::_instance = nullptr;

#endif // TEMPLATESINGLETON_H
