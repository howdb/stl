#ifndef MYTINYSTL_MAP_H_
#define MYTINYSTL_MAP_H_

// 这个头文件包含了两个模板类 map 和 multimap
// map      : 映射，元素具有键值和实值，会根据键值大小自动排序，键值不允许重复
// multimap : 映射，元素具有键值和实值，会根据键值大小自动排序，键值允许重复

// notes:
//
// 异常保证：
// mystl::map<Key, T> / mystl::multimap<Key, T> 满足基本异常保证，对以下等函数做强异常安全保证：
//   * emplace
//   * emplace_hint
//   * insert

#include "rb_tree.h"

namespace mystl
{

template <typename Key, typename T, typename Compare = mystl::less<Key>>
class map
{
public:
    typedef Key                       Key_type;
    typedef T                         mapped_type;
    typedef mystl::pair<const Key, T> value_type;
    typedef Compare                   key_compare;

class value_compare : public binary_function <value_type, value_type, bool>
{
    friend class map<Key, T, Compare>;
private:
    Compare comp;
    value_compare(Compare c) : comp(c) {}
public:
    bool operator()(const value_type& lhs, const value_type& rhs) const
    {
        return comp(lhs.first, rhs.first);  // 比较键值的大小
    }
};

private:
    // 以 mystl::rb_tree 作为底层机制
    typedef mystl::rb_tree<value_type, key_compare> base_type;
    base_type tree_;

public:
    // 使用 rb_tree 定义的型别
    typedef typename base_type::node_type              node_type;
    typedef typename base_type::pointer                pointer;
    typedef typename base_type::const_pointer          const_pointer;
    typedef typename base_type::reference              reference;
    typedef typename base_type::const_reference        const_reference;
    typedef typename base_type::iterator               iterator;
    typedef typename base_type::const_iterator         const_iterator;
    typedef typename base_type::reverse_iterator       reverse_iterator;
    typedef typename base_type::const_reverse_iterator const_reverse_iterator;
    typedef typename base_type::size_type              size_type;
    typedef typename base_type::difference_type        difference_type;
    typedef typename base_type::allocator_type         allocator_type;




};

}

#endif