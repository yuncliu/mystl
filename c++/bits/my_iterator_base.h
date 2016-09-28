#ifndef MY_ITERATOR_BASE_H_
#define MY_ITERATOR_BASE_H_

namespace my {

/**
 * @defgroup iterator_tags Iterator Tags
 * @{
 */
///  Marking input iterators.
struct input_iterator_tag { };

///  Marking output iterators.
struct output_iterator_tag { };

/// Forward iterators support a superset of input iterator operations.
struct forward_iterator_tag : public input_iterator_tag { };

/// Bidirectional iterators support a superset of forward iterator
/// operations.
struct bidirectional_iterator_tag : public forward_iterator_tag { };

/// Random-access iterators support a superset of bidirectional
/// iterator operations.
struct random_access_iterator_tag : public bidirectional_iterator_tag { };

 // @}

template<typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
    typename _Pointer = _Tp*, typename _Reference = _Tp&>
struct iterator
{
    /// One of the @link iterator_tags tag types@endlink.
    typedef _Category  iterator_category;
    /// The type "pointed to" by the iterator.
    typedef _Tp        value_type;
    /// Distance between iterators is represented as this type.
    typedef _Distance  difference_type;
    /// This type represents a pointer-to-value_type.
    typedef _Pointer   pointer;
    /// This type represents a reference-to-value_type.
    typedef _Reference reference;
};

} // end namespace

#endif // MY_ITERATOR_BASE_H_
