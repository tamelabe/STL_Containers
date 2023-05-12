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
        // Объявление псевдонимов
        using value_type = T;  //ok
        using size_type = std::size_t; //ok
        using reference = value_type &; //ok
        using const_reference = const value_type &; //ok


        list() : begin_(new Node<value_type>), end_(new Node<value_type>), size_(0) {
            std::cout << "Started" << std::endl;
        };
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


    private:
    Node<value_type> *begin_;
    Node<value_type> *end_;
    size_type size_;
};
} // namespace s21
#endif // SRC_S21_LIST_H_