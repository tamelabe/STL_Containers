#ifndef CPP2_S21_CONTAINERS_SRC_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_SRC_S21_ARRAY_H_

#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>

namespace s21 {
template <class T, size_t N>
class array {
 public:
  // Aliases declaration
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // Array Member functions
  array();
  explicit array(std::initializer_list<value_type> const &);
  array(const array &);
  array(array &&) noexcept;
  ~array();
  array &operator=(array &&);

  // Array Element access
  reference at(size_type);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  // Array Iterators
  iterator begin();
  iterator end();

  // Array Capacity
  bool empty();
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Array Modifiers
  void swap(array &);
  void fill(const_reference);

 private:
  size_type size_;
  iterator data_;
};

// default constructor, creates empty array
template <class T, size_t N>
array<T, N>::array() : size_(N), data_(new T[N]{}) {}

// initializer list constructor,
// creates array initizialized using std::initializer_list
template <class T, size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items)
    : size_(N), data_(new T[N]{}) {
  size_type count = items.size();
  if (count > size_) {
    throw std::length_error{"Count of items is bigger than size."};
  }
  int index = 0;
  for (const T &item : items) {
    data_[index] = item;
    index++;
  }
}

// copy constructor
template <class T, size_t N>
array<T, N>::array(const array &other) : size_(other.size_), data_(new T[N]{}) {
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = other.data_[i];
  }
}

// move constructor
template <class T, size_t N>
array<T, N>::array(array &&origin) noexcept : array() {
  swap(origin);
  origin.size_ = 0;
}

// assignment operator overload for moving object
template <class T, size_t N>
array<T, N> &array<T, N>::operator=(array<T, N> &&origin) {
  swap(origin);
  origin.size_ = 0;
  return *this;
}

// destructor
template <class T, size_t N>
array<T, N>::~array() {
  delete[] data_;
}

// access specified element with bounds checking
template <class T, size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range{"Position is out of range."};
  return data_[pos];
}

// access specified element
template <class T, size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  if (pos >= size_) throw std::out_of_range{"Position is out of range."};
  return data_[pos];
}

// access the first element
template <class T, size_t N>
typename array<T, N>::const_reference array<T, N>::front() {
  if (empty()) throw std::out_of_range{"Position is out of range."};
  return data_[0];
}

// access the last element
template <class T, size_t N>
typename array<T, N>::const_reference array<T, N>::back() {
  if (empty()) throw std::out_of_range{"Position is out of range."};
  return data_[size_ - 1];
}

// direct access to the underlying array
template <class T, size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return data_;
}

// returns an iterator to the beginning
template <class T, size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return data_;
}

// returns an iterator to the end
template <class T, size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return data_ + size_;
}

// checks whether the container is empty
template <class T, size_t N>
bool array<T, N>::empty() {
  return size_ == 0;
}

// returns the number of elements
template <class T, size_t N>
typename array<T, N>::size_type array<T, N>::size() const noexcept {
  return size_;
}

// returns the maximum possible number of elements
template <class T, size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const noexcept {
  return size_;
}

// swaps the contents
template <class T, size_t N>
void array<T, N>::swap(s21::array<T, N> &v) {
  using std::swap;
  swap(size_, v.size_);
  swap(data_, v.data_);
}

// assigns the given value value to all elements in the container
template <class T, size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < size_; ++i) data_[i] = value;
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H_
