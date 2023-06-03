#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <initializer_list>
#include <iostream>
#include <limits>
#include "./s21_iterator.h"
#include "./s21_node.h"

namespace s21 {
    template<class T> class list {
    public:
        // Aliases declaration
        using difference_type = std::ptrdiff_t;
        using value_type = T;  //ok
        using size_type = std::size_t; //ok
        using reference = value_type &; //ok
        using const_reference = const value_type &; //ok
        using iterator = ListIterator<value_type>;
        using const_iterator = ListConstIterator<value_type>;
        using node = Node<T>;
        using node_ptr = node*;

        // List Member functions
        /**
         * default constructor, creates empty list and "fake" node
         */
        list() : begin_(nullptr), end_(new Node<value_type>), size_(0) {
            initList();
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
            for (auto i = l.cbegin(); i != l.cend(); ++i)
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
        list &operator=(list &&l) noexcept {
            clear();
            for (auto i = l.begin_; i != l.end(); ++i)
                push_back(*i);
            return *this;
        }

        // List Element access
        /**
        * Returns a reference to the first element in the container.
        * @return reference to the first element
        */
        const_reference front() {
            if (begin_ == end_)
                throw std::out_of_range("list is empty");
            return begin_->data_;
        }
        /**
         * Returns a reference to the last element in the container.
         * @return reference to the last element.
         */
        const_reference back() {
            if (begin_ == end_)
                throw std::out_of_range("list is empty");
            return end_->prev_->data_;
        }

        // List Iterators
        /**
         * returns an iterator to the beginning
         */
        iterator begin() {
            return iterator(begin_);
        }
        const_iterator cbegin() const {
            return const_iterator(begin_);
        }
        /**
         * returns an iterator to the end (next from the last element)
         */
        iterator end() {
            return iterator(end_);
        }
        const_iterator cend() const {
            return const_iterator(end_);
        }

        // List Capacity
        /**
        * Checks if the container has no elements
        * @return true if the container is empty, false otherwise
        */
        bool empty() {
            return begin_ == end_;
        }
        /**
         * The number of elements in the container.
         * @return the number of elements
         */
        size_type size() {
            return size_;
        }
        /**
         * Returns the maximum number of elements the container is able to hold due to system or library implementation limitations
         * @return Maximum number of elements.
         */
        size_type max_size() const {
            return std::numeric_limits<difference_type>::max();
        }

        // List Modifiers
        /**
        * clears the contents
        */
        void clear() {
            deallocate(false);
            initList();
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
                new_node->prev_ = pos.iter_->prev_;
                new_node->next_ = pos.iter_;
                pos.iter_->prev_->next_ = new_node;
                pos.iter_->prev_ = new_node;
                ret_iter = iterator(new_node);
                ++size_;
            }
            return ret_iter;
        }
        /**
        * erases element at pos
        * @param pos - position of iterator
        */
        void erase(iterator pos) {
            if (pos == begin()) {
                pop_front();
            } else if (pos != end()) {
                node_ptr temp = pos.iter_->prev_;
                temp->next_ = pos.iter_->next_;
                pos.iter_->next_->prev_ = temp;
                delete pos.iter_;
            }
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
                new_node->prev_ = end_->prev_;
                new_node->next_ = end_;
                end_->prev_->next_ = new_node;
                end_->prev_ = new_node;
            }
            ++size_;
        }
        /**
        * removes the last element
        */
        void pop_back() noexcept {
            node_ptr tmp = end_->prev_;
            tmp->prev_->next_ = end_;
            end_->prev_ = tmp->prev_;
            delete tmp;
            begin_ = end_->next_;
            --size_;
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
                new_node->prev_ = end_;
                new_node->next_ = begin_;
                end_->next_ = new_node;
                begin_->prev_ = new_node;
                begin_ = new_node;
            }
            ++size_;
        }
        /**
         * removes the first element
         */
        void pop_front() noexcept {
            end_->next_ = begin_->next_;
            begin_->next_->prev_ = end_;
            delete begin_;
            begin_ = end_->next_;
            --size_;
        }
        /**
         * swaps the contents
         */
        void swap(list& other) {
            std::swap(begin_, other.begin_);
            std::swap(end_, other.end_);
            std::swap(size_, other.size_);
        }

        void merge(list& other) {
            if (other.begin() == begin() || !other.size_)
                return;
            if (!size_) {
                swap(other);
            }
            for (auto iter_ths = begin(), iter_oth = other.begin(); iter_ths != end() || iter_oth != other.end(); ++iter_ths) {
                while ((*iter_ths > *iter_oth || iter_ths == end()) && iter_oth != other.end()) {
                    iterator last_oth = sortCheck(iter_oth, other.end());
                    iter_oth = insSubList(iter_ths, iter_oth, last_oth);
                }
            }
            size_ += other.size_;
            other.initList();
        }
        /// PRIVATE!!!
        iterator sortCheck(iterator current, const iterator& end) {
            auto start_pos = current;
            while (*start_pos > *(++current) && current != end) {}
            --current;
            return current;
        }
        /// PRIVATE!!!
        iterator insSubList(iterator& pos, iterator& first, iterator& last) {
            iterator next = last;
            ++next;
            pos.iter_->prev_->next_ = first.iter_;
            first.iter_->prev_ = pos.iter_->prev_;
            pos.iter_->prev_ = last.iter_;
            last.iter_->next_ = pos.iter_;
            if (pos == begin() || begin_ == nullptr)
                begin_ = first.iter_;
            return next;
        }
        /**
         * Merge Sort algorithm based onion brand principle
         */
//        void sort() {
//            if (begin_ == end_ || size_ <= 1)
//                return;
//            sortEngine(begin(), --end());
//
//
//        }
//
//        void sortEngine(const iterator& first_st, const iterator& sec_end) {
//            auto first_end = --splitList();
//            auto sec_st = ++first_end;
//            if (first_st != first_end && sec_st != sec_end) {
//                sortEngine(first_st, first_end);
//                sortEngine(sec_st, sec_end);
//            }
//
//        }
//
//        iterator splitList() {
//            iterator iter = begin();
//            for (auto i = 0; i < size_/2; ++i)
//                ++iter;
//            return iter;
//        }

    private:
        // Variables
        node_ptr begin_;
        node_ptr end_;
        size_type size_;

        // Methods
        /**
         * Create connection of empty list nodes from end_ to begin_
         */
        void initList() {
            end_->next_ = end_;
            end_->prev_ = end_;
            begin_ = end_;
            size_ = 0;
        }
        /**
         * Deallocator
         * @param mode false - deallocate all non fake nodes,
         *             true - fully deallocation
         */
        void deallocate(bool mode) {
            if (begin_ != end_)
                for (auto i = begin(); i != end(); ++i) {
                    delete i.iter_;
                    --size_;
                }
            if (mode) {
                delete end_;
                end_ = begin_ = nullptr;
            }
        }
        /**
         * Using when pushing node in empty list
         * @param value pushing value in data_ field
         */
        void pushFirstNode(const_reference value) {
            node_ptr new_node = new node(value);
            new_node->next_ = new_node->prev_ = end_;
            end_->prev_ = end_->next_ = new_node;
            begin_ = new_node;
        }
};
} // namespace s21
#endif // SRC_S21_LIST_H_