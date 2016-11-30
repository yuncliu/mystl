#include "gtest/gtest.h"
#include <myvector>

TEST(vector, push_back) {
    my::vector<int> m;
    m.push_back(1);
    EXPECT_EQ( (unsigned)1, m.capacity());
    EXPECT_EQ( (unsigned)1, m.size());
    m.push_back(2);
    EXPECT_EQ( (unsigned)2, m.capacity());
    EXPECT_EQ( (unsigned)2, m.size());
    m.push_back(3);
    EXPECT_EQ( (unsigned)4, m.capacity());
    EXPECT_EQ( (unsigned)3, m.size());

    EXPECT_EQ( 1, m.data()[0]);
    EXPECT_EQ( 2, m.data()[1]);
    EXPECT_EQ( 3, m.data()[2]);

    EXPECT_EQ( 1, m[0]);
    EXPECT_EQ( 2, m[1]);
    EXPECT_EQ( 3, m[2]);
}

TEST(vector, iter) {
    my::vector<int> m;
    m.push_back(1);
    m.push_back(2);
    m.push_back(3);
    my::vector<int>::iterator it;
    int i = 1;
    for (it = m.begin(); it != m.end(); ++it) {
       printf("%d\n", *it);
       EXPECT_EQ( i, *it);
       i++;
    }
}

class P {
    public:
        P(int i) {
            p = (int*)malloc(sizeof(int));
            *p = i;
        }
        P(const P& x) {
            p = (int*)malloc(sizeof(int));
            *p = *(x.p);
        }
        ~P() {
            free(p);
        }
        int *p;
};

TEST(vector, Point) {
    my::vector<P> m;
    for (int i = 0; i < 100; ++i) {
        P t(i);
        m.push_back(t);
    }
    for (int i = 0; i < 100; ++i) {
       EXPECT_EQ( i, *(m[i].p));
    }
}
