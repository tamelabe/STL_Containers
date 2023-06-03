#ifndef CPP2_S21_CONTAINERS//-1_SRC_S21_iter_H_
#define S21_iter_H_

#include "./s21_node.h"

namespace s21 {

template<class T> class list;

template<class T> class ListIterator {
friend class list<T>;

public:
//    using iter_category = std::bidirectional_iter_tag;
//    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using n_pointer = Node<T> *;
    using reference = T&;
    using size_type = std::size_t;

    ListIterator() : iter_(nullptr) {};
    explicit ListIterator(n_pointer ptr) : iter_(ptr) {};
    ListIterator(const ListIterator &other) : iter_(other.iter_) {}
    ListIterator(ListIterator &&other) noexcept : iter_(other.iter_) {
        other.iter_ = nullptr;
    }
    ~ListIterator() { iter_ = nullptr; }
    ListIterator& operator=(const ListIterator &other) {
        iter_ = other.iter_;
        return *this;
    }

    /**
     * gets the element pointed to by the iterator
     */
    reference operator*() const {
        return iter_->data_;
    }
    /**
     * two iterators are not equal if they point to different elements
     */
    bool operator!=(const ListIterator &other) {
        return iter_ != other.iter_;
    }
    /**
     * two iterators are equal if they point to the same element
     */
    bool operator==(const ListIterator &other) {
        return iter_ == other.iter_;
    }
    /**
     * moves the iterator forward to the next element
     * @return incremented value
     */
    ListIterator operator++() {
        iter_ = iter_->next_;
        return *this;
    }
    /**
     * @return original value
     */
    ListIterator operator++(int) {
        ListIterator<value_type> tmp(*this);
        iter_ = iter_->next_;
        return *tmp;
    }
    /**
     * moves the iterator backwards to the previous element
     * @return decremented value
     */
    ListIterator operator--() {
        iter_ = iter_->prev_;
        return *this;
    }
    /**
     * @return original value
     */
    ListIterator operator--(int) {
        ListIterator<value_type> tmp(*this);
        iter_ = iter_->prev_;
        return *tmp;
    }
    size_type operator-(ListIterator(other)) {
        size_type size = 1;
        n_pointer start = iter_;
        while (start != other.iter_) {
            start = start->next_;
            ++size;
        }
        return size;
    }
protected:
    n_pointer iter_;
};

template<class T>
class ListConstIterator : public ListIterator<T> {
friend class list<T>;

public:
    using value_type = const T;
    using pointer = const T*;
    using reference = const T&;
    using n_pointer = Node<T> *;

    explicit ListConstIterator(ListIterator<T> other) : ListIterator<T>(other) {}
    reference operator*() const {
        return this->iter_->data_;
    }
};
    


}
#endif  // S21_iter_H_