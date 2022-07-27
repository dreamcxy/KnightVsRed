//
// Created by chenxiaoyu5 on 2022/7/27.
// 一个通用的raii模板
//

#include <functional>

#ifndef SERVER_RAII_H
#define SERVER_RAII_H


// 这个写法是直接用manager去管理外部申请的对象
class CRAIIManager
{
    using func_type = std::function<void()>;

public:
    explicit CRAIIManager(func_type release, func_type acquire = []{}) noexcept : m_oRelease(release)
    {
        acquire();
    }
    ~CRAIIManager()
    {
        m_oRelease();
    };

    // 禁用拷贝构造 和 赋值
    CRAIIManager(const CRAIIManager&) = delete;
    CRAIIManager &operator=(const CRAIIManager&) = delete;

private:

private:
    std::function<void()> m_oRelease; // 析构函数调用的操作

};



#endif //SERVER_RAII_H
