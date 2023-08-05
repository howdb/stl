#ifndef MYTINYSTL_SET_H_
#define MYTINYSTL_SET_H_

// 这个头文件包含两个模板类 set 和 multiset
// set      : 集合，键值即实值，集合内元素会自动排序，键值不允许重复
// multiset : 集合，键值即实值，集合内元素会自动排序，键值允许重复

// notes:
//
// 异常保证：
// mystl::set<Key> / mystl::multiset<Key> 满足基本异常保证，对以下等函数做强异常安全保证：
//   * emplace
//   * emplace_hint
//   * insert

#include "rb_tree.h"

namespace mystl
{

// 模板类 set，键值不允许重复
// 参数一代表键值类型，参数二代表键值比较方式，缺省使用 mystl::less 
template <typename Key, typename Compare = mystl::less<Key>>
class set
{
public:
    typedef Key      key_type;
    typedef Key      value_type;
    typedef Compare  key_compare;
    typedef Compare  value_compare;

private:
    // 以 mystl::rb_tree 作为底层机制
    typedef mystl::rb_tree<value_type, key_compare> base_type;
    base_type tree_;

public:
    // 使用 rb_tree 定义的型别
    typedef typename base_type::node_type               node_type;
    typedef typename base_type::const_pointer           pointer;
    typedef typename base_type::const_pointer           const_pointer;
    typedef typename base_type::const_reference         reference;
    typedef typename base_type::const_reference         const_reference;
    typedef typename base_type::const_iterator          iterator;
    typedef typename base_type::const_iterator          const_iterator;
    typedef typename base_type::const_reverse_iterator  reverse_iterator;
    typedef typename base_type::const_reverse_iterator  const_reverse_iterator;
    typedef typename base_type::size_type               size_type;
    typedef typename base_type::difference_type         difference_type;
    typedef typename base_type::allocator_type          allocator_type;

public:
    // 构造、复制、移动函数
    set() = default();

    template <typename InputIterator>
    set(InputIterator first, InputIterator last) : tree_()
    {
        tree_.insert_unique(first, last);
    }
    set(std::initializer_list<value_type> ilist) : tree_()
    {
        tree_.insert_unique(ilist.begin(), ilist.end());
    }

    set(const set& rhs) : tree_(rhs.tree_) {}
    set(set&& rhs) : tree_(mystl::move(rhs.tree_));
};

}

#endif