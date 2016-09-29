#ifndef MY_TYPE_TRAITS_H
#define MY_TYPE_TRAITS_H

namespace my {

struct __true_type{ };
struct __false_type{ };

template<class _Tp>
struct is_int {
    enum {value = 0};
    typedef __false_type __type;
};

template<>
struct is_int<int> {
    enum {value = 1};
    typedef __true_type __type;
};

}

#endif // MY_TYPE_TRAITS_H
