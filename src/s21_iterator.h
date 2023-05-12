#ifndef S21_ITERATOR_H_
#define S21_ITERATOR_H_

#include "./s21_node.h"

namespace s21 {
template <class T>
class ListIterator {
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using n_pointer = Node<T> *;
    using reference = T&;

    ListIterator() : iterator_(nullptr) {};
    ListIterator(n_pointer p) : iterator_(p) {};

private:
    n_pointer iterator_;


};
}
#endif  // S21_ITERATOR_H_