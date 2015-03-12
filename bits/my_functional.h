#ifndef _MY_FUNCTIONAL_H_
#define _MY_FUNCTIONAL_H_
namespace my {

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

}
#endif
