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
        Vector(Vector &&v) noexcept;

        // DESTRUCTORS
        ~Vector();

        // OPERATOR OVERLOADS
        Vector<T> &operator=(std::initializer_list<value_type> const &items);
        Vector<T> &operator=(const Vector<T> &origin);
        Vector<T> &operator=(Vector<T> &&origin);

        // // ELEMENT ACCESS METHODS
        // value_type& at(size_type pos);
        // value_type& operator[](size_type pos);
        // const value_type& front();
        // const value_type& back();
        T* data();

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
        size_type size_;
        size_type capacity_;
        iterator storage_;
    
    private:
        // void reserve_more_capacity(size_type size);
        void swap(Vector &);
};


// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
// = = = = = = = = = = = = = =  IMPLEMENTATION = = = = = = = = = = = = = = //
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //

// CONSTRUCTORS
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
// default constructor, creates empty vector
template <class T>
s21::Vector<T>::Vector()
    : size_(0U)
    , capacity_(0U)
    , storage_(nullptr) 
{}

// parameterized constructor, creates the vector of size n
template <class T>
s21::Vector<T>::Vector(size_type n) 
    : size_(n)
    , capacity_(n)
    , storage_(new T[capacity_]) 
{
    for (size_type i = 0; i < n; i++)
        storage_[i] = T();
}

// initializer list constructor, creates vector initizialized using std::initializer_list
template <class T>
s21::Vector<T>::Vector(std::initializer_list<T> const &items)
{
    size_type count = items.size();
    size_ = 0;
    capacity_ = count;
    storage_ = new T[capacity_];
    
    for (const T& item : items)
        storage_[size_++] = item;
}

// copy constructor
template <class T>
s21::Vector<T>::Vector(const Vector &v)
    : size_(v.size_)
    , capacity_(v.capacity_)
    , storage_(new T[capacity_])
{
    for (size_type i = 0; i < size_; i++)
        storage_[i] = v.storage_[i];
};

// move constructor
template <class T>
s21::Vector<T>::Vector(Vector &&origin) noexcept 
    : Vector() 
{
    swap(origin);
}

// destructor
template <class T>
s21::Vector<T>::~Vector()
{
    delete[] storage_; 
}


// OPERATOR OVERLOADS
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
// assignment operator overload for vector initizialized list
template <class T>
s21::Vector<T> &
s21::Vector<T>::operator=(std::initializer_list<value_type> const &items)
{
    swap(s21::Vector<T>(items));
    return *this;
}

// assignment operator overload for copy object
template <class T>
s21::Vector<T> &
s21::Vector<T>::operator=(const s21::Vector<T> &origin)
{
    swap(s21::Vector<T>(origin));
    return *this;
}

// assignment operator overload for moving object
template <class T>
s21::Vector<T> &
s21::Vector<T>::operator=(s21::Vector<T> &&origin)
{
    swap(origin);
    return *this;
}


// CAPACITY METHODS
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
// returns the number of elements
template <class T>
typename s21::Vector<T>::size_type 
s21::Vector<T>::size() const noexcept
{
    return size_;
}

// returns the number of elements that can be held in currently allocated storage
template <class T>
typename s21::Vector<T>::size_type 
s21::Vector<T>::capacity() const noexcept
{
    return capacity_;
}

// ELEMENT ACCESS METHODS
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = //
template <class T>
T *
s21::Vector<T>::data()
{
    return storage_;
}


// HELPER METHODS
template<typename T>
void 
s21::Vector<T>::swap(s21::Vector<T>& v)
{
    using std::swap;
    swap(size_, v.size_);
    swap(capacity_, v.capacity_);
    swap(storage_, v.storage_);
}

};  // namespace s21


#endif  // S21_VECTOR_H
