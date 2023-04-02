//
// Created by HP on 17-Oct-22.
//

#ifndef UNTITLED7_ASSIGNMENT_H
#define UNTITLED7_ASSIGNMENT_H

#include <iterator>

namespace task_1 {
    template<typename SomeType>
    SomeType greater_than(SomeType t, SomeType u) {
        if (t > u) return true;
        return false;
    }
    template<typename SomeType>
    SomeType less_than(SomeType t, SomeType u) {
        if (t < u) return true;
        return false;
    }
    template<typename SomeType>
    SomeType compare(SomeType t, SomeType u) {
        if (t == u) return 0;
        else if (t > u) return 1;
        else return -1;
    }

}

namespace task_2 {
    template <std::size_t SZ, typename T >
    T sum(T* array, T init = T{} ){
        for (auto i=0; i< SZ; i++){
            init += array[i];
        }
        return init;
    }
}

namespace task_3 {
    template <std::size_t SZ, typename T >
    T sum(T (&array)[SZ], T init = T{} ){
        for (auto i=0; i< SZ; i++){
            init += array[i];
        }
        return init;
    }
}


namespace task_4 {

    template <typename Container>
    auto sum(const Container& cont, typename Container::value_type init){
        for (auto value: cont){
            init += value;
        }
        return init;
    }

}

namespace task_5_1{
    template <typename Iterator, typename T>
    T sum(Iterator begin, Iterator end, T init = T{}){
        using IterValue = typename std::iterator_traits<Iterator>::value_type;
        for (auto i=begin; i<end; i++){
            init += *i;

        }

        return init;
    }

}

namespace task_5_2{
    template <typename Iterator, typename T>

    T sum(Iterator begin, Iterator end, T init = T{}){
        using IterValue = typename std::iterator_traits<Iterator>::value_type;
        static_assert(std::is_same_v<T, IterValue>, "init should be same type as the container");
        for (auto i=begin; i<end; i++){
            init += *i;

        }

        return init;
    }
}

namespace task_6{
    template <typename Iterator>
    auto sum(Iterator begin, Iterator end, typename Iterator::value_type init){
        using IterValue = typename std::iterator_traits<Iterator>::value_type;
        for (auto i=begin; i<end; i++){
            init += *i;

        }

        return init;
    }
}

#endif //UNTITLED7_ASSIGNMENT_H

