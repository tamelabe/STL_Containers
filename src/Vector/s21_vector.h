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
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  //
  vector() : size_(0U), capacity_(0U), storage_(nullptr) {}

  //
  explicit vector(size_type n) : size_(n), capacity_(n), storage_(new T[capacity_]) {
    for (size_type i = 0; i < n; ++i) storage_[i] = T();
  }

  //
  explicit vector(std::initializer_list<T> const &items) : size_(0) {
    size_type count = items.size();
    capacity_ = count;
    storage_ = new T[capacity_];

    for (const T &item : items) storage_[size_++] = item;
  }

  //
  vector(const vector &v) : size_(v.size_), capacity_(v.capacity_), storage_(new T[capacity_]) {
    for (size_type i = 0; i < size_; ++i) storage_[i] = v.storage_[i];
  }

  //
  vector(vector &&origin) noexcept : vector() {
    swap(origin);
  }

  //
  vector<T> &operator=(std::initializer_list<value_type> const &items) {
    swap(vector<T>(items));
    return *this;
  }

  //
  vector<T> &operator=(const vector<T> &origin) {
    swap(vector<T>(origin));
    return *this;
  }

  //
  vector<T> &operator=(vector<T> &&origin) {
    swap(origin);
    return *this;
  }

  //
  ~vector() {
    delete[] storage_;
  }

  //
  reference at(size_type pos) {
    if (pos >= size_) 
      throw std::out_of_range{"Position is out of range."};
    return storage_[pos];
  }

  //
  reference operator[](size_type pos) {
    return storage_[pos];
  }

  //
  const_reference front() {
    return storage_[0];
  }

  //
  const_reference back() {
    return storage_[size_ - 1];
  }

  //
  iterator data() {
    return storage_;
  }

  //
  iterator begin() {
    return storage_;
  }

  //
  iterator end() {
    return storage_ + size_;
  }

  //
  bool empty() {
    return size_ == 0;
  }

  //
  size_type size() const noexcept {
    return size_;
  }

  //
  size_type max_size() const noexcept {
    return MAX_VECTOR_SIZE;
  }

  void reserve(size_type n) {
    if (n > MAX_VECTOR_SIZE) {
      throw std::length_error{"Requesting size is larger than max_size."};
    }
    if (n <= capacity_) {
      return;
    }
    s21::vector<T> tmp;
    tmp.reallocate(n, size_, storage_);
    tmp.swap(*this);
  }

  //
  size_type capacity() const noexcept {
    return capacity_;
  }

  //
  void shrink_to_fit() {
    s21::vector<T> tmp;
    tmp.reallocate(size_, size_, storage_);
    tmp.swap(*this);
  }

  //
  void clear() noexcept {
    for (size_type i = 0; i < size_; ++i) {
      storage_[i].~T();
    }
    size_ = 0;
  }

  //
  iterator insert(iterator pos, const_reference value) {
    s21::vector<T> tmp(size_ + 1);
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

  //
  void erase(iterator pos) {
    s21::vector<T> tmp(size_ - 1);
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

  //
  void push_back(const_reference value) {
    s21::vector<T> tmp(size_ + 1);
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

  //
  void pop_back() {
    storage_[--size_].~T();
  }

  //
  void swap(vector<T> &v) {
    using std::swap;
    swap(size_, v.size_);
    swap(capacity_, v.capacity_);
    swap(storage_, v.storage_);
  }

  // HELPER methods
  void printVector() {
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

 private:
  size_type size_;
  size_type capacity_;
  iterator storage_;

  // HELPER methods
  void reallocate(size_type capacity, size_type size, const iterator storage) {
    storage_ = new T[capacity];
    capacity_ = capacity;
    for (size_type i = 0; i < size; ++i) {
      storage_[i] = storage[i];
    }
    size_ = size;
  }
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_VECTOR_H_
