#include "gtest/gtest.h"
#include "my_functional.h"
using namespace my;

TEST(less, 0) {
    my::less<int> a;
    EXPECT_TRUE( a(1,2) );
}

