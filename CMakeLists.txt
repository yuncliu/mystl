cmake_minimum_required(VERSION 2.8)
project(mystl)

INCLUDE_DIRECTORIES(
    ./
    ./bits/
    $ENV{C_INCLUDE_PATH}
    /home/liu/software/gtest-1.7.0/include
)
link_directories(
/home/liu/software/gtest-1.7.0/lib/.libs/
)
set(SOURCE_LIST
test/pair_unitest.cpp
test/functional_unitest.cpp
test/rbtree_unitest.cpp
test/map_unitest.cpp
main.cpp
)

add_executable(a.out ${SOURCE_LIST})
target_link_libraries(a.out gtest)
target_link_libraries(a.out pthread)
