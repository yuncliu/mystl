#include "gtest/gtest.h"
#include <myvector>

TEST(vector, push_back) {
    my::vector<int> m;
    m.push_back(1);
    m.push_back(2);
    m.push_back(3);
    EXPECT_TRUE( 3 == m.size());
    EXPECT_EQ( 1 , m.data()[0]);
    EXPECT_EQ( 2 , m.data()[1]);
    EXPECT_EQ( 3 , m.data()[2]);

    EXPECT_EQ( 1 , m[0]);
    EXPECT_EQ( 2 , m[1]);
    EXPECT_EQ( 3 , m[2]);
}
