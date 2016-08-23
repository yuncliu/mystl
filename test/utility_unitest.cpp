#include "gtest/gtest.h"
#include <myutility>
using namespace my;

#if __cplusplus > 201103L

class Test {
    public:
        Test(int i): p(NULL) {
            p = new int;
            *p = i;
        }

        Test(const Test& t) {
            p = new int;
            *p = *t.p;
        }

        Test(Test&& t):p(t.p) {
            t.p = NULL;
        }
        ~Test() {
            if (p!=NULL) {
                free(p);
                p = NULL;
            }
        }
        int *p;
}

Test get_rvalue() {
    return Test(10);
}

TEST(rvalue, move1) {
    Test a(100);
    Test b(my::move(a));
    EXPECT_TRUE( NULL == *a.p);
    EXPECT_TRUE( 100 == *b.p);
}

TEST(less, 0) {
    my::less<int> a;
    EXPECT_TRUE( a(1,2) );
}

#endif
