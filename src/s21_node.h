#ifndef SRC_S21_NODE_H
#define SRC_S21_NODE_H

#include "./s21_list.h"


namespace s21 {
template<class T> class list;
template<class T> class ListIterator;
template<class T> class ListConstIterator;

template<class T> class Node {
friend class list<T>;
friend class ListIterator<T>;
friend class ListConstIterator<T>;

public:
    // Aliases
    using value_type = T;
    using reference = value_type &;
    using node_ptr = Node*;
    // Constructors and destructor
    Node() : prev_(this), next_(this), data_(value_type{}) {}
    explicit Node(value_type value) : prev_(nullptr), next_(nullptr), data_(value) {}
    Node(Node *prev, value_type value) : prev_(prev), next_(nullptr), data_(value) {}
    Node(Node *prev, Node *next, value_type value) : prev_(prev), next_(next), data_(value) {}
    ~Node() {}
    // Reference-Type functions for accessing private fields from another classes
//    node_ptr getPrev() { return prev_; }
//    node_ptr& rNext() { return next_; }
//    value_type& rData() { return data_; }

//    Node operator=(const Node &other) {
//        this->prev_ = other.prev_;
//        this->next_ = other.next_;
//        this->data_ = other.data_;
//        return this;
//    }
    void swapNodes(Node* &other) {
        Node* tmp;
        tmp = this->prev_;
        this->prev_ = other->prev_;
        other->prev_ = tmp;
        tmp = this->next_;
        this->next_ = other->next_;
        this->next_ = tmp;
    }
private:
    node_ptr prev_;
    node_ptr next_;
    value_type data_;
};
}
#endif // S21_NODE_H