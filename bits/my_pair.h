#ifndef _MY_PAIR_H_
#define _MY_PAIR_H_
#include "my_utility.h"
namespace my {

template<class T1, class T2>
class pair{
public:
    typedef T1 first_type;
    typedef T2 second_type;

    pair()
    :first(), second() {}

    pair(const T1& t1, const T2& t2)
    :first(t1), second(t2) {}

    pair(const pair<T1, T2>& _p)
    :first(_p.first), second(_p.second) {}

    void swap(pair<T1, T2>& a) {
        my::swap(this->first, a.first);
        my::swap(this->second, a.second);
    }

    pair<T1, T2>& operator= (const pair<T1, T2>& _p) {
        first = _p.first;
        second = _p.second;
        return *this;
    }

    first_type  first;
    second_type second;
};  // class pair

template <class T1, class T2>
void swap(pair<T1, T2>& t1, pair<T1, T2>& t2) {
    t1.swap(t2);
}

template <class T1, class T2>
inline pair<T1, T2>
make_pair(T1 t1, T2 t2) {
    return pair<T1, T2>(t1, t2);
}

}//namespace my
#endif //__MY_PAIR_H_
