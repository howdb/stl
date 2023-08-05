#ifndef MYTINYSTL_UNINITIALIZED_H_
#define MYTINYSTL_UNINITIALIZED_H_

// 这个头文件用于对未初始化空间构造元素

#include "algobase.h"
#include "construct.h"
#include "iterator.h"
#include "type_traits.h"
#include "util.h"

namespace mystl
{

// uninitialized_copy
// 把 [first, last) 上的内容复制到以 result 为起始处的空间，返回复制结束的位置
template <class InputIterator, class ForwardIterator>
ForwardIterator unchecked_uninit_copy(InputIterator first, InputIterator last, ForwardIterator result, std::true_type)
{
    return mystl::copy(first, last, result);
}
template <class InputIterator, class ForwardIterator>
ForwardIterator unchecked_uninit_copy(InputIterator first, InputIterator last, ForwardIterator result, std::false_type)
{
    auto cur = result;
    try
    {
        for(; first != last; ++first, ++cur)
        {
            mystl::construct(&*cur, *first);
        }
    }
    catch(...)
    {
        for(; result != cur; --cur)
        {
            mystl::destroy(&*cur);
        }
    }
    return cur;
}

template <class InputIterator, class ForwardIterator>
ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
{
    return unchecked_uninit_copy(first, last, result, std::is_trivially_copy_assignable<typename iterator_traits<ForwardIterator>::value_type>{});
}


// uninitialized_copy_n
// 把 [first, first + n) 上的内容复制到以 result 为起始处的空间，返回复制结束的位置
template <class InputIterator, class Size, class ForwardIterator>
ForwardIterator unchecked_uninit_copy_n(InputIterator first, Size n, ForwardIterator result, std::true_type)
{
    return mystl::copy_n(first, n, result).second;
}
template <class InputIterator, class Size, class ForwardIterator>
ForwardIterator unchecked_uninit_copy_n(InputIterator first, Size n, ForwardIterator result, std::false_type)
{
    auto cur = result;
    try
    {
        for(; n > 0; --n, ++first, ++cur)
        {
            mystl::construct(&*cur, *first);
        }
    }
    catch(...)
    {
        for(; result != cur; --cur)
        {
            mystl::destroy(&*cur);
        }
    }
    return cur;
}

template <class InputIterator, class Size, class ForwardIterator>
ForwardIterator uninitialized_copy_n(InputIterator first, Size n, ForwardIterator result)
{
    return unchecked_uninit_copy_n(first, n, result, std::is_trivially_copy_assignable<typename iterator_traits<ForwardIterator>::value_type>{});
}


// uninitialized_fill
// 在 [first, last) 区间内填充元素值
template <class ForwardIterator, class T>
void unchecked_uninit_fill(ForwardIterator first, ForwardIterator last, const T& value, std::true_type)
{
    mystl::fill(first, last, value);
}
template <class ForwardIterator, class T>
void unchecked_uninit_fill(ForwardIterator first, ForwardIterator last, const T& value, std::false_type)
{
    auto cur = first;
    try
    {
        for(; cur != last; ++cur)
        {
            mystl::construct(&*cur, value);
        }
    }
    catch(...)
    {
        for(; first != cur; ++first)
        {
            mystl::destroy(&*first);
        }
    }
}

template <class ForwardIterator, class T>
void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value)
{
    unchecked_uninit_fill(first, last, value, std::is_trivially_copy_assignable<typename iterator_traits<ForwardIterator>::value_type>{});
}


// uninitialized_fill_n
// 从 first 位置开始，填充 n 个元素值，返回填充结束的位置
template <class ForwardIterator, class Size, class T>
ForwardIterator unchecked_uninit_fill_n(ForwardIterator first, Size n, const T& value, std::true_type)
{
    return mystl::fill_n(first, n, value);
}
template <class ForwardIterator, class Size, class T>
ForwardIterator unchecked_uninit_fill_n(ForwardIterator first, Size n, const T& value, std::false_type)
{
    auto cur = first;
    try
    {
        for(; n > 0; --n, ++cur)
        {
            mystl::construct(&*cur, value);
        }
    }
    catch(...)
    {
        for(; first != cur; ++first)
        {
            mystl::destroy(&*first);
        }
    }
    return cur;
}

template <class ForwardIterator, class Size, class T>
ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& value)
{
    return unchecked_uninit_fill_n(first, n, value, std::is_trivially_copy_assignable<typename iterator_traits<ForwardIterator>::value_type>{});
}


// uninitialized_move
// 把[first, last)上的内容移动到以 result 为起始处的空间，返回移动结束的位置
template <class InputIterator, class ForwardIterator>
ForwardIterator unchecked_uninit_move(InputIterator first, InputIterator last, ForwardIterator result, std::true_type)
{
    return mystl::move(first, last, result);
}
template <class InputIterator, class ForwardIterator>
ForwardIterator unchecked_uninit_move(InputIterator first, InputIterator last, ForwardIterator result, std::false_type)
{
    ForwardIterator cur = result;
    try
    {
        for(; first != last; ++first, ++cur)
        {
            mystl::construct(&*cur, mystl::move(*first));
        }
    }
    catch(...)
    {
        mystl::destroy(result, cur);
    }
    return cur;
}

template <class InputIterator, class ForwardIterator>
ForwardIterator uninitialized_move(InputIterator first, InputIterator last, ForwardIterator result)
{
    return unchecked_uninit_move(first, last, result, std::is_trivially_move_assignable<typename iterator_traits<InputIterator>::value_type>{});
}


// uninitialized_move_n
// 把[first, first + n)上的内容移动到以 result 为起始处的空间，返回移动结束的位置
template <class InputIterator, class Size, class ForwardIterator>
ForwardIterator unchecked_uninit_move_n(InputIterator first, Size n, ForwardIterator result, std::true_type)
{
    return mystl::move(first, first + n, result);
}
template <class InputIterator, class Size, class ForwardIterator>
ForwardIterator unchecked_uninit_move_n(InputIterator first, Size n, ForwardIterator result, std::false_type)
{
    auto cur = result;
    try
    {
        for(; n > 0; --n, ++first, ++cur)
        {
            mystl::construct(&*cur, mystl::move(*first));
        }
    }
    catch(...)
    {
        for(; result != cur; ++result)
        {
            mystl::destroy(&*result);
        }
        throw;
    }
    return cur;
}

template <class InputIterator, class Size, class ForwardIterator>
ForwardIterator uninitialized_move_n(InputIterator first, Size n, ForwardIterator result)
{
    return unchecked_uninit_move_n(first, n, result, std::is_trivially_move_assignable<typename iterator_traits<InputIterator>::value_type>{});
}

} // namespace mystl

#endif // !MYTINYSTL_UNINITIALIZED_H_