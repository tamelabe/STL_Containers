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
        Vector(std::initializer_list<value_type> const &items);
        Vector(const Vector &v);
        // Vector(Vector &&v) : size_(v.size_), capacity_(v.capacity_), arr(v.arr) {v.arr = nullptr; v.size_ = 0;}

        // DESTRUCTORS
        ~Vector() { delete[] storage_; }

        // // OPERATOR OVERLOADS
        // Vector<T>& operator=(std::initializer_list<value_type> const &items);
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
        size_type size() const noexcept;
        // size_type max_size() const noexcept;
        size_type capacity() const noexcept;

        // // MODIFIER METHODS
        // iterator insert(iterator pos, const_reference value);
        // void clear();
        // void erase(iterator pos);
        // void push_back(const_reference value);
        // void pop_back();
        // void swap(vector& other);

    private:
        size_t size_;
        size_t capacity_;
        T * storage_;
    
    private:
        // void reserve_more_capacity(size_type size);
};

// IMPLEMENTATION

// CONSTRUCTORS
template <class T>
s21::Vector<T>::Vector() : 
    size_(0U), 
    capacity_(0U), 
    storage_(nullptr) 
{}

template <class T>
s21::Vector<T>::Vector(size_type n) : 
    size_(n), capacity_(n), storage_(n ? new T[n] : nullptr) 
{
    for (size_type i = 0; i < n; i++)
        storage_[i] = T();
}

template <class T>
s21::Vector<T>::Vector(std::initializer_list<T> const &items) {
    size_type count = items.size();
    size_ = 0;
    capacity_ = count;
    storage_ = new T[capacity_];
    
    for (const T& item : items)
        storage_[size_++] = item;
}

template <class T>
s21::Vector<T>::Vector(const Vector &v) : size_(v.size_), capacity_(v.capacity_) {
    storage_ = new T[capacity_];
    for (size_type i = 0; i < size_; i++)
        storage_[i] = v.storage_[i];
};


// CAPACITY METHODS
template <class T>
typename s21::Vector<T>::size_type 
s21::Vector<T>::size() const noexcept {
    return size_;
}

template <class T>
T * s21::Vector<T>::data() {
    return storage_;
}

template <class T>
typename s21::Vector<T>::size_type 
s21::Vector<T>::capacity() const noexcept {
    return capacity_;
}

};

#endif  // S21_VECTOR_H
