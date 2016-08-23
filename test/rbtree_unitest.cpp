#include "gtest/gtest.h"
#include "mymap"
#include "myutility"

TEST(rb_tree, 0) {
    my::RBTree<int> a;
    EXPECT_TRUE( 0 == a.size());
}

TEST(rb_tree, 1) {
    my::RBTree<int> a;
    for (int i = 0; i<100; ++i)
    {
        a.insert(i);
    }

    for (int i = 0; i<100; ++i)
    {
        //a.erase(i);
        //EXPECT_TRUE( (unsigned int)(99-i) == a.size());
        my::RBTree<int>::iterator it = a.find(i);
        EXPECT_TRUE( i == *it);
        a.erase(it);
        EXPECT_TRUE( a.find(i) == a.end());
    }
}

TEST(rb_tree, 2) {
    my::RBTree<int> a;
    for (int i = 0; i<100; ++i)
    {
        a.insert(i);
    }
    my::RBTree<int>::iterator it = a.begin();
    EXPECT_TRUE( 0 == *it);
    it++;
    EXPECT_TRUE( 1 == *it);
    it++;
    EXPECT_TRUE( 2 == *it);

    my::RBTree<int>::iterator itt = a.begin();
    for (int i = 0;itt != a.end(); itt++) {
        EXPECT_TRUE( i ==  *itt);
        if (i == 50)
        {
            my::RBTree<int>::iterator it1 = itt;
            it1--;
            EXPECT_TRUE( 49 ==  *it1);
        }
        i++;
    }
}

TEST(rb_tree, insert_return_pair1) {
    my::RBTree<int> a;
    my::pair<my::RBTree<int>::iterator, bool> i1 = a.insert(1);

    EXPECT_TRUE( 1 ==  *i1.first);
    EXPECT_TRUE( i1.second);

    my::pair<my::RBTree<int>::iterator, bool> i2 = a.insert(2);
    EXPECT_TRUE( 2 ==  *i2.first);
    EXPECT_TRUE( i2.second);

    my::pair<my::RBTree<int>::iterator, bool> i3 = a.insert(2);
    EXPECT_TRUE( 2 ==  *i3.first);
    EXPECT_TRUE( false == i3.second);
}

TEST(rb_tree, insert_return_pair2) {
    int max = 100000;
    int failure = 0;
    srand(time(NULL));
    my::RBTree<int> a;
    my::pair<my::RBTree<int>::iterator, bool> r;
    for (int i = 0; i<max; ++i)
    {
        int x = rand()%100000;
        r = a.insert(x);
        if (!r.second)
        {
            failure++;
        }
    }
    EXPECT_TRUE( max - failure == (int)a.size());
    a.clear();
    EXPECT_TRUE( 0 == a.size());
}

TEST(rb_tree, get_value_from_iterator) {
    my::RBTree<int> a;
    for (int i = 0; i<100; ++i)
    {
        a.insert(i);
    }
    my::RBTree<int>::iterator it = a.begin();
    for (int i = 0;it != a.end(); ++it) {
        EXPECT_TRUE( i ==  *it);
        i++;
    }
}

TEST(rb_tree, const_iterator1) {
    my::RBTree<int> a;
    for (int i = 0; i<100; ++i)
    {
        a.insert(i);
    }

    my::RBTree<int>::const_iterator it = a.begin();
    for (int i = 0;it != a.end(); ++it) {
        EXPECT_TRUE( i ==  *it);
//        (*it)++;
        i++;
    }
    it = a.begin();
    my::RBTree<int>::iterator itt = a.begin();
    for (int i = 0; i<100; ++i)
    {
        EXPECT_TRUE( it ==  itt);
        it++;
        EXPECT_TRUE( it !=  itt);
        itt++;
    }
}

TEST(rb_tree, const_iterator2) {
    my::RBTree<int> a;
    for (int i = 0; i<100; ++i)
    {
        a.insert(i);
    }
    my::RBTree<int>::const_iterator it = a.find(10);
    EXPECT_TRUE( 10 ==  *it);
}

TEST(rb_tree, prefix_and_suffix) {
    my::RBTree<int> a;
    for (int i = 0; i<100; ++i)
    {
        a.insert(i);
    }
    my::RBTree<int>::iterator it = a.begin();
    my::RBTree<int>::iterator it1 = it++;
    EXPECT_TRUE( it1 == a.begin());
    my::RBTree<int>::iterator it2 = it;
    it2++;
    my::RBTree<int>::iterator it3 = ++it;
    EXPECT_TRUE( it2 == it3);

    it++;
    it++;
    it++;

    my::RBTree<int>::iterator it4 = it;
    my::RBTree<int>::iterator it5 = it--;
    EXPECT_TRUE( it4 == it5);

    my::RBTree<int>::iterator it6 = --it4;
    EXPECT_TRUE( it == it6);
}

TEST(rb_tree, std_move) {
    my::RBTree<int> a;
    for (int i = 0; i<100; ++i)
    {
        a.insert(i);
    }
    my::RBTree<int> b;
    b = std::move(a);
    my::RBTree<int>::const_iterator it = b.find(10);
    EXPECT_TRUE( *it == 10);
    EXPECT_TRUE( a._root == NULL);
}
