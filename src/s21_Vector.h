#pragma once
#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <iostream>
#include <initializer_list>
#include <utility>

#define MAX_VECTOR_SIZE 1073741824U  //1GB

namespace s21
{
template <class T>
class Vector
{
    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using iterator = T *;
        using const_iterator = const T *;
        using size_type = size_t;

    public:
        // CONSTRUCTORS
        
        Vector();

        explicit Vector(size_type);
        // s21_vector(std::initializer_list<value_type> const &items);
        // s21_vector(const s21_vector &v) : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr) {};
        // s21_vector(s21_vector &&v) : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr) {v.arr = nullptr; v.m_size = 0;}

        // DESTRUCTORS
        ~Vector() { delete[] storage; }

        // // OPERATOR OVERLOADS
        // operator=(vector &&v)
        
        // // ELEMENT ACCESS METHODS
        T* data();  // T*
        // size_type size();
        // value_type& at(size_type pos);
        // value_type& operator[](size_type pos);
        // const value_type& front();
        // const value_type& back();

        // // ITERATOR METHODS
        // iterator begin();
        // iterator end();

        // // CAPACITY METHODS
        // bool empty();
        // void reserve(size_type size);
        // void shrink_to_fir();
        size_type size() const noexcept;;
        size_type max_size() const noexcept;;
        size_type capacity() const noexcept;;

        // // MODIFIER METHODS
        // iterator insert(iterator pos, const_reference value);
        // void clear();
        // void erase(iterator pos);
        // void push_back(const_reference value);
        // void pop_back();
        // void swap(vector& other);

    private:
        size_t m_size;
        size_t m_capacity;
        T * storage;
    
    private:
        // void reserve_more_capacity(size_type size);
};
}

#include "s21_vector.cc"

#endif  // S21_VECTOR_H
