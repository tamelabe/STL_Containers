#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_NODE_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_NODE_H_

#include "./s21_list.h"

namespace s21 {
template <class T>
class List;
template <class T>
class ListIterator;
template <class T>
class ListConstIterator;

template <class T>
class Node {
  friend class List<T>;
  friend class ListIterator<T>;
  friend class ListConstIterator<T>;

 public:
  // Aliases
  using value_type = T;
  using node_ptr = Node *;
  using const_reference = const value_type &;
  // Constructors and destructor
  Node() : prev_(this), next_(this), data_(nullptr) {}
  explicit Node(const_reference value)
      : prev_(nullptr), next_(nullptr), data_(new value_type) {
    *data_ = value;
  }
  Node(Node *prev, Node *next, const_reference value)
      : prev_(prev), next_(next), data_(new value_type) {
    *data_ = value;
  }
  ~Node() {}

  Node &operator=(const Node &other) {
    this->prev_ = other.prev_;
    this->next_ = other.next_;
    this->data_ = other.data_;
    return *this;
  }

 private:
  node_ptr prev_;
  node_ptr next_;
  value_type *data_;
};
}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_NODE_H_