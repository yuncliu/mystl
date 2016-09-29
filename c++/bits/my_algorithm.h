#ifndef MY_ALGORITHM_H_

#define MY_ALGORITHM_H_

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
int* quick_sort_partion(int* __first, int* __last);

void sort(int* __first, int* __last) {
    if (__first < __last) {
        int* j = quick_sort_partion(__first, __last);
        sort(__first, j-1);
        sort(j+1, __last);
    }
}

int* quick_sort_partion(int* __first, int* __last) {
    int pivot;
    int* i;
    int* j;
    int tmp;
    pivot = *__first;
    i = __first;
    j = __last + 1;

    while(1) {
        do ++i; while( *i <= pivot && i <= __last );
        do --j; while( *j > pivot );
        if( i >= j ) break;
        tmp = *i; *i = *j; *j = tmp;
    }
    tmp = *__first;
    *__first = *j;
    *j = tmp;
    return j;
}

}

#endif // MY_ALGORITHM_H_
