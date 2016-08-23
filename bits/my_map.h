#ifndef _MY_MAP_H_
#define _MY_MAP_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_rbtree.h"
#include "my_allo.h"

//for gtest
#ifdef TEST
#define PRIVATE public
#else
#define PRIVATE private
#endif

namespace my{

template<typename Key, typename Val, typename Compare = my::less<Key> >
class pair_compare {
public:
    typedef my::pair<Key, Val> pair_type;
    bool operator() (const pair_type& t1, const pair_type& t2) const {
        return _less(t1.first, t2.first);
    }
    PRIVATE:
    Compare _less;
};

//template<typename _Key, typename _Val, typename _Compare = my::pair_compare<_Key, _Val>, 
template<typename Key, typename Val, typename Compare = my::less<Key>,
    typename Allocator = my::my_allocator<my::pair<Key, Val> > >
class map {
public:
    typedef Key key_type;
    typedef Val value_type;
    typedef Val maped_type;
    typedef my::pair<key_type, value_type> pair_type;
    typedef Allocator allocator_type;

    typedef pair_compare<Key, Val, Compare> pair_compare_type;

    typedef my::RBTree<pair_type, pair_compare_type, allocator_type> tree_type;

    typedef typename tree_type::iterator iterator;
    typedef typename tree_type::const_iterator const_iterator;
    typedef typename tree_type::size_type size_type;

    typedef typename my::map<key_type, value_type, Compare, allocator_type> self_type;

    map() {
    }

    map(const self_type& m): _tree(m._tree) {
    }

    ~map() {
    }

    size_type size() {
        return _tree.size();
    }

    pair<iterator, bool> insert(pair_type p) {
        return _tree.insert(p);
    }

    void erase(iterator it) {
        _tree.erase(it);
    }

    void erase(iterator start, iterator end) {
        iterator tmp;
        for(;start != end; ) {
            tmp = start;
            start++;
            this->erase(tmp);
        }
    }

    iterator find(key_type key) {
        value_type v;
        memset(&v, 0x00, sizeof(value_type));
        pair_type key_pair = make_pair(key, v);
        return _tree.find(key_pair);
    }

    const_iterator find(key_type key) const {
        value_type v;
        memset(&v, 0x00, sizeof(value_type));
        pair_type key_pair = make_pair(key, v);
        return const_iterator(_tree.find(key_pair));
    }

    iterator begin() {
        return _tree.begin();
    }

    const_iterator begin() const {
        return _tree.begin();
    }

    iterator end() {
        return _tree.end();
    }

    const_iterator end() const {
        return _tree.end();
    }

    void clear() {
        _tree.clear();
    }

    bool empty() {
        return 0 == _tree.size();
    }

    self_type& operator=(self_type& m) {
        this->clear();
        _tree = m._tree;
        return *this;
    }

    self_type& operator=(self_type&& m) {
        this->clear();
        _tree = std::move(m._tree);
        return *this;
    }

    self_type& operator=(const self_type& m) {
        this->clear();
        _tree = m._tree;
        return *this;
    }

    self_type& operator=(const self_type&& m) {
        this->clear();
        _tree = std::move(m._tree);
        return *this;
    }

    value_type& operator[](key_type key) {
        iterator it = this->find(key);
        if ( it == _tree.end())
        {
            value_type v;
            memset(&v, 0x00, sizeof(value_type));
            my::pair<iterator, bool> itt = this->insert(pair_type(key, v));
            it = itt.first;
        }
        return it->second;
    }

PRIVATE:
    tree_type _tree;
};

}
#endif // _MY_MAP_H_
