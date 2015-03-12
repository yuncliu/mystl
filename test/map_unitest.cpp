#include "gtest/gtest.h"
#include "map"
#include <map>
#include <algorithm>

TEST(map, insert) {
    my::map<int ,int> m;
    EXPECT_TRUE(m.empty());
    EXPECT_TRUE( 0 == m.size());
    m.insert(my::pair<int, int>(1,1));
    EXPECT_TRUE( 1 == m.size());
}

TEST(map, insert_and_find) {
    my::map<int ,int> m;
    EXPECT_TRUE(m.empty());
    for (int i = 0; i < 100; ++i) {
        m.insert(my::pair<int, int>(i, i*2));
    }

    my::map<int ,int>::iterator it;

    for (int i = 0; i < 100; ++i) {
        it = m.find(i);
        EXPECT_TRUE( it->second == 2*i);
    }
}

TEST(map, iterator) {
    my::map<int ,int> m;
    for (int i = 0; i < 100; ++i) {
        m.insert(my::pair<int, int>(i, i*2));
    }

    my::map<int ,int>::iterator it;

    for (int i = 0; i < 100; ++i) {
        it = m.find(i);
        EXPECT_TRUE( it->second == 2*i);
    }

    int i = 0;
    for (it = m.begin(); it != m.end(); it++) {
        EXPECT_TRUE( it->second == 2*i);
        i++;
    }
}

void couttt(my::pair<int, int>& a){ 
    EXPECT_TRUE(a.first*2 == a.second);
}

TEST(map, std_for_each) {
    my::map<int ,int> m;
    for (int i = 0; i < 100; ++i) {
        m.insert(my::pair<int, int>(i, i*2));
    }
    std::for_each(m.begin(), m.end(),couttt);
}

TEST(map, erase_range) {
    my::map<int ,int> m;
    for (int i = 0; i < 100; ++i) {
        m.insert(my::pair<int, int>(i, i*2));
    }
    m.erase(m.begin(), m.end());
    EXPECT_TRUE( 0 == m.size() );
}

TEST(map, operator_compare) {
    my::map<int ,int> m;
    for (int i = 0; i < 100; ++i) {
        m.insert(my::pair<int, int>(i, i*2));
    }
    my::map<int ,int> mm;
    mm = m;
    EXPECT_TRUE(mm.size() == m.size());

    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(mm.find(i)->second == i*2);
    }
}

TEST(map, operator_arrary_access) {
    my::map<int ,int> m;
    for (int i = 0; i < 100; ++i) {
        m.insert(my::pair<int, int>(i, i*2));
    }

    for (int i = 0; i < 100; ++i) {
        EXPECT_TRUE(m[i] == i*2);
    }
}

class Point {
public:
    Point():x(0), y(0) {
    }
    Point(int xx, int yy):x(xx), y(yy) {
    }
    ~Point() {
    }
    int x;
    int y;
};

class test_less {
public:
    bool operator()(const Point& a, const Point&b) const{
        return a.x > b.x;
    }
};

TEST(map, self_define_less) {
    my::map<Point, int, test_less> m;
    for (int i = 0; i<100; ++i) {
        m.insert(my::pair<Point, int>(Point(i,1), i));
    }

    my::map<Point, int, test_less>::iterator it;

    int i = 99;
    for (it = m.begin(); it != m.end(); ++it) {
        EXPECT_TRUE( it->second == i);
        i--;
    }
}

TEST(map, const_iterator) {
    my::map<Point, int, test_less> m;
    for (int i = 0; i<100; ++i) {
        m.insert(my::pair<Point, int>(Point(i,1), i));
    }

    my::map<Point, int, test_less>::const_iterator it;

    int i = 99;
    for (it = m.begin(); it != m.end(); ++it) {
        EXPECT_TRUE( it->second == i);
        //assignment of member ‘my::pair<Point, int>::second’ in read-only object
        //it->second = i;
        i--;
    }
}

TEST(map, operator_assign) {
    my::map<int, int> m;
    int&a = m[1];
    a = 10;
    m[2] = 20;
    EXPECT_TRUE( m[1] == 10);
    EXPECT_TRUE( m[2] == 20);
    m[2] = 30;
    EXPECT_TRUE( m[2] == 30);
}

TEST(map, assign) {
    my::map<int, int> m;
    m[1] = 10;
    m[2] = 20;
    m[3] = 30;
    my::map<int, int> a;
    a = m;
    a[4] = 40;
    EXPECT_TRUE( m.end() == m.find(4));

    my::map<int, int> b = m;
    b[4] = 40;
    EXPECT_TRUE( m.end() == m.find(4));
    EXPECT_TRUE( 40 == b[4]);
}

TEST(map, map_of_map) {
    my::map<int, my::map<int, int> > m;
    my::map<int, int> v;
    v.insert(my::pair<int, int>(1, 123));
    int k = 0;
    m.insert(my::pair<int, my::map<int, int> >(k, v));
    EXPECT_TRUE( 1 == m.size());

    my::map<int, my::map<int, int> >::iterator it = m.find(0);

    EXPECT_TRUE( 1 == it->second.size());

    my::map<int, int>::iterator itt = it->second.find(1);
    EXPECT_TRUE( 123 == itt->second);
}
