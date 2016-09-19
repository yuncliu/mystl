#ifndef _MY_RBTREE_H_
#define _MY_RBTREE_H_
#include "my_utility.h"
#include "my_pair.h"
#include "my_allo.h"

//#include <ext/new_allocator.h>    // for new__allocator
//for gtest
#ifdef TEST
#define PRIVATE public
#else
#define PRIVATE private
#endif

namespace my {

#define RB_RED true
#define RB_BLACK false
#define IS_LEFT(x) x == x->parent->left
#define IS_RIGHT(x) x == x->parent->right

/**
 * @class TreeNode
 * @brief data type for tree node
 */
template<typename T>
class TreeNode {
 public:
    typedef TreeNode<T> NodeType;

    TreeNode()
        :left(NULL), right(NULL), parent(NULL){
    }

    explicit TreeNode(const T& t)
        :data(t), left(NULL), right(NULL), parent(NULL) {
    }

    explicit TreeNode(const NodeType& t)
        :data(t.data), left(t.left), right(t.right), parent(t.parent){
    }

#if __cplusplus >= 201103L
    explicit TreeNode(NodeType&& t)
        :data(t.data), left(t.left), right(t.right), parent(t.parent){
    }
#endif

    ~TreeNode() {
    }

    static NodeType* maximum(TreeNode<T>* p) {
        while ( NULL !=  p->right ) {
            p = p->right;
        }
        return p;
    }

    static NodeType* maximum(const TreeNode<T>* p) {
        return TreeNode<T>::maximum(p);
    }

    static NodeType* minimum(TreeNode<T>* p) {
        while ( NULL !=  p->left ) {
            p = p->left;
        }
        return p;
    }

    static NodeType* minimum(const TreeNode<T>* p) {
        return TreeNode<T>::minimum(p);
    }

    T           data;
    NodeType*   left;
    NodeType*   right;
    NodeType*   parent;
    bool        color;
};

template<typename T>
TreeNode<T>* rbtree_increment(TreeNode<T>* p) {
    if (NULL != p->right) {
        return TreeNode<T>::minimum(p->right);
    }
    while(NULL != p->parent && IS_RIGHT(p)) {
        p = p->parent;
    }
    return p->parent;
}

template<typename T>
TreeNode<T>* rbtree_increment(const TreeNode<T>* p) {
    return rbtree_increment(p);
}

template<typename T>
TreeNode<T>* rbtree_decrement(TreeNode<T>* p) {
    if (NULL != p->left) {
        return TreeNode<T>::maximum(p->right);
    }
    while(NULL != p->parent && IS_LEFT(p)) {
        p = p->parent;
    }
    return p->parent;
}

template<typename T>
TreeNode<T>* rbtree_decrement(const TreeNode<T>* p) {
    return rbtree_decrement(p);
}

template<typename T>
class RBTree_const_iterator;

template<typename T>
class RBTree_iterator {
public:
    typedef T                           value_type;
    typedef T&                          reference;
    typedef T*                          pointer;
    typedef RBTree_iterator<T>          self_type;
    typedef RBTree_const_iterator<T>    const_iterator;
    typedef RBTree_iterator<T>*         self_pointer_type;
    typedef TreeNode<T>*                base_ptr;
    typedef TreeNode<T>*                link_type;

    RBTree_iterator(): node(NULL){
    }

    RBTree_iterator(link_type p): node(p){
    }

    RBTree_iterator(const self_type& p): node(p.node){
    }

#if __cplusplus >= 201103L
    RBTree_iterator(self_type&& p): node(p.node){
    }
#endif

    RBTree_iterator(const_iterator& p): node(p.node){
    }

    reference operator*() const {
        return node->data;
    }

    pointer operator->() const {
        return &node->data;
    }

    self_type& operator++(void) {
        node = rbtree_increment(node);
        return *this;
    }

    self_type operator++(int) {
        self_type tmp = *this;
        node = rbtree_increment(node);
        return tmp;
    }

    self_type& operator--(void) {
        node = rbtree_decrement(node);
        return *this;
    }

    self_type operator--(int) {
        self_type tmp = *this;
        node = rbtree_decrement(node);
        return tmp;
    }

    self_type& operator=(const self_type& it) {
        node = it.node;
        return *this;
    }

    self_type& operator=(const const_iterator& it) {
        node = it.node;
        return *this;
    }

    self_type& operator=(const_iterator& it) {
        node = it.node;
        return *this;
    }


    bool operator!=(self_type p) {
        return node != p.node;
    }

    bool operator==(self_type p) {
        return node == p.node;
    }

    link_type node;
};

template<typename T>
class RBTree_const_iterator {
public:
    typedef T                           value_type;
    typedef T&                          reference;
    typedef const T&                    const_reference;
    typedef T*                          pointer;
    typedef const T*                    const_pointer;
    typedef RBTree_iterator<T>          iterator;
    typedef RBTree_const_iterator<T>    self_type;
    typedef RBTree_const_iterator<T>*   self_pointer_type;
    typedef TreeNode<T>*                base_ptr;
    typedef TreeNode<T>*                link_type;

    RBTree_const_iterator(): node(NULL){
    }

    RBTree_const_iterator(const self_type& t): node(t.node){
    }

#if __cplusplus >= 201103L
    RBTree_const_iterator(self_type&& t): node(t.node){
    }
#endif

    RBTree_const_iterator(link_type p): node(p){
    }

    RBTree_const_iterator(iterator it): node(it.node){
    }

    const_reference operator*() const {
        return node->data;
    }

    const_pointer operator->() const {
        return &node->data;
    }

    self_type operator++(int) {
        self_type tmp(*this);
        node = rbtree_increment(node);
        return tmp;
    }

    self_type& operator++(void) {
        node = rbtree_increment(node);
        return *this;
    }

    self_type operator--(int) {
        self_type tmp(*this);
        node = rbtree_decrement(node);
        return tmp;
    }

    self_type& operator--(void) {
        node = rbtree_decrement(node);
        return *this;
    }

    self_type& operator=(iterator it) {
        node = it.node;
        return *this;
    }

    bool operator!=(self_type p) {
        return node != p.node;
    }

    bool operator==(self_type p) {
        return node == p.node;
    }

    link_type node;
};

template<typename T>
inline bool
operator==(const RBTree_iterator<T>& x,
const RBTree_const_iterator<T>& y) {
    return x._node == y._node;
}

template<typename T>
inline bool
operator!=(const RBTree_iterator<T>& x,
const RBTree_const_iterator<T>& y) {
    return x._node != y._node;
}

/**
 * @brief Red-Black tree
 */
template<typename T, typename Compare = my::less<T> ,
    typename Allocator = my::my_allocator<T> >
class RBTree {
 public:
    typedef typename Allocator::template rebind<TreeNode<T> >::other
           node_allocator;

    typedef typename Allocator::template rebind<T>::other allocator_type;

    typedef TreeNode<T>                     NodeType;
    typedef RBTree<T, Compare, Allocator>   self_type;
    typedef typename Allocator::size_type   size_type;
    typedef RBTree_iterator<T>              iterator;
    typedef RBTree_const_iterator<T>        const_iterator;

    RBTree(): _root(NULL), _size(0) {
    }

    RBTree(const self_type& tree): _root(NULL), _size(0) {
        const_iterator it = tree.begin();
        for(;it != tree.end();it++) {
            insert(*it);
        }
    }
#if __cplusplus >= 201103L
    /**
     * @brief move constructor;
     */
    RBTree(self_type&& tree): _root(tree._root), _size(tree._size) {
        tree._root = NULL;
        tree._size = 0;
    }
#endif

    ~RBTree() {
        delete_tree(_root);
        _root = NULL;
    }

    /**
     * @brief  insert element
     * @retval <pos, result>, result is ture when success, pos is where
     *         the new node is located
     */
    pair<iterator, bool> insert(const T& _t) {
        NodeType* p = _node_alloc.allocate(1);
        NodeType* tmp = NULL;
        _alloc.construct(&p->data, _t);

        if (NULL == p) {
            return my::make_pair(iterator(NULL), false);
        }
        tmp = rb_insert(p);
        if (tmp == p) {
            _size++;
            return my::make_pair(iterator(p), true);
        } else {
            _alloc.destroy(&p->data);
            _node_alloc.deallocate(p, 1);
            return my::make_pair(iterator(tmp), false);
        }
    }

    size_type size() {
        return _size;
    }

    void clear() {
        delete_tree(_root);
        _root = NULL;
    }

    void erase(iterator it) {
        erase_node(it.node);
    }

    iterator find(const T& _t) {
        return iterator(find_node(_t));
    }

    const_iterator find(const T& _t) const {
        return const_iterator(find_node(_t));
    }

    iterator begin() {
        return iterator(minimum(_root));
    }

    iterator end() {
        return iterator(NULL);
    }

    const_iterator begin() const {
        if (NULL == _root) {
            return const_iterator(NULL);
        }
        return const_iterator(minimum(_root));
    }

    const_iterator end() const {
        return const_iterator(NULL);
    }

    self_type& operator=(const self_type& tree) {
        this->clear();
        const_iterator it = tree.begin();
        for(;it != tree.end();it++) {
            this->insert(*it);
        }
        return *this;
    }
#if __cplusplus >= 201103L
    /**
     * @brief operator = for right value reference
     */
    self_type& operator=(self_type&& tree) {
        my::swap(this->_root, tree._root);
        my::swap(this->_size, tree._size);
        return *this;
    }
#endif

 PRIVATE:

    void left_rotate(NodeType* x) {
        NodeType* y = x->right;
        x->right = y->left;
        if (NULL != y->left) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (NULL == x->parent) {
            _root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void right_rotate(NodeType* x) {
        NodeType* y = x->left;
        x->left = y->right;
        if ( NULL != y->right ) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if ( NULL == x->parent ) {
            _root = y;
        } else if ( IS_RIGHT(x) ) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    NodeType* rb_insert(NodeType* z) {
        NodeType* tmp = z;
        NodeType* y = NULL;
        NodeType* x = _root;
        while (NULL != x) {
            y = x;
            if (_less(z->data, x->data)) {
                x = x->left;
            } else {
                if ( !_less(x->data, z->data) ) {
                    return x;
                }
                x = x->right;
            }
        }
        z->parent = y;
        if ( NULL == y ) {
            _root = z;
        } else {
            if ( _less(z->data, y->data) ) {
                y->left = z;
            } else {
                y->right = z;
            }
        }
        z->left = NULL;
        z->right = NULL;
        z->color = RB_RED;
        rb_insert_fixup(z);
        if (tmp != z) {
            abort();
        }
        return z;
    }

    void rb_insert_fixup(NodeType* z) {
        while ( NULL != z->parent &&
                z->parent->color == RB_RED &&
                NULL != z->parent->parent ) {
            if (z->parent == z->parent->parent->left) {
                NodeType* y = z->parent->parent->right;
                if (NULL != y && y->color == RB_RED) {
                    z->parent->color = RB_BLACK;
                    y->color = RB_BLACK;
                    z->parent->parent->color = RB_RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        left_rotate(z);
                    }
                    z->parent->color = RB_BLACK;
                    z->parent->parent->color = RB_RED;
                    right_rotate(z->parent->parent);
                }
            } else {
                NodeType* y = z->parent->parent->left;
                if (NULL != y && y->color == RB_RED) {
                    z->parent->color = RB_BLACK;
                    y->color = RB_BLACK;
                    z->parent->parent->color = RB_RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->color = RB_BLACK;
                    z->parent->parent->color = RB_RED;
                    left_rotate(z->parent->parent);
                }
            }
        }
        _root->color = RB_BLACK;
    }

    void rb_transplant(NodeType* u, NodeType* v) {
        if (NULL == u->parent) {
            _root = v;
        } else if ( u == u->parent->left ) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        if (NULL != v) {
            v->parent = u->parent;
        }
    }

    void erase(T _t) {
        NodeType* p = find_node(_t);
        erase_node(p);
    }

    void erase_node(NodeType* p) {
        if (NULL != p) {
            rb_delete(p);
            _alloc.destroy(&p->data);
            _node_alloc.deallocate(p, 1);
            _size--;
        }
    }

    void delete_tree(NodeType* p) {
        if (NULL == p) {
            return;
        }
        this->delete_tree(p->left);
        this->delete_tree(p->right);
        _alloc.destroy(&p->data);
        _node_alloc.deallocate(p, 1);
        _size--;
    }

    void rb_delete(NodeType* z) {
        NodeType* y = z;
        NodeType* x = NULL;
        bool y_original_color = y->color;
        if ( NULL == z->left ) {
            x = z->right;
            rb_transplant(z, z->right);
        } else if ( NULL == z->right ) {
            x = z->left;
            rb_transplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (z == y->parent) {
                if (NULL != x) {
                    x->parent = y;
                }
            } else {
                rb_transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            rb_transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if ( NULL != x && y_original_color == RB_BLACK ) {
            rb_delete_fixup(x);
        }
    }

    void rb_delete_fixup(NodeType* x) {
        while (x != _root && x->color == RB_BLACK) {
            if ( x == x->parent->left ) {
                NodeType* w = x->parent->right;
                if (w->color == RB_RED) {
                    w->color = RB_BLACK;
                    x->parent->color = RB_RED;
                    left_rotate(x->parent);
                }
                w = x->parent->right;
                if ( w->left->color == RB_BLACK &&
                        w->right->color == RB_BLACK ) {
                    w->color = RB_RED;
                    x = x->parent;
                } else {
                    if (w->right->color == RB_BLACK) {
                        w->left->color = RB_BLACK;
                        w->color = RB_RED;
                        right_rotate(w);
                        w->color = x->parent->color;
                    }
                    w->color = x->parent->color;
                    x->parent->color = RB_BLACK;
                    w->right->color = RB_BLACK;
                    left_rotate(x->parent);
                    x = _root;
                }
            } else {
                NodeType* w = x->parent->left;
                if ( w->color == RB_RED ) {
                    w->color = RB_BLACK;
                    x->parent->color = RB_RED;
                    right_rotate(x->parent);
                }
                w = x->parent->left;
                if ( w->right->color == RB_BLACK &&
                        w->left->color == RB_BLACK ) {
                    w->color = RB_RED;
                    x = x->parent;
                } else {
                    if (w->left->color == RB_BLACK) {
                        w->right->color = RB_BLACK;
                        w->color = RB_RED;
                        left_rotate(w);
                        w->color = x->parent->color;
                    }
                    w->color = x->parent->color;
                    x->parent->color = RB_BLACK;
                    w->left->color = RB_BLACK;
                    right_rotate(x->parent);
                    x = _root;
                }
            }
        }
        x->color = RB_BLACK;
    }

    inline NodeType* minimum(NodeType* p) const {
        return NodeType::minimum(p);
    }

    NodeType* find_node(const T& _t) {
        if  (NULL == _root) {
            return NULL;
        }
        NodeType* last_less = NULL;
        NodeType* p = _root;
        while (NULL != p) {
            if ( _less(_t, p->data) ) {
                p = p->left;
            } else {
                last_less = p;
                p = p->right;
            }
        }
        return ( NULL == last_less || _less(last_less->data, _t) ) ?
            NULL : last_less;
    }

 PRIVATE:
    NodeType*       _root;
    Compare         _less;
    allocator_type  _alloc;
    node_allocator  _node_alloc;
    size_type       _size;
};

}  //  namespace my

#endif  //  _MY_RBTREE_H_
