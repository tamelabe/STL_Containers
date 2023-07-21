#ifndef CPP2_S21_CONTAINERS_SRC_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_SRC_S21_ARRAY_H_

#include <initializer_list>
#include <limits>
#include <stdexcept>
#include <utility>

namespace s21 {
template <class T, size_t N>
class Array {
 public:
  // Aliases declaration
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // Array Member functions
  Array();
  explicit Array(std::initializer_list<value_type> const &);
  Array(const Array &);
  Array(Array &&) noexcept;
  ~Array();
  Array &operator=(Array &&);

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
  void swap(Array &);
  void fill(const_reference);

 private:
  size_type size_;
  iterator data_;
};

// default constructor, creates empty array
template <class T, size_t N>
Array<T, N>::Array() : size_(N), data_(new T[N]{}) {}

// initializer list constructor,
// creates Array initizialized using std::initializer_list
template <class T, size_t N>
Array<T, N>::Array(std::initializer_list<value_type> const &items)
    : size_(N), data_(new T[N]{}) {
  size_type count = items.size();
  if (count > size_) throw std::length_error{"Too large count"};
  int index = 0;
  for (const T &item : items) {
    data_[index] = item;
    index++;
  }
}

// copy constructor
template <class T, size_t N>
Array<T, N>::Array(const Array &other) : size_(other.size_), data_(new T[N]{}) {
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = other.data_[i];
  }
}

// move constructor
template <class T, size_t N>
Array<T, N>::Array(Array &&origin) noexcept : Array() {
  swap(origin);
}

// assignment operator overload for moving object
template <class T, size_t N>
Array<T, N> &Array<T, N>::operator=(Array<T, N> &&origin) {
  swap(origin);
  origin.size_ = 0;
  return *this;
}

// destructor
template <class T, size_t N>
Array<T, N>::~Array() {
  delete[] data_;
}

// access specified element with bounds checking
template <class T, size_t N>
typename Array<T, N>::reference Array<T, N>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range{"Position is out of range."};
  return data_[pos];
}

// access specified element
template <class T, size_t N>
typename Array<T, N>::reference Array<T, N>::operator[](size_type pos) {
  return data_[pos];
}

// access the first element
template <class T, size_t N>
typename Array<T, N>::const_reference Array<T, N>::front() {
  if (empty()) throw std::out_of_range{"Position is out of range."};
  return data_[0];
}

// access the last element
template <class T, size_t N>
typename Array<T, N>::const_reference Array<T, N>::back() {
  if (empty()) throw std::out_of_range{"Position is out of range."};
  return data_[size_ - 1];
}

// direct access to the underlying Array
template <class T, size_t N>
typename Array<T, N>::iterator Array<T, N>::data() {
  return data_;
}

// returns an iterator to the beginning
template <class T, size_t N>
typename Array<T, N>::iterator Array<T, N>::begin() {
  return data_;
}

// returns an iterator to the end
template <class T, size_t N>
typename Array<T, N>::iterator Array<T, N>::end() {
  return data_ + size_;
}

// checks whether the container is empty
template <class T, size_t N>
bool Array<T, N>::empty() {
  return size_ == 0;
}

// returns the number of elements
template <class T, size_t N>
typename Array<T, N>::size_type Array<T, N>::size() const noexcept {
  return size_;
}

// returns the maximum possible number of elements
template <class T, size_t N>
typename Array<T, N>::size_type Array<T, N>::max_size() const noexcept {
  return size_;
}

// swaps the contents
template <class T, size_t N>
void Array<T, N>::swap(s21::Array<T, N> &v) {
  using std::swap;
  swap(size_, v.size_);
  swap(data_, v.data_);
}

// assigns the given value value to all elements in the container
template <class T, size_t N>
void Array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < size_; ++i) data_[i] = value;
}

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_SRC_S21_VECTOR_H_
