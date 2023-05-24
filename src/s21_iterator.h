#ifndef CPP2_S21_CONTAINERS//-1_SRC_S21_ITERATOR_H_
#define S21_ITERATOR_H_

#include "./s21_node.h"

namespace s21 {

template<class T> class list;

template<class T> class ListIterator {
friend class list<T>;

public:
//    using iterator_category = std::bidirectional_iterator_tag;
//    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using n_pointer = Node<T> *;
    using reference = T&;

    ListIterator() : iterator_(nullptr) {};
    ListIterator(n_pointer ptr) : iterator_(ptr) {};
    ListIterator(const ListIterator &other) : iterator_(other.iterator_) {}
    ListIterator(ListIterator &&other) : iterator_(other.iterator_) {
        other.iterator_ = nullptr;
    }
    ~ListIterator() { iterator_ = nullptr; }

//    n_pointer &iterPtr() { return iterator_; }

    reference operator*() const {
        return iterator_->data_;
    }
    bool operator!=(const ListIterator &other) {
        return iterator_ != other.iterator_;
    }
    bool operator==(const ListIterator &other) {
        return iterator_ == other.iterator_;
    }
    void operator=(const ListIterator &other) {
        iterator_ = other.iterator_;
    }


    ListIterator operator++() {
        iterator_ = iterator_->next_;
        return *this;
    }
    ListIterator operator--() {
        iterator_ = iterator_->prev_;
        return *this;
    }




private:
    n_pointer iterator_;


};
}
#endif  // S21_ITERATOR_H_