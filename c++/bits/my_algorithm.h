#ifndef MY_ALGORITHM_H_

#define MY_ALGORITHM_H_

#include "my_utility.h"

namespace my {

/*
template<class _RandomAccessIterator, class _Compare>
sort(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp) {
}

sort_r(_RandomAccessIterator __first, _RandomAccessIterator __last, _Compare __comp) {
    if (__first  != __last) {
        int j  = quick_sort_partion(array, start, end);
        quick_sort_r(array, start, j - 1);
        quick_sort_r(array, j + 1, end);
    }
}
*/

/**
 * @brief partion the array
 */
int* quick_sort_partion(int* __first, int* __last) {
    int pivot   = *__first;
    int* i      = __first;
    int* j      = __last;

    while (1) {
        do ++i; while ( *i <= pivot && i <= __last );
        // here i points to the fist element which bigger than pivot
        do --j; while ( *j > pivot );
        // here j points to the last element which samller or equal than pivot
        if( i >= j ) break;
        // because j is smaller and i is bigger, swap them
        my::swap(*i, *j);
    }

    my::swap(*__first, *j);

    return j;
}

/**
 * @brief sort
 * a[4] = {2,1,4,3}, then sort(a[0], a[4]); the second sould be an sentinel position
 * like container.end();
 */
void sort(int* __first, int* __last) {
    if (__first < __last) {
        // make the array in to two part on both side of the pivot
        // all elements in the left side is smaller or equal to pivot
        // all elements in the right side is bigger than pivot
        int* pivot = quick_sort_partion(__first, __last);
        // sort again on the left side
        sort(__first, pivot);
        // sort again on the right side
        sort(pivot + 1, __last);
    }
}

} // namespace my

#endif // MY_ALGORITHM_H_
