#ifndef MYTINYSTL_MAP_TEST_H_
#define MYTINYSTL_MAP_TEST_H_

// map test : 测试 map, multimap 的接口与它们 insert 的性能

#include <map>

#include "../mytinystl/vector.h"
// #include "../mytinystl/map.h"
#include "test.h"

namespace mystl
{

namespace test
{

namespace map_test
{

// pair 的宏定义
#define PAIR    mystl::pair<int, int>

// map 的遍历输出
#define MAP_COUT(m) do{                                                         \
    std::string m_name = #m;                                                    \
    std::cout << " " << m_name << " :";                                         \
    for(auto it : m)std::cout << " <" << it.first << "," << it.second << ">";   \
    std::cout << std::endl;                                                     \
}while(0)

// map 的函数操作
#define MAP_FUN_AFTER(con, fun) do{                                             \
    std::string str = #fun;                                                     \
    std::cout << " After " << str << " :" << std::endl;                         \
    fun;                                                                        \
    MAP_COUT(con);                                                              \
}while(0)

// map 的函数值
#define MAP_VALUE(fun) do{                                                      \
    std::string str = #fun;                                                     \
    auto it = fun;                                                              \
    std::cout << " " << str << " : <" << it.first << "," << it.second << ">\n"; \
}while(0)




}

}

}

#endif