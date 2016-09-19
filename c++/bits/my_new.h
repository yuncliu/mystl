#ifndef _MY_NEW_H_
#define _MY_NEW_H_
#include <stddef.h> // size_t

//for gtest
#ifdef TEST
#define PRIVATE public
#else
#define PRIVATE private
#endif

void* operator new(size_t size);
void operator delete(void* p);

#endif // _MY_NEW_H_
