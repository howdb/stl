#include <bits/stdc++.h>
using namespace std;

namespace nstd
{

// enable_if
template <bool, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> { typedef T type; };

// iterator_traits


// template <typename T>
// struct has_iterator_cat
// {
// private:

// public:
//     static const bool value = ;
// };


// template <typename Iterator>
// struct iterator_traits_helper {};


// template <typename Iterator>
// struct iterator_traits: public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value> {};


// 编译时引用来获得数组长度
template <typename T, size_t N>
constexpr size_t array_size(T(&)[N]) noexcept
{
    return N;
}

/*
template <typename T>
using mylist = std::list<T, myalloc<T>>
mylist<int> l;

template <typename T>
struct mylist
{
    typedef std::list<T, myalloc<T>> type;
};
mylist<int>::type l;
*/




}

/*
void print()
{

}

template<typename T, typename... Args>
void print(T t, Args... args)
{
    cout << t;
    print(args...);
}
*/

/*
template<typename... Args>
void print(Args... args)
{
    int arr[] = {(cout << args, 0)...};
}
*/


int main()
{
    using namespace nstd;
    // map<string, vector<int>> mp;
    // mp.insert({"36", {1, 2}});
    // cout << mp["36"][1];
    int a=5;    
    vector<int> v{1,2,3};while(--a)v.push_back(1);cout << v.capacity();
    // cout << v.data() << ' ' << *v.data();
    // v.reserve(100);
    // cout << &*v.begin() << endl;
    // v.shrink_to_fit();
    // cout << &*v.begin() << endl;
    // auto it = copy_n(v.begin(), 1, v.end());
    // cout << *it;
    // int a[5];
    // cout << array_size(a) << endl;
    // const int a = 1;
    // auto b = a;
    // const int& c = b;
    // decltype(auto) d = c;
    // auto d = c;
    // vector<bool> bv{1, 0};
    // // cout << &c << endl << &d << endl;
    // auto a = bv[0];
    // cout << typeid(a).name();assert(nullptr == 0);
}