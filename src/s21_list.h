#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <initializer_list>
#include <iostream>
#include "./s21_iterator.h"
#include "./s21_node.h"

namespace s21 {
    template<class T>
    class list {
    public:
        // Aliases declaration
        using value_type = T;  //ok
        using size_type = std::size_t; //ok
        using reference = value_type &; //ok
        using const_reference = const value_type &; //ok
        using iterator = ListIterator<T>;
        using node = Node<T>;
        using node_ptr = node*;

        // Constructors and destructor
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
        explicit list(size_type n) : list() {
            for(auto i = 0; i < n; ++i)
                push_back(value_type{});
        }
        /**
         * initializer list constructor, creates list initizialized using std::initializer_list
         * @param items
         */
        list(std::initializer_list<value_type> const &items) : list() {
            for(auto i = items.begin(); i < items.end(); ++i)
                push_back(*i);
        }
        /**
         * copy constructor
         * @param l - list to copy
         */
        list(const list &l) : list() {
            for (auto i = l.begin_; i < l.end_; i++)
                push_back(*i);
        }
        /**
         * move constructor
         * @param l - rvalue reference
         */
        list(list &&l) : begin_(l.begin_), end_(l.end_), size_(l.size_) {
            l.begin_ = l.end_ = nullptr;
            l.size_ = 0;
        }
        /**
         * destructor
         */
        ~list() {
            std::cout << "Destructor" << std::endl;
            deallocate(true);
        }
//    operator=(list &&l);
        //Methods
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
            if (end_ == begin_) {
                pushFirstNode(value);
            } else {
                node_ptr new_node = new node(value);
                new_node->rPrev() = end_->rPrev();
                new_node->rNext() = end_;
                end_->rPrev()->rNext() = new_node;
                end_->rPrev() = new_node;
            }
            ++size_;
        }
        /**
        * adds an element to the head
        * @param value additional element
        */
        void push_front(const_reference value) {
            if (end_ == begin_) {
                pushFirstNode(value);
            } else {
                node_ptr new_node = new node(value);
                new_node->rPrev() = end_;
                new_node->rNext() = begin_;
                end_->rNext() = new_node;
                begin_->rPrev() = new_node;
                begin_ = new_node;
            }
            ++size_;
        }
        /**
         * removes the last element
         */
        void pop_back() {
            node_ptr tmp = end_->rPrev();
            tmp->rPrev()->rNext() = end_;
            end_->rPrev() = tmp->rPrev();
            delete tmp;
            --size_;
        }
        /**
         * removes the first element
         */
        void pop_front() {
            end_->rNext() = begin_->rNext();
            begin_->rNext()->rPrev() = end_;
            delete begin_;
            begin_ = end_->rNext();
            --size_;
        }

        /**
         * inserts element into concrete pos and returns the iterator that points to the new element
         * @param pos position of iterator to push new element
         * @param value value to push in data field
         * @return iterator that points to the new element
         */
        iterator insert(iterator pos, const_reference value) {
            iterator ret_iter;
            if (pos == begin()) {
                push_front(value);
                ret_iter = begin();
            } else {
                node_ptr new_node = new node(value);
                new_node->rPrev() = pos.iterPtr()->rPrev();
                new_node->rNext() = pos.iterPtr();
                pos.iterPtr()->rPrev()->rNext() = new_node;
                pos.iterPtr()->rPrev() = new_node;
                ret_iter = iterator(new_node);
                ++size_;
            }
            return ret_iter;
        }

    private:
        // Variables
        node_ptr begin_;
        node_ptr end_;
        size_type size_;

        // Methods
        /**
         * Deallocator
         * @param mode false - deallocate all non fake nodes,
         *             true - fully deallocation
         */
        void deallocate(bool mode) {
            if (begin_ != end_)
                for (auto i = begin(); i != end(); ++i) {
                    delete i.iterPtr();
                    --size_;
                }
            if (mode)
                delete end_;
                end_ = begin_ = nullptr;
        }
        /**
         * Using when pushing node in empty list
         * @param value pushing value in data_ field
         */
        void pushFirstNode(const_reference value) {
            node_ptr new_node = new node(value);
            new_node->rNext() = new_node->rPrev() = end_;
            end_->rPrev() = end_->rNext() = new_node;
            begin_ = new_node;
        }
};
} // namespace s21
#endif // SRC_S21_LIST_H_