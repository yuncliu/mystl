#include "gtest/gtest.h"
#include <mytype_traits>

using namespace my;

TEST(type_traits, is_int) {

    EXPECT_TRUE(is_int<int>::value);
    EXPECT_FALSE(is_int<double>::value);
}
