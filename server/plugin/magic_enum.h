//
// Created by chenxiaoyu5 on 2022/8/1.
// 模拟magic_enum这个在c++17上面的库实现的
//


#ifndef KNIGHTVSREDSERVER_MAGIC_ENUM_H
#define KNIGHTVSREDSERVER_MAGIC_ENUM_H

#include "type_traits"
#include "string"

namespace magic_enum
{
//    原来的magic_enum的方法行不通
//    template<typename E, E V>
//    constexpr auto n() noexcept
//    {
//        static_assert(std::is_enum<E>,  "this is not enum type, need enum type");
//        constexpr auto name = __PRETTY_FUNCTION__ ;
//
//
//    }
//
//    constexpr std::string pretty_name(std::string& name) noexcept {
//        for (std::size_t i = name.size(); i > 0; --i) {
//            if (!((name[i - 1] >= '0' && name[i - 1] <= '9') ||
//                  (name[i - 1] >= 'a' && name[i - 1] <= 'z') ||
//                  (name[i - 1] >= 'A' && name[i - 1] <= 'Z') ||
//                  #if defined(MAGIC_ENUM_ENABLE_NONASCII)
//                  (name[i - 1] & 0x80) ||
//                  #endif
//                  (name[i - 1] == '_')))
//            {
//                name.erase(i);
////                name.remove_prefix(i);
//                break;
//            }
//        }
//
//        // 这里检查名称是否有效，注意到这里和前面稍有不同，这里不允许出现数字
//        if (name.size() > 0 && ((name.front() >= 'a' && name.front() <= 'z') ||
//                                (name.front() >= 'A' && name.front() <= 'Z') ||
//                                #if defined(MAGIC_ENUM_ENABLE_NONASCII)
//                                (name.front() & 0x80) ||
//                                #endif
//                                (name.front() == '_'))) {
//            return name;
//        }
//
//        return {}; // Invalid name.
//    }

#define stringify(name) #name

#define convert_enum_to_string() {\
    \
}

}




#endif //KNIGHTVSREDSERVER_MAGIC_ENUM_H
