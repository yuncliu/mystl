#ifndef _MY_CONSTRUCT_H_
#define _MY_CONSTRUCT_H_

namespace my {

template<class _TP>
void destroy(_TP* __pointer) {
    __pointer->~TP();
}

void destroy(int* __pointer) {
}

template<class _TP>
void destroy(_TP* __head, _TP* __tail) {
    for (_TP* __t = __head; __t != __tail; ++__t) {
        destroy(__t);
    }
}

template<class _TP>
void construct(_TP* __p, const _TP& __x) {
    new ((void*)__p) _TP(__x);
}

}

#endif // _MY_CONSTRUCT_H_
