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
#if __cplusplus >= 201103L
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
#endif
/**
 *    *  @addtogroup utilities
 *    *  @{
 *    */

/**
 *  @brief Swaps two values.
 *  @param  __a  A thing of arbitrary type.
 *  @param  __b  Another thing of arbitrary type.
 *  @return   Nothing.
 */
template<typename _Tp>
inline void swap(_Tp& _a, _Tp& _b) {
    _Tp _tmp = _a;
    _a = _b;
    _b = _tmp;
}

/**
 * @breif base class binary_function
 */
template <class Arg1, class Arg2, class Result>
class binary_function {
public:
    typedef Arg1    first_argument_type;
    typedef Arg2    second_argument_type;
    typedef Result  result_type;
};

/**
 * @breif less
 */
template<typename _T>
class less : public my::binary_function<_T, _T, bool> {
public:
    bool operator() (const _T& t1, const _T& t2) const {
        return t1 < t2;
    }
};

}// end namespace my
#endif
