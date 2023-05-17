#ifndef S21_NODE_H
#define S21_NODE_H

namespace s21 {

template<class T>
class Node {
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
    // Reference-Type Functions (Accessors and Mutators alternative)
    node_ptr &rPrev() { return prev_; }
    node_ptr &rNext() { return next_; }
    value_type &rData() { return data_; }
//    Node operator=(const Node &other) {
//        this->prev_ = other.prev_;
//        this->next_ = other.next_;
//        this->data_ = other.data_;
//        return this;
//    }

private:
    node_ptr prev_;
    node_ptr next_;
    value_type data_;
};
}
#endif // S21_NODE_H