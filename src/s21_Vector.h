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

#ifndef CPP2_S21_CONTAINERS_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_S21_VECTOR_H_

#include <initializer_list>
#include <iostream>
#include <utility>

#define MAX_VECTOR_SIZE 1073741824U  // 1GB

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
  explicit Vector(std::initializer_list<value_type> const &);
  Vector(const Vector &);
  Vector(Vector &&) noexcept;

  // ASSIGNMENTS
  Vector<T> &operator=(std::initializer_list<value_type> const &);
  Vector<T> &operator=(const Vector<T> &);
  Vector<T> &operator=(Vector<T> &&);

  // DESTRUCTOR
  ~Vector();

  // ELEMENT ACCESS METHODS
  reference at(size_type);
  reference operator[](size_type);  // OPERATOR OVERLOAD
  const_reference front();
  const_reference back();
  iterator data();

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
  void clear() noexcept;
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(Vector &);

  // HELPER methods
  void printVector();

 private:
  size_type size_;
  size_type capacity_;
  iterator storage_;

  // HELPER methods
  void reallocate(size_type, size_type, const iterator);
};

// CONSTRUCTORS AND MEMBER FUNCTIONS
// default constructor, creates empty vector
template <class T>
Vector<T>::Vector() : size_(0U), capacity_(0U), storage_(nullptr) {}

// parameterized constructor, creates the vector of size n
template <class T>
Vector<T>::Vector(size_type n)
    : size_(n), capacity_(n), storage_(new T[capacity_]) {
  for (size_type i = 0; i < n; ++i) storage_[i] = T();
}

// initializer list constructor,
// creates vector initizialized using std::initializer_list
template <class T>
Vector<T>::Vector(std::initializer_list<T> const &items) : size_(0) {
  size_type count = items.size();
  capacity_ = count;
  storage_ = new T[capacity_];

  for (const T &item : items) storage_[size_++] = item;
}

// copy constructor
template <class T>
Vector<T>::Vector(const Vector &v)
    : size_(v.size_), capacity_(v.capacity_), storage_(new T[capacity_]) {
  for (size_type i = 0; i < size_; ++i) storage_[i] = v.storage_[i];
};

// move constructor
template <class T>
Vector<T>::Vector(Vector &&origin) noexcept : Vector() {
  swap(origin);
}

// destructor
template <class T>
Vector<T>::~Vector() {
  delete[] storage_;
}

// OPERATOR OVERLOADS
// assignment operator overload for vector initizialized list
template <class T>
Vector<T> &Vector<T>::operator=(
    std::initializer_list<value_type> const &items) {
  swap(Vector<T>(items));
  return *this;
}

// assignment operator overload for copy object
template <class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &origin) {
  swap(Vector<T>(origin));
  return *this;
}

// assignment operator overload for moving object
template <class T>
Vector<T> &Vector<T>::operator=(Vector<T> &&origin) {
  swap(origin);
  return *this;
}

// ELEMENT ACCESS METHODS
// access specified element with bounds checking
template <class T>
typename Vector<T>::reference Vector<T>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range{"Position is out of range."};
  return storage_[pos];
}

template <class T>
typename Vector<T>::iterator Vector<T>::data() {
  return storage_;
}

template <class T>
typename Vector<T>::reference Vector<T>::operator[](size_type pos) {
  return storage_[pos];
}

template <class T>
typename Vector<T>::const_reference Vector<T>::front() {
  return storage_[0];
}

template <class T>
typename Vector<T>::const_reference Vector<T>::back() {
  return storage_[size_ - 1];
}

// ITERATOR METHODS
// returns an iterator to the beginning
template <class T>
typename Vector<T>::iterator Vector<T>::begin() {
  return storage_;
}

// returns an iterator to the end
template <class T>
typename Vector<T>::iterator Vector<T>::end() {
  return storage_ + size_;
}

// CAPACITY METHODS
// checks whether the container is empty
template <class T>
bool Vector<T>::empty() {
  return size_ == 0;
}

// returns the number of elements
template <class T>
typename Vector<T>::size_type Vector<T>::size() const noexcept {
  return size_;
}

// returns the maximum possible number of elements
template <class T>
typename Vector<T>::size_type Vector<T>::max_size() const noexcept {
  return MAX_VECTOR_SIZE;
}

// returns the number of elements that can be held in
// currently allocated storage
template <class T>
typename Vector<T>::size_type Vector<T>::capacity() const noexcept {
  return capacity_;
}

// allocate storage of size elements and copies current
// array elements to a newely allocated array
template <class T>
void Vector<T>::reserve(size_type n) {
  if (n > MAX_VECTOR_SIZE) {
    throw std::length_error{"Requesting size is larger than max_size."};
  }
  if (n <= capacity_) {
    return;
  }
  s21::Vector<T> tmp;
  tmp.reallocate(n, size_, storage_);
  tmp.swap(*this);
}

// reduces memory usage by freeing unused memory
template <class T>
void Vector<T>::shrink_to_fit() {
  s21::Vector<T> tmp;
  tmp.reallocate(size_, size_, storage_);
  tmp.swap(*this);
}

// MODIFIER METHODS
// clears the contents
template <class T>
void Vector<T>::clear() noexcept {
  for (size_type i = 0; i < size_; ++i) {
    storage_[i].~T();
  }
  size_ = 0;
}

// inserts elements into concrete pos and
// returns the iterator that points to the new element
template <class T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos,
                                               const_reference value) {
  s21::Vector<T> tmp(size_ + 1);
  size_type new_element_index = 0;
  iterator ptr = begin();
  size_type i = 0;
  while (ptr <= end()) {
    if (ptr < pos) {
      tmp.storage_[i] = *ptr;
    } else if (ptr == pos) {
      tmp.storage_[i] = value;
      new_element_index = i;
    } else {
      tmp.storage_[i] = *(ptr - 1);
    }
    ptr++;
    ++i;
  }
  tmp.swap(*this);

  return &(storage_[new_element_index]);
}

// erases element at pos
template <class T>
void Vector<T>::erase(iterator pos) {
  s21::Vector<T> tmp(size_ - 1);
  iterator ptr = begin();
  size_type i = 0;
  while (ptr < end()) {
    if (ptr < pos) {
      tmp.storage_[i] = *ptr;
    } else {
      tmp.storage_[i] = *(ptr + 1);
    }
    ptr++;
    ++i;
  }
  tmp.swap(*this);
}

// adds an element to the end
template <class T>
void Vector<T>::push_back(const_reference value) {
  s21::Vector<T> tmp(size_ + 1);
  iterator ptr = begin();
  size_type i = 0;
  while (ptr <= end()) {
    if (ptr == end()) {
      tmp.storage_[i] = value;
    } else {
      tmp.storage_[i] = *ptr;
    }
    ptr++;
    ++i;
  }
  tmp.swap(*this);
}

// removes the last element
template <class T>
void Vector<T>::pop_back() {
  storage_[--size_].~T();
}

// swaps the contents
template <typename T>
void s21::Vector<T>::swap(s21::Vector<T> &v) {
  using std::swap;
  swap(size_, v.size_);
  swap(capacity_, v.capacity_);
  swap(storage_, v.storage_);
}

// HELPER METHODS
template <typename T>
void s21::Vector<T>::printVector() {
  iterator ptr = begin();
  std::cout << "============" << std::endl;
  std::cout << "PRINT VECTOR" << std::endl;
  std::cout << "============" << std::endl;
  while (ptr < end()) {
    std::cout << "ptr: " << *ptr << " - " << ptr << std::endl;
    ++ptr;
  }
  std::cout << "============" << std::endl;
}

template <typename T>
void s21::Vector<T>::reallocate(size_type capacity, size_type size,
                                const iterator storage) {
  storage_ = new T[capacity];
  capacity_ = capacity;
  for (size_type i = 0; i < size; ++i) {
    storage_[i] = storage[i];
  }
  size_ = size;
}
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_VECTOR_H_
