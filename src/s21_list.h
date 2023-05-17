#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <initializer_list>
#include <iostream>
#include "./s21_iterator.h"
#include "./s21_node.h"

namespace s21 {
    template<class T>
    class list {
    friend class s21::ListIterator<T>;
    public:
        // Aliases declaration
        using value_type = T;  //ok
        using size_type = std::size_t; //ok
        using reference = value_type &; //ok
        using const_reference = const value_type &; //ok
        using iterator = ListIterator<T>;
        using node = Node<T>;
        using node_ptr = node*;
        /**
         * default constructor, creates empty list and "fake" node
         */
        list() : begin_(nullptr), end_(new Node<value_type>), size_(0) {
            end_->rNext() = end_;
            end_->rPrev() = end_;
            begin_ = end_;
            std::cout << "Started def" << std::endl;
        };
        /**
         * parameterized constructor
         * @param creates the list of size n
         */
//        explicit list(size_type n) : begin_()
//    list(std::initializer_list<value_type> const &items);
//    list(const list &l);
//    list(list &&l);
        ~list() {
            std::cout << "Destructor" << std::endl;
            deallocate(true);
        }
//    operator=(list &&l);
        /**
         * returns an iterator to the beginning
         */
        iterator begin() {
            return iterator(begin_);
        }
        /**
         * returns an iterator to the end (next from the last element)
         */
        iterator end() const {
            return iterator(end_);
        }
        /**
         * adds an element to the end
         * @param value additional element
         */
        void push_back(const_reference value) {
            node_ptr new_node = new node(value);
            if (end_ == begin_) {
                new_node->rNext() = new_node->rPrev() = end_;
                end_->rPrev() = end_->rNext() = new_node;
                begin_ = new_node;
            } else {
                new_node->rPrev() = end_->rPrev();
                new_node->rNext() = end_;
                end_->rPrev()->rNext() = new_node;
                end_->rPrev() = new_node;
            }
            size_++;
        }
        /**
        * adds an element to the head
        * @param value additional element
        */
        void push_front(const_reference value) {

        }
        /**
         * removes the last element
         */
        void pop_back() {

        }
        /**
         * removes the first element
         */
        void pop_front() {

        }

//
//        iterator insert(iterator pos, const_reference value) {
//            node_ptr curr_node = new node(value);
//            node_ptr next_node = pos.GetPointer();
//
//
//        }


    private:
    node_ptr begin_;
    node_ptr end_;
    size_type size_;

    /**
     * Deallocator
     * @param mode false - deallocate all non fake nodes,
     *             true - fully deallocation
     */
    void deallocate(bool mode) {
        if (begin_ != end_)
            for (auto i = begin(); i != end(); ++i) {
                delete i.iterPtr();
//                i.iterPtr() = nullptr;
            }
        if (mode)
            delete end_;
            end_ = begin_ = nullptr;
    }
};
} // namespace s21
#endif // SRC_S21_LIST_H_