#ifndef MY_VECTOR_H
#define MY_VECTOR_H 1

#include "my_allo.h"
#include "my_utility.h"
#include "my_construct.h"
#include <string.h>

namespace my {

template<class _TP, class _Alloc>
class vector_base {
public:
    typedef _Alloc  allocator_type;

    vector_base(const allocator_type& alloc)
    :_head(NULL), _tail(NULL), _end_of_storage(NULL) {}

    vector_base(size_t __n, const allocator_type& alloc)
    :_head(NULL), _tail(NULL), _end_of_storage(NULL) {
        _head = _allocate(__n);
        _tail = _head;
        _end_of_storage = _head + __n;
    }

    ~vector_base() {
        _deallocate(_head, _end_of_storage - _head);
    }

    allocator_type get_alloctor() {
        return allocator_type();
    }
protected:
    _TP* _head;
    _TP* _tail;
    _TP* _end_of_storage;
    typedef simple_alloc<_TP, _Alloc> _data_alloctor;
    _TP* _allocate(size_t __n) {
        return _data_alloctor::allocate(__n);
    }
    void _deallocate(_TP* __p, size_t __n) {
        return _data_alloctor::deallocate(__p, __n);
    }
};

/**
 * @brief vector
 */
template<class _TP, class _Alloc = my_allocator<_TP> >
class vector : protected vector_base<_TP, _Alloc> {
private:
    typedef vector_base<_TP, _Alloc> _base;
public:
    typedef _TP                 value_type;
    typedef value_type*         pointer;
    typedef const value_type*   const_pointer;
    typedef value_type*         iterator;
    typedef const value_type*   const_iterator;
    typedef ptrdiff_t           difference_type;
    typedef typename _base::allocator_type      allocator_type;
    typedef typename allocator_type::size_type  size_type;

    allocator_type get_allocator() const {
        return _base::get_allocator();
    }

protected:

    using _base::_allocate;
    using _base::_deallocate;
    using _base::_head;
    using _base::_tail;
    using _base::_end_of_storage;

    void _insert_aux(iterator pos, const _TP& __x);

public:
    explicit vector(const allocator_type& __a = allocator_type())
    :_base(__a) {}

    explicit vector(const size_type __n)
    :_base(__n, allocator_type()) {
    }

    vector(const vector&) {
    }

    vector(const vector&&) {
    }

    ~vector() {
        destroy(_head, _tail);
    }

    iterator begin() {
        return _head;
    }

    iterator end() {
        return _tail;
    }

    void push_back(const _TP& __x) {
        if (_tail != _end_of_storage) {
            //new ((void*)_tail) T(__x);
            construct(_tail, __x);
            _tail++;
        }
        else {
            _insert_aux(_tail, __x);
        }
    }

    size_type size() const {
        return size_type(_tail - _head);
    }

    value_type*  data() const {
        return _head;
    }

    value_type& font() const {
        return _head[0];
    }

    value_type& operator[] (int idx) const {
        return _head[idx];
    }

    size_type capacity() const {
        return size_type(_end_of_storage - _head);
    }
};

template<class _TP, class _Alloc>
void vector<_TP, _Alloc>::_insert_aux(iterator pos, const _TP& __x) {
    if(pos != _end_of_storage) {
        printf("not support now\n");
    } else {
        const size_type __old_size = size();
        const size_type __len = __old_size != 0 ? 2 * __old_size : 1;
        iterator __new_head = _allocate(__len);
        iterator __new_tail = __new_head;
        memcpy(__new_head, _head, (_tail - _head)*sizeof(_TP));
        __new_tail += _tail - _head;

        construct(__new_tail, __x);
        __new_tail++;

        destroy(begin(), end()); //all destructor of elements in old position
        _deallocate(_head, _end_of_storage - _head);
        _head = __new_head;
        _tail = __new_tail;
        _end_of_storage = __new_head + __len;
    }
}

} // end namespace

#endif
