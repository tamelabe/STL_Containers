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

#ifndef CPP2_S21_CONTAINERS_SRC_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_SRC_S21_ARRAY_H_

#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {
template <class T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // 
  array() : size_(N), data_(new T[N]) {}

  // 
  explicit array(std::initializer_list<value_type> const &items) : size_(N) {
    size_type count = items.size();
    if (count > size_) {
      throw std::length_error{"Count of items is bigger than size."};
    }
    data_ = new T[count];
    int index = 0;
    for (const T &item : items) {
      data_[index] = item;
      index++;
    }
  }

  // copy constructor
  array(const array &a) : size_(a.size_), data_(nullptr) {
    for (size_type i = 0; i < size_; ++i) data_[i] = a.data_[i];
  }

  // move constructor
  array(array &&origin) noexcept : array() {swap(origin);}

  // assignment operator overload for moving object
  array<T, N> &operator=(array<T, N> &&origin) {
    swap(origin);
    return *this;
  }

  // destructor
  ~array() {delete[] data_;}

  //
  reference at(size_type pos) {
    if (pos >= size_) throw std::out_of_range{"Position is out of range."};
    return data_[pos];
  }

  //
  reference operator[](size_type pos) {
    if (pos >= size_) throw std::out_of_range{"Position is out of range."};
    return data_[pos];
  }

  //
  const_reference front() {
    if (empty()) throw std::out_of_range{"Position is out of range."};
    return data_[0];
  }

  //
  const_reference back() {
    if (empty()) throw std::out_of_range{"Position is out of range."};
    return data_[size_ - 1];
  }
  
  //
  iterator data() {return data_;}

  //
  iterator begin() {return data_;}

  //
  iterator end() {return data_ + size_;}

  //
  bool empty() {return size_ == 0;}

  //
  size_type size() const noexcept {return size_;}

  //
  size_type max_size() const noexcept {return size_;}

  //
  void swap(s21::array<T, N> &v) {
    using std::swap;
    swap(size_, v.size_);
    swap(data_, v.data_);
    v.size_ = 0;
  }

  void fill(const_reference value) {
    for (size_type i = 0; i < size_; ++i) data_[i] = value;
  }

 private:
  size_type size_;
  iterator data_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H_
