#ifndef MYTINYSTL_NUMERIC_H_
#define MYTINYSTL_NUMERIC_H_

#include"iterator.h"

namespace mystl{

// accumulate
template<class InputIterator,class T>
T accumulate(InputIterator first,InputIterator last,T init){
    for(;first!=last;++first){
        init=init+*first;
    }
    return init;
}

template<class InputIterator,class T,class BinaryOperation>
T accumulate(InputIterator first,InputIterator last,T init,BinaryOperation binary_op){
    for(;first!=last;++first){
        init=binary_op(init,*first);
    }
    return init;
}


// adjacent_difference
template<class InputIterator,class OutputIterator>
OutputIterator adjacent_difference(InputIterator first,InputIterator last,OutputIterator result){
    if(first==last)return result;
    *result=*first;
    // iterator_traits<InputIterator>::value_type value=*result;
    auto value=*first;
    while(++first!=last){
        auto tmp=*first;
        *++result=tmp-value;
        value=tmp;
    }
    return ++result;
}

template<class InputIterator,class OutputIterator,class BinaryOperation>
OutputIterator adjacent_difference(InputIterator first,InputIterator last,OutputIterator result,BinaryOperation binary_op){
    if(first==last)return result;
    *result=*first;
    // iterator_traits<InputIterator>::value_type value=*result;
    auto value=*first;
    while(++first!=last){
        auto tmp=*first;
        *++result=binary_op(tmp,value);
        value=tmp;
    }
    return ++result;
}


// inner_product
template<class InputIterator1,class InputIterator2,class T>
T inner_product(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2,T init){
    for(;first1!=last1;++first1,++first2){
        init=init+(*first1 * *first2);
    }
    return init;
}

template<class InputIterator1,class InputIterator2,class T,class BinaryOperation1,class BinaryOperation2>
T inner_product(InputIterator1 first1,InputIterator1 last1,InputIterator2 first2,T init,BinaryOperation1 binary_op1,BinaryOperation2 binary_op2){
    for(;first1!=last1;++first1,++first2){
        init=binary_op1(init,binary_op2(*first1,*first2));
    }
    return init;
}


// partial_sum
template<class IunputIterator,class OutputIterator>
OutputIterator partial_sum(InputIterator first,InputIterator last,OutputIterator result){
    if(first==last)return result;
    *result=*first;
    auto value=*first;
    while(++first!=last){
        value=value+*first;
        *++result=value;
    }
    return ++result;
}

template<class IunputIterator,class OutputIterator,class BinaryOperation>
OutputIterator partial_sum(InputIterator first,InputIterator last,OutputIterator result,BinaryOperation binary_op){
    if(first==last)return result;
    *result=*first;
    auto value=*first;
    while(++first!=last){
        value=binary_op(value,*first);
        *++result=value;
    }
    return ++result;
}


// iota
template<class ForwardIterator,class T>
void iota(Forward_iterator first,ForwardIterator last,T value){
    while(first!=last){
        *first++=value++;
    }
}


// power
power

}

#endif