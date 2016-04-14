#ifndef _MY_ALLOC_H_
#define _MY_ALLOC_H_
#include <stdio.h>
namespace my{

template<typename _Tp>
class my_allocator
{
    public:
        typedef size_t     size_type;
        typedef size_t  difference_type;
        typedef _Tp*       pointer;
        typedef const _Tp* const_pointer;
        typedef _Tp&       reference;
        typedef const _Tp& const_reference;
        typedef _Tp        value_type;

        my_allocator() {
        }

        ~my_allocator() {
        }

        _Tp*  allocate(size_type n, const void* hint = 0) {
            return static_cast<_Tp*>(::operator new(n * sizeof(_Tp)));
        }

        void  deallocate (_Tp* __p, size_type n) {
            ::operator delete(__p);
        }

        template<typename _Tp1>
        struct rebind {
            typedef my_allocator<_Tp1> other;
        };

        void construct(pointer __p, const _Tp& __val) {
            ::new((void *)__p) _Tp(__val);
        }

        template<typename _Up>
        void destroy(_Up* __p) {
            __p->~_Up();
        }

        size_type max_size() const
        {
            return 10000000;
        }

    private:
};
}
#endif
