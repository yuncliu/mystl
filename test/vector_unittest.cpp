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
