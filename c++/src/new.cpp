#include "../bits/my_new.h"
#include <stdlib.h> // malloc and free

void* operator new(size_t size) {
    return malloc(size);
}

void operator delete(void* p) {
    free(p);
}
