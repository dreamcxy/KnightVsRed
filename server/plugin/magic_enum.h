//
// Created by chenxiaoyu5 on 2022/8/1.
//


#ifndef KNIGHTVSREDSERVER_MAGIC_ENUM_H
#define KNIGHTVSREDSERVER_MAGIC_ENUM_H



namespace magic_enum
{


    #define ENUM_MACRO(name, v1, v2, v3) \
        enum class name {v1, v2, v3};        \
        const char* psz##name[] = {#v1, #v2, #v3}; \
        template<typename T>             \
        constexpr const char* name##ToString(T value) { return psz##name[static_cast<int>(value)]; }

}




#endif //KNIGHTVSREDSERVER_MAGIC_ENUM_H
