#ifndef WTEMPLATESINGLETON_H
#define WTEMPLATESINGLETON_H

#include <stdlib.h>
#include <QtCore/QObject>

template <typename T>
class WTemplateSingleton
{
public:
    static void instance(QObject* parent = nullptr)
    {
        if (WTemplateSingleton::_instance == nullptr) {
            WTemplateSingleton::_instance = CreateInstance(parent);
        }
    }

    static T& get()        { return *(WTemplateSingleton::_instance); }
    static T* registrate() { return _instance; }

protected:
    virtual ~WTemplateSingleton()
    {
        if (WTemplateSingleton::_instance != nullptr) {
            delete WTemplateSingleton::_instance;
        }
        WTemplateSingleton::_instance = nullptr;
    }

    inline explicit WTemplateSingleton() { WTemplateSingleton::_instance = static_cast <T*> (this); }

private:
    static T* _instance;
    static T* CreateInstance(QObject* parent) { return new T(parent); }
};

template<typename T>
T* WTemplateSingleton < T >::_instance = nullptr;

#endif // TEMPLATESINGLETON_H
