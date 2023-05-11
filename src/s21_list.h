#ifndef SRC_S21_LIST_H_
#define SRC_S21_LIST_H_

#include <initializer_list>
#include <iostream>

namespace s21 {
    template<class T>
    class list {
    public:
        // Объявление псевдонимов
        using value_type = T;  //ok
        using size_type = std::size_t; //ok
        using reference = value_type &; //ok
        using const_reference = const value_type &; //ok
//    using pointer = std::allocator_traits<Allocator>::pointer;
//    using const_pointer = std::allocator_traits<Allocator>::const_pointer;
        list() : begin_(new Node), end_(new Node), size_(0) {
            std::cout << "Started" << std::endl;
        };
        explicit list(size_type n) : list() {
            for (auto i : n)

        }
//    list(std::initializer_list<value_type> const &items);
//    list(const list &l);
//    list(list &&l);
        ~list() {
            std::cout << "Destructor" << std::endl;
            delete begin_;
            delete end_;
            begin_ = nullptr;
            end_ = nullptr;
        }
//    operator=(list &&l);
    class ListIterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using diff = type;
        };
    private:

    class Node {
    public:
        Node() : prev_(this), next_(this), data_(value_type{}) {}
        explicit Node(value_type value) : prev_(nullptr), next_(nullptr), data_(value) {}
        explicit Node(Node *prev, value_type value) : prev_(prev), next_(nullptr), data_(value) {}
        explicit Node(Node *prev, Node *next, value_type value) : prev_(prev), next_(next), data_(value) {}

    private:
        Node *prev_;
        Node *next_;
        value_type data_;
    };

    Node *begin_;
    Node *end_;
    size_type size_;
};
} // namespace s21
#endif // SRC_S21_LIST_H_