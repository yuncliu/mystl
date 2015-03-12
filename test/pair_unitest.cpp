#include "gtest/gtest.h"
#include "my_pair.h"
using namespace my;

TEST(pair, 0) {
    my::pair<int, int> a = pair<int, int>(1,1);
    EXPECT_TRUE( 1 == a.first);
    EXPECT_TRUE( 1 == a.second);
}

TEST(pair, swap) {
    my::pair<int, int> a = pair<int, int>(1,1);
    my::pair<int, int> b = pair<int, int>(2,2);
    a.swap(b);
    EXPECT_TRUE( 2 == a.first);
    EXPECT_TRUE( 1 == b.first);
}

TEST(pair, swap2) {
    my::pair<int, int> a = pair<int, int>(1,1);
    my::pair<int, int> b = pair<int, int>(2,2);
    my::swap(a, b);
    EXPECT_TRUE( 2 == a.first);
    EXPECT_TRUE( 1 == b.first);
}

TEST(pair, make_pair) {
    my::pair<int, int> a = make_pair<int, int>(1,1);
    EXPECT_TRUE( 1 == a.first);
    EXPECT_TRUE( 1 == a.second);
}
