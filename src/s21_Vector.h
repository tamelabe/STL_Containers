#ifndef S21_VECTOR_H
#define S21_VECTOR_H

#include <iostream>
#include <initializer_list>
#include <utility>

template <class T>
class s21_Vector
{
    private:
        size_t m_size;
        size_t m_capacity;
        T *arr;

    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using iterator = T *;
        using const_iterator = const T *;
        using size_type = size_t;

    private:
        void reserve_more_capacity(size_type size);

    public:
        // CONSTRUCTORS
        
        s21_Vector();
        s21_Vector(size_type n);
        // s21_Vector(std::initializer_list<value_type> const &items);
        // s21_Vector(const s21_Vector &v) : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr) {};
        // s21_Vector(s21_Vector &&v) : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr) {v.arr = nullptr; v.m_size = 0;}

        // // DESTRUCTORS
        // ~s21_Vector() { delete[] arr; }

        // // OPERATOR OVERLOADS
        // operator=(vector &&v)
        
        // // ELEMENT ACCESS METHODS
        // iterator data();  // T*
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
        // size_type size();
        // size_type max_size();
        // size_type capacity();

        // // MODIFIER METHODS
        // iterator insert(iterator pos, const_reference value);
        // void clear();
        // void erase(iterator pos);
        // void push_back(const_reference value);
        // void pop_back();
        // void swap(vector& other);

};

#endif  // S21_VECTOR_H
