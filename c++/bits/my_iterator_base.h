#ifndef MY_ITERATOR_BASE_H_
#define MY_ITERATOR_BASE_H_

namespace my {

template <class _Tp, class _Distance = ptrdiff_t,
          class _Pointer = _Tp*, class _Reference = _Tp&>
struct iterator {
  typedef _Tp        value_type;
  typedef _Distance  difference_type;
  typedef _Pointer   pointer;
  typedef _Reference reference;
};

template <class _Iterator>
struct iterator_traits {
  typedef typename _Iterator::value_type        value_type;
  typedef typename _Iterator::difference_type   difference_type;
  typedef typename _Iterator::pointer           pointer;
  typedef typename _Iterator::reference         reference;
};

template <class _TP>
struct iterator_traits<_TP*> {
  typedef _TP          value_type;
  typedef ptrdiff_t    difference_type;
  typedef _TP*         pointer;
  typedef _TP&         reference;
};

} // end namespace

#endif // MY_ITERATOR_BASE_H_
