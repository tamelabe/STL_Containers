/**
Copyright 2023 Kadyr Atakhanov

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#pragma once
#ifndef CPP2_S21_CONTAINERS_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_S21_VECTOR_H_

#include <iostream>
#include <initializer_list>
#include <utility>

#define MAX_VECTOR_SIZE 1073741824U  //1GB

namespace s21 {

template <class T>
class Vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // CONSTRUCTORS
  Vector();
  explicit Vector(size_type);
  Vector(std::initializer_list<value_type> const&);
  Vector(const Vector&);
  Vector(Vector&&) noexcept;

  // ASSIGNMENTS
  Vector<T> &operator=(std::initializer_list<value_type> const &);
  Vector<T> &operator=(const Vector<T> &);
  Vector<T> &operator=(Vector<T> &&);

  // DESTRUCTOR
  ~Vector();

  // ELEMENT ACCESS METHODS
  reference at(size_type);
  reference operator[](size_type); // OPERATOR OVERLOAD
  const_reference front();
  const_reference back();
  T* data();

  // ITERATOR METHODS
  iterator begin();
  iterator end();

  // CAPACITY METHODS
  bool empty();
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type size);
  size_type capacity() const noexcept;
  void shrink_to_fit();

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

  // void reserve_more_capacity(size_type size);
  void swap(Vector &);
  Vector<T> reallocate(size_type, size_type, iterator);
};

// IMPLEMENTATION
// ========================================================
// CONSTRUCTORS
// default constructor, creates empty vector
template <class T>
s21::Vector<T>::Vector()
    : size_(0U),
      capacity_(0U),
      storage_(nullptr) {}

// parameterized constructor, creates the vector of size n
template <class T>
s21::Vector<T>::Vector(size_type n) 
    : size_(n), 
      capacity_(n), 
      storage_(new T[capacity_]) {
  for (size_type i = 0; i < n; i++)
    storage_[i] = T();
}

// initializer list constructor, 
// creates vector initizialized using std::initializer_list
template <class T>
s21::Vector<T>::Vector(std::initializer_list<T> const &items) : size_(0) {
  size_type count = items.size();
  capacity_ = count;
  storage_ = new T[capacity_];
  
  for (const T& item : items)
    storage_[size_++] = item;
}

// copy constructor
template <class T>
s21::Vector<T>::Vector(const Vector &v)
    : size_(v.size_), 
      capacity_(v.capacity_), 
      storage_(new T[capacity_]) {
  for (size_type i = 0; i < size_; i++)
    storage_[i] = v.storage_[i];
};

// move constructor
template <class T>
s21::Vector<T>::Vector(Vector &&origin) noexcept : Vector() {
  swap(origin);
}

// destructor
template <class T>
s21::Vector<T>::~Vector() {
  delete[] storage_; 
}


// OPERATOR OVERLOADS
// assignment operator overload for vector initizialized list
template <class T>
s21::Vector<T> &
s21::Vector<T>::operator=(std::initializer_list<value_type> const &items) {
  swap(s21::Vector<T>(items));
  return *this;
}

// assignment operator overload for copy object
template <class T>
s21::Vector<T> &
s21::Vector<T>::operator=(const s21::Vector<T> &origin) {
  swap(s21::Vector<T>(origin));
  return *this;
}

// assignment operator overload for moving object
template <class T>
s21::Vector<T> &
s21::Vector<T>::operator=(s21::Vector<T> &&origin) {
  swap(origin);
  return *this;
}


// ELEMENT ACCESS METHODS
// access specified element with bounds checking
template <class T>
typename s21::Vector<T>::reference
s21::Vector<T>::at(size_type pos) {
  if (pos >= size_)
    throw std::out_of_range{"Position is out of range."};
  return storage_[pos];
}

template <class T>
T * s21::Vector<T>::data() {
  return storage_;
}

template <class T>
typename s21::Vector<T>::reference
s21::Vector<T>::operator[](size_type pos) {
  return storage_[pos];
}

template <class T>
typename s21::Vector<T>::const_reference
s21::Vector<T>::front() {
  return storage_[0];
}

template <class T>
typename s21::Vector<T>::const_reference
s21::Vector<T>::back() {
  return storage_[size_ - 1];
}


// ITERATOR METHODS
// returns an iterator to the beginning
template <class T>
typename s21::Vector<T>::iterator
s21::Vector<T>::begin() {
  return storage_;
}

// returns an iterator to the end
template <class T>
typename s21::Vector<T>::iterator
s21::Vector<T>::end() {
  return storage_ + size_;
}


// CAPACITY METHODS
// checks whether the container is empty
template <class T>
bool s21::Vector<T>::empty() {
  return size_ == 0;
}

// returns the number of elements
template <class T>
typename s21::Vector<T>::size_type 
s21::Vector<T>::size() const noexcept {
  return size_;
}

// returns the maximum possible number of elements
template <class T>
typename s21::Vector<T>::size_type 
s21::Vector<T>::max_size() const noexcept {
  return MAX_VECTOR_SIZE;
}

// returns the number of elements that can be held in 
// currently allocated storage
template <class T>
typename s21::Vector<T>::size_type 
s21::Vector<T>::capacity() const noexcept {
  return capacity_;
}

// allocate storage of size elements and copies current 
// array elements to a newely allocated array
template <class T>
void s21::Vector<T>::reserve(size_type n) {
  if (n > MAX_VECTOR_SIZE){
    throw std::length_error{"Requesting size is larger than max_size."};
  }
  if (n <= capacity_) {
    return;
  }
  s21::Vector<T> tmp(0);
  tmp.reallocate(n, size_, storage_);
  tmp.swap(*this);
}

// reduces memory usage by freeing unused memory
template <class T>
void Vector<T>::shrink_to_fit() {
  s21::Vector<T> tmp(size_);
  tmp.reallocate(size_, size_, storage_);
  tmp.swap(*this);
}

// HELPER METHODS
template<typename T>
void s21::Vector<T>::swap(s21::Vector<T>& v) {
  using std::swap;
  swap(size_, v.size_);
  swap(capacity_, v.capacity_);
  swap(storage_, v.storage_);
}

template<typename T>
s21::Vector<T> s21::Vector<T>::reallocate(
    size_type capacity, 
    size_type size, 
    iterator storage) {
  storage_ = new T[capacity];
  capacity_ = capacity;
  for (size_type i = 0; i < size; i++) {
    storage_[i] = storage[i];
    size_ = i + 1;
  }
  return *this;
}
}  // namespace s21


#endif  // CPP2_S21_CONTAINERS_S21_VECTOR_H_
