#ifndef MY_VECTOR_H
#define MY_VECTOR_H 1

#include "my_allo.h"
#include "my_utility.h"

namespace my {

template<typename T, typename Allocator = my_allocator<T> >
class vector {
    typedef T           value_type;
    typedef Allocator   allocator_type;
    typedef typename allocator_type::size_type       size_type;
public:
    vector():_data(NULL), _head(NULL), _tail(NULL), _size(0) {
        _data = _allocator.allocate(100);
        _allocated_size = 100;
        _head = _data;
        _tail = _data;
    }

    vector(const vector&) {
    }

    vector(const vector&&) {
    }

    ~vector() {
        for (size_t i = 0; i < _size; ++i) {
            _allocator.destroy(&_data[i]);
        }
        _allocator.deallocate(_data);
    }

    void push_back(const T& t) {
        if (_size <= _allocated_size) {
            _allocator.construct(_tail, t);
            _tail ++;
            _size ++;
        }
        else {
        }
    }

    size_type size() const {
        return _size;
    }

    value_type*  data() const {
        return _data;
    }

    value_type& font() const {
        return _data[0];
    }

    value_type& operator[] (int idx) const {
        return _data[idx];
    }

private:
    value_type* _data;
    value_type* _head;
    value_type* _tail;
    size_type _size;
    size_type _allocated_size;
    allocator_type _allocator;
};

} // end namespace

#endif
