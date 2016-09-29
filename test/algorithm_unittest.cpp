#include "gtest/gtest.h"
#include <myalgorithm>

TEST(algorithm, array) {
    int a[4] = {2,1,4,3};
    my::sort(&a[0], &a[3]);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
    EXPECT_EQ(a[2], 3);
    EXPECT_EQ(a[3], 4);
}

TEST(algorithm, array1) {
    int a[100];
    for (int i = 0; i < 100; ++i) {
        a[i] = 100 - i - 1;
    }

    my::sort(&a[0], &a[99]);

    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(a[i], i);
    }
}
