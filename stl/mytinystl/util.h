#ifndef MYTINYSTL_UTIL_H_
#define MYTINYSTL_UTIL_H_

// 这个文件包含一些通用工具，包括 move, forward, swap 等函数，以及 pair 等 

#include <cstddef>

#include "type_traits.h"

namespace mystl
{
// move
template <typename T>
typename std::remove_reference<T>::type&& move(T&& arg) noexcept
{
    return static_cast<typename std::remove_reference<T>::type&&>(arg);
}

// forward
template <typename T>
T&& forward(typename std::remove_reference<T>::type& arg) noexcept
{
    return static_cast<T&&>(arg);
}

template <typename T>
T&& forward(typename std::remove_reference<T>::type&& arg) noexcept
{
    static_assert(!std::is_lvalue_reference<T>::value, "bad forward");
    return static_cast<T&&>(arg);
}

// swap
template <typename T>
void swap(T& lhs, T& rhs)
{
    auto tmp(mystl::move(lhs));
    lhs = mystl::move(rhs);
    rhs = mystl::move(tmp);
}

template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator2 swap_range(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2)
{
    for(; first1 != last1; ++first1, (void) ++first2){
        mystl::swap(*first1, *first2);
    }
    return first2;
}

template <typename T, size_t N>
void swap(T(&a)[N], T(&b)[N])
{
    mystl::swap_range(a, a + N, b);
}


// pair

// 结构体模板 : pair
// 两个模板参数分别表示两个数据的类型
// 用 first 和 second 来分别取出第一个数据和第二个数据
template <typename T1, typename T2>
struct pair
{

    typedef T1 first_type;
    typedef T2 second_type;

    first_type first;    // 保存第一个数据
    second_type second;  // 保存第二个数据

    // default constructiable
    template <typename Other1 = T1, typename Other2 = T2,
    typename std::enable_if<std::is_default_constructible<Other1>::value &&
    std::is_default_constructible<Other2>::value, void>::type = 0>
    constexpr pair(): first(), second() {}

    // implicit constructiable for this type
    template <typename U1 = T1, typename U2 = T2,
    typename std::enable_if<std::is_copy_constructible<U1>::value && std::is_copy_constructible<U2>::value
    && std::is_convertible<const U1&, T1>::value && std::is_convertible<const U2&, T2>::value, int>::type = 0>
    constexpr pair(const T1& a, const T2& b): first(a), second(b) {}

    // explicit constructible for this type
    template <typename U1 = T1, typename U2 = T2,
    typename std::enable_if<std::is_copy_constructible<U1>::value && std::is_copy_constructible<U2>::value
    && (!std::is_convertible<const U1&, T1>::value || !std::is_convertible<const U2&, T2>::value), int>::type = 0>
    explicit constexpr pair(const T1& a, const T2& b): first(a), second(b) {}

    pair(const pair& rhs) = default;
    pair(pair&& rhs) = default;

    // implicit constructiable for other type
    template <typename Other1, typename Other2,
    typename std::enable_if<std::is_constructible<T1, Other1>::value && std::is_constructible<T2, Other2>::value
    && std::is_convertible<Other1&&, T1>::value && std::is_convertible<Other2&&, T2>::value, int>::type = 0>
    constexpr pair(Other1&& a, Other2&& b): first(mystl::forward<Other1>(a)), second(mystl::forward<Other2>(b)) {}

    // explicit constructiable for other type
    template <typename Other1, typename Other2,
    typename std::enable_if<std::is_constructible<T1, Other1>::value && std::is_constructible<T2, Other2>::value
    &&(!std::is_convertible<Other1, T1>::value || !std::is_convertible<Other2&&, T2>::value), int>::type = 0>
    explicit constexpr pair(Other1&& a, Other2&& b): first(mystl::forward<Other1>(a)), second(mystl::forward<Other2>(b)) {}

    // implicit constructiable for other pair
    template<typename Other1, typename Other2,
    typename std::enable_if<std::is_constructible<T1, const Other1&>::value && std::is_constructible<T2, const Other2&>::value
    && std::is_convertible<const Other1&, T1>::value && std::is_convertible<const Other2&, T2>::value, int>::type = 0>
    constexpr pair(const pair<Other1, Other2>& other): first(other.first), second(other.second) {}

// explicit constructiable for other pair
template<typename Other1, typename Other2,
typename std::enable_if<
std::is_constructible<T1, const Other1&>::value &&
std::is_constructible<T2, const Other2&>::value &&
(!std::is_convertible<const Other1&, T1>::value ||
!std::is_convertible<const Other2&, T2>::value), int>::type = 0>
explicit constexpr pair(const pair<Other1, Other2>& other)
: first(other.first), second(other.second){}

// implicit constructiable for other pair
template<typename Other1, typename Other2,
typename std::enable_if<
std::is_constructible<T1, Other1>::value &&
std::is_constructible<T2, Other2>::value &&
std::is_convertible<Other1, T1>::value &&
std::is_convertible<Other2, T2>::value, int>::type = 0>
constexpr pair(pair<Other1, Other2>&& other)
: first(mystl::forward<Other1>(other.first)), second(mystl::forward<Other2>(other.second)){}

// explicit constructiable for other pair
template<typename Other1, typename Other2,
typename std::enable_if<
std::is_constructible<T1, Other1>::value &&
std::is_constructible<T2, Other2>::value &&
(!std::is_convertible<Other1, T1>::value ||
!std::is_convertible<Other2, T2>::value), int>::type = 0>
explicit constexpr pair(const pair<Other1, Other2>& other)
: first(mystl::forward<Other1>(other.first)), second(mystl::forward<Other2>(other.second)){}


    // copy assign for this pair
    pair& operator=(const pair& rhs){
        if(this != &rhs){
            first = rhs.first;
            second = rhs.second;
        }
        return *this;
    }

    // move assign for this pair
    pair& operator=(pair&& rhs){
        if(this != &rhs){
            first = mystl::move(rhs.first);
            second = mystl::move(rhs.second);
        }
        return *this;
    }

    // copy assign for other pair
    template <typename Other1, typename Other2>
    pair& operator=(const pair<Other1, Other2>& rhs){
        first = rhs.first;
        second = rhs.second;
        return *this;
    }

    // move assign for other pair
    template <typename Other1, typename Other2>
    pair& operator=(pair<Other1, Other2>&& rhs){
        first = mystl::forward<Other1>(rhs.first);
        second = mystl::forward<Other2>(rhs.second);
        return *this;
    }

    ~pair() = default;

    void swap(pair& other){
        if(this != &other){
            mystl::swap(first, other.first);
            mystl::swap(second, other.second);
        }
    }
};


// 重载比较操作符
template <class T1, class T2>
bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template <class T1, class T2>
bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
}

template <class T1, class T2>
bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(lhs == rhs);
}

template <class T1, class T2>
bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return rhs < lhs;
}

template <class T1, class T2>
bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(rhs < lhs);
}

template <class T1, class T2>
bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
{
    return !(lhs < rhs);
}


// 重载 mystl 的 swap
template <class T1, class T2>
void swap(pair<T1, T2>& lhs, pair<T1, T2>& rhs)
{
    lhs.swap(rhs);
}

// 全局函数，让两个数据成为一个 pair
template <class T1, class T2>
pair<T1, T2> make_pair(T1&& first, T2&& second)
{
    return pair<T1, T2>(mystl::forward<T1>(first), mystl::forward<T2>(second));
}

}

#endif // !MYTINYSTL_UTIL_H_