/**
 * 单例类,线程安全
 * 
**/ 
#include<iostream>
#include<type_traits>

template<typename T>
class TSingleton
{
public:
    static T* GetInstance() noexcept(std::is_nothrow_constructible<T>::value)
    {
        // 局部static变量，保证线程安全
        static T instance;
        return &instance;
    }

    virtual ~TSingleton() noexcept 
    {
        #ifdef DEBUG
            std::cout << "singleton destroy" << std::endl;
        #endif
    }

    // 屏蔽直接创建实例的操作，想要获得此类只能通过GetInstance()方法
    TSingleton(const TSingleton &) = delete;
    TSingleton &operator=(const TSingleton &) = delete;

protected:
    // 采用protected的目的是为了派生类可以继承它
    TSingleton() 
    {
        #ifdef DEBUG
            std::cout << "singleton construct" << std::endl;
        #endif
    }
};

#define DECLARE_CLASS_SINGLETON(type) \
    friend class TSinglton<type>; 
