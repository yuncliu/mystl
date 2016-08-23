#ifndef _MY_UTILITY_H_
#define _MY_UTILITY_H_
namespace my {

    // not correct now
    template<typename T>
    T&& move(T&& t) {
        return t;
    }

}
#endif
