#ifndef CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>

namespace s21 {
template <class T>
class vector {
  class VectorIterator;
  class VectorConstIterator;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector();
  explicit vector(size_type);
  explicit vector(std::initializer_list<T> const &);
  vector(const vector &);
  vector(vector &&) noexcept;
  vector<T> &operator=(std::initializer_list<value_type> const &);
  vector<T> &operator=(const vector<T> &);
  vector<T> &operator=(vector<T> &&);
  ~vector();
  reference at(size_type);
  reference operator[](size_type);
  const_reference front();
  const_reference back();
  iterator data();
  iterator begin();
  iterator end();
  bool empty();
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type);
  size_type capacity() const noexcept;
  void shrink_to_fit();
  void clear() noexcept;
  iterator insert(iterator, const_reference);
  void erase(iterator);
  void push_back(const_reference);
  void pop_back();
  void swap(vector<T> &);
  void printVector();

  template <class... Args>
  iterator insert_many(const_iterator, Args &&...);

  template <class... Args>
  void insert_many_back(Args &&...);

 private:
  size_type size_;
  size_type capacity_;
  iterator storage_;
  const unsigned MAX_VECTOR_SIZE = 1073741824U;  // 1GB

  void reallocate(size_type capacity, size_type size, const iterator storage);
};

// default constructor, creates empty vector
template <class T>
vector<T>::vector() : size_(0U), capacity_(0U), storage_(nullptr) {}

// parameterized constructor, creates the vector of size n
template <class T>
vector<T>::vector(size_type n)
    : size_(n), capacity_(n), storage_(new T[capacity_]) {
  for (size_type i = 0; i < n; ++i) storage_[i] = T();
}

// initializer list constructor, creates vector initizialized using
// std::initializer_list
template <class T>
vector<T>::vector(std::initializer_list<T> const &items) : size_(0) {
  size_type count = items.size();
  capacity_ = count;
  storage_ = new T[capacity_];

  for (const T &item : items) storage_[size_++] = item;
}

// copy constructor
template <class T>
vector<T>::vector(const vector &v)
    : size_(v.size_), capacity_(v.capacity_), storage_(new T[capacity_]) {
  for (size_type i = 0; i < size_; ++i) storage_[i] = v.storage_[i];
}

// move constructor
template <class T>
vector<T>::vector(vector &&origin) noexcept : vector() {
  swap(origin);
}

// assignment operator overload for initializer list constructor
template <class T>
vector<T> &vector<T>::operator=(
    std::initializer_list<value_type> const &items) {
  swap(vector<T>(items));
  return *this;
}

// assignment operator overload for copy object
template <class T>
vector<T> &vector<T>::operator=(const vector<T> &origin) {
  swap(vector<T>(origin));
  return *this;
}

// assignment operator overload for moving object
template <class T>
vector<T> &vector<T>::operator=(vector<T> &&origin) {
  swap(origin);
  return *this;
}

// destructor
template <class T>
vector<T>::~vector() {
  delete[] storage_;
}

// access specified element with bounds checking
template <class T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range{"Position is out of range."};
  return storage_[pos];
}

// access specified element
template <class T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return storage_[pos];
}

// access the first element
template <class T>
typename vector<T>::const_reference vector<T>::front() {
  return storage_[0];
}

// access the last element
template <class T>
typename vector<T>::const_reference vector<T>::back() {
  return storage_[size_ - 1];
}

// direct access to the underlying array
template <class T>
typename vector<T>::iterator vector<T>::data() {
  return storage_;
}

// returns an iterator to the beginning
template <class T>
typename vector<T>::iterator vector<T>::begin() {
  return storage_;
}

// returns an const iterator to the beginning
// template <class T>
// typename vector<T>::const_iterator vector<T>::begin() const noexcept {
//   const auto result = storage_;
//   return result;
// }

// returns an iterator to the end
template <class T>
typename vector<T>::iterator vector<T>::end() {
  return storage_ + size_;
}

// checks whether the container is empty
template <class T>
bool vector<T>::empty() {
  return size_ == 0;
}

// returns the number of elements
template <class T>
typename vector<T>::size_type vector<T>::size() const noexcept {
  return size_;
}

// returns the maximum possible number of elements
template <class T>
typename vector<T>::size_type vector<T>::max_size() const noexcept {
  return MAX_VECTOR_SIZE;
}

// allocate storage of size elements and copies current array elements to a
// newely allocated array
template <class T>
void vector<T>::reserve(size_type n) {
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

// returns the number of elements that can be held in currently allocated
// storage
template <class T>
typename vector<T>::size_type vector<T>::capacity() const noexcept {
  return capacity_;
}

// reduces memory usage by freeing unused memory
template <class T>
void vector<T>::shrink_to_fit() {
  s21::vector<T> tmp;
  tmp.reallocate(size_, size_, storage_);
  tmp.swap(*this);
}

// clears the contents
template <class T>
void vector<T>::clear() noexcept {
  for (size_type i = 0; i < size_; ++i) {
    storage_[i].~T();
  }
  size_ = 0;
}

// inserts elements into concrete pos and returns the iterator that points to
// the new element
template <class T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
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
template <class T>
template <class... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args &&...args) {
  auto it_pos = const_cast<iterator>(pos);
  for (auto &val : {args...}) {
    it_pos = insert(it_pos, val) + 1;
  }

  return it_pos - 1;
}

template <class T>
template <class... Args>
void vector<T>::insert_many_back(Args &&...args) {
  for (auto &val : {args...}) {
    push_back(val);
  }
}

// erases element at pos
template <class T>
void vector<T>::erase(iterator pos) {
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

// adds an element to the end
template <class T>
void vector<T>::push_back(const_reference value) {
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

// removes the last element
template <class T>
void vector<T>::pop_back() {
  storage_[--size_].~T();
}

// swaps the contents
template <class T>
void vector<T>::swap(vector<T> &v) {
  using std::swap;
  swap(size_, v.size_);
  swap(capacity_, v.capacity_);
  swap(storage_, v.storage_);
}

// HELPER method
template <class T>
void vector<T>::reallocate(size_type capacity, size_type size,
                           const iterator storage) {
  storage_ = new T[capacity];
  capacity_ = capacity;
  for (size_type i = 0; i < size; ++i) {
    storage_[i] = storage[i];
  }
  size_ = size;
}
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_H_
