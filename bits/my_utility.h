#ifndef _MY_UTILITY_H_
#define _MY_UTILITY_H_
namespace my {

    template<class T>
    struct remove_reference {
        typedef T type;
    };

    template<class T>
    struct remove_reference<T&> {
        typedef T type;
    };

    template<class T>
    struct remove_reference<T&&> {
        typedef T type;
    };
    // not correct now
    template<class T>
    typename remove_reference<T>::type&&
    move(T&& t) {
        typedef typename remove_reference<T>::type UP;
        return static_cast<UP&&>(t);
    }

}
#endif
