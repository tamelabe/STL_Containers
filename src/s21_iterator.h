#ifndef CPP2_S21_CONTAINERS_1_SRC_S21_ITERATOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_S21_ITERATOR_H_

#include "./s21_node.h"

namespace s21 {

template <class T>
class List;

template <class T>
class ListIterator {
  friend class List<T>;

 public:
  using value_type = T;
  using n_pointer = Node<T> *;
  using reference = T &;

  ListIterator() : node_(nullptr){};
  explicit ListIterator(n_pointer ptr) : node_(ptr){};
  ListIterator(const ListIterator &other) : node_(other.node_) {}
  ListIterator(const ListConstIterator<T> &other) : node_(other.getNode()) {}
  ListIterator(ListIterator &&other) noexcept : node_(other.node_) {}
  ~ListIterator() { node_ = nullptr; }

  ListIterator &operator=(const ListIterator &other) {
    node_ = other.node_;
    return *this;
  }

  n_pointer getNode() const { return node_; }
  /**
   * gets the element pointed to by the iterator
   */
  reference operator*() const { return *(node_->data_); }
  /**
   * two iterators are not equal if they point to different elements
   */
  bool operator!=(const ListIterator &other) { return node_ != other.node_; }
  /**
   * two iterators are equal if they point to the same element
   */
  bool operator==(const ListIterator &other) { return node_ == other.node_; }
  /**
   * moves the iterator forward to the next element
   * @return incremented value
   */
  ListIterator operator++() {
    node_ = node_->next_;
    return *this;
  }
  /**
   * @return original value
   */
  ListIterator operator++(int) {
    ListIterator<value_type> tmp = *this;
    node_ = node_->next_;
    return tmp;
  }
  /**
   * moves the iterator backwards to the previous element
   * @return decremented value
   */
  ListIterator operator--() {
    node_ = node_->prev_;
    return *this;
  }
  /**
   * @return original value
   */
  ListIterator operator--(int) {
    ListIterator<value_type> tmp = *this;
    node_ = node_->prev_;
    return tmp;
  }

 private:
  n_pointer node_;
};

template <class T>
class ListConstIterator {
  friend class List<T>;

 public:
  using value_type = T;
  using reference = const value_type &;
  using n_pointer = Node<T> *;

  ListConstIterator() : node_(nullptr){};
  explicit ListConstIterator(n_pointer ptr) : node_(ptr){};
  ListConstIterator(const ListConstIterator &other) : node_(other.node_) {}
  ListConstIterator(const ListIterator<value_type> &other)
      : node_(other.getNode()) {}
  ListConstIterator(ListConstIterator &&other) noexcept : node_(other.node_) {
    other.node_ = nullptr;
  }

  ~ListConstIterator() { node_ = nullptr; }

  ListConstIterator &operator=(const ListConstIterator &other) {
    node_ = other.node_;
    return *this;
  }
  ListConstIterator &operator=(ListConstIterator &&other) noexcept {
    node_ = other.node_;
    return *this;
  }

  /**
   * gets the element pointed to by the iterator
   */
  reference operator*() const { return *(node_->data_); }
  /**
   * two iterators are not equal if they point to different elements
   */
  bool operator!=(const ListConstIterator &other) {
    return node_ != other.node_;
  }
  /**
   * two iterators are equal if they point to the same element
   */
  bool operator==(const ListConstIterator &other) {
    return node_ == other.node_;
  }
  /**
   * moves the iterator forward to the next element
   * @return incremented value
   */
  ListConstIterator operator++() {
    node_ = node_->next_;
    return *this;
  }

  /**
   * @return original value
   */
  ListConstIterator operator++(int) {
    ListConstIterator<value_type> tmp = *this;
    node_ = node_->next_;
    return tmp;
  }

  /**
   * moves the iterator backwards to the previous element
   * @return decremented value
   */
  ListConstIterator operator--() {
    node_ = node_->prev_;
    return *this;
  }

  /**
   * @return original value
   */
  ListConstIterator operator--(int) {
    ListConstIterator<value_type> tmp = *this;
    node_ = node_->prev_;
    return tmp;
  }
  n_pointer getNode() const { return node_; }

 private:
  n_pointer node_;
};
}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_1_SRC_S21_ITERATOR_H_