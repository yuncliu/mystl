#ifndef _MY_ALLOC_H_
#define _MY_ALLOC_H_
#include "my_new.h"
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

        /**
         * only allocate memory, do not call constructor
         */
        static _Tp*  allocate(size_type n, const void* hint = 0) {
            return static_cast<_Tp*>(::operator new(n * sizeof(_Tp)));
        }

        /**
         * free memeory, do not call destructor
         */
        static void  deallocate (_Tp* __p, size_type n = 0) {
            ::operator delete(__p);
        }

        template<typename _Tp1>
        struct rebind {
            typedef my_allocator<_Tp1> other;
        };

        /**
         * call constructor
         */
        void construct(pointer __p, const _Tp& __val) {
            ::new((void *)__p) _Tp(__val);
        }

        /**
         * call destructor
         */
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

template<class _Tp, class _Alloc>
class simple_alloc {
public:
    static _Tp* allocate(size_t __n)
      { return 0 == __n ? 0 : (_Tp*) _Alloc::allocate(__n * sizeof (_Tp)); }
    static _Tp* allocate(void)
      { return (_Tp*) _Alloc::allocate(sizeof (_Tp)); }
    static void deallocate(_Tp* __p, size_t __n)
      { if (0 != __n) _Alloc::deallocate(__p, __n * sizeof (_Tp)); }
    static void deallocate(_Tp* __p)
      { _Alloc::deallocate(__p, sizeof (_Tp)); }
};

}
#endif
