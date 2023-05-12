#ifndef S21_NODE_H
#define S21_NODE_H

namespace s21 {

template<class T>
class Node {
public:
    using value_type = T;
    Node() : prev_(this), next_(this), data_(value_type{}) {}
    explicit Node(value_type value) : prev_(nullptr), next_(nullptr), data_(value) {}
    Node(Node *prev, value_type value) : prev_(prev), next_(nullptr), data_(value) {}
    Node(Node *prev, Node *next, value_type value) : prev_(prev), next_(next), data_(value) {}
private:
    Node *prev_;
    Node *next_;
    value_type data_;
};
}
#endif // S21_NODE_H