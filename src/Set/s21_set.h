/**
Copyright 2023 darrpama

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
**/

#ifndef CPP2_S21_CONTAINERS_S21_SET_H_
#define CPP2_S21_CONTAINERS_S21_SET_H_

#include <limits>

#include "../Map/BTree.h"

namespace s21 {

template <typename KT>
class set {
  using key_type = KT;
  using value_type = KT;
  using reference = value_type &;
  using const_reference = const value_type &;
  using tree_type = s21::BTree<KT>;
  using iterator = typename tree_type::iterator;
  using const_iterator = const typename tree_type::iterator;
  using size_type = size_t;

 public:
  set();
  explicit set(std::initializer_list<value_type> const &);
  set(const set &s);
  set(set &&s);
  ~set();
  reference operator=(std::initializer_list<value_type> const &);
  reference operator=(const set &);
  reference operator=(set &&);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();

  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  iterator find(const KT &key);
  bool contains(const KT &key);

 private:
  tree_type tree_;
  size_type size_;
};

// Default constructor
template <typename KT>
s21::set<KT>::set() : tree_(), size_(0) {}

// Constructor for initializer list
template <typename KT>
s21::set<KT>::set(std::initializer_list<value_type> const &items)
    : tree_(), size_(0) {
  for (auto item : items) {
    tree_.insert(item, item);
    size_++;
  }
}

// Copy constructor
template <typename KT>
s21::set<KT>::set(const set &other) : size_(0) {
  for (auto it = other.tree_.begin(); it != other.tree_.end(); ++it) {
    tree_.insert(it.getNode()->key, *it);
    size_++;
  }
}

// Move constructor
template <typename KT>
s21::set<KT>::set(set &&other) : set() {
  swap(other);
}

// Destructor
template <typename KT>
s21::set<KT>::~set() {
  if (size_ > 0 && tree_.getRoot()) {
    size_ = 0;
    tree_.destroy(tree_.getRoot());
  }
}

// Getter size_
template <typename KT>
typename s21::set<KT>::size_type s21::set<KT>::size() {
  return size_;
}

// Getter maxsize
template <typename KT>
typename s21::set<KT>::size_type s21::set<KT>::max_size() {
  return ((std::numeric_limits<size_type>::max() / 2) - sizeof(s21::BTree<KT>) -
          sizeof(s21::Node<KT>)) /
         sizeof(s21::Node<KT>);
}

template <typename KT>
typename s21::set<KT>::reference s21::set<KT>::operator=(
    std::initializer_list<value_type> const &items) {
  swap(set<KT>(items));
  return *this;
}

template <typename KT>
typename s21::set<KT>::reference s21::set<KT>::operator=(const set &s) {
  swap(set<KT>(s));
  return *this;
}

template <typename KT>
typename s21::set<KT>::reference s21::set<KT>::operator=(set &&s) {
  swap(s);
  return *this;
}

// Method to find iterator to specific node
template <typename KT>
typename s21::set<KT>::iterator s21::set<KT>::find(const KT &key) {
  return tree_.searchNode(key);
}

// Returns iterator to begin
template <typename KT>
typename s21::set<KT>::iterator s21::set<KT>::begin() {
  return tree_.begin();
}

// Returns iterator after end node
template <typename KT>
typename s21::set<KT>::iterator s21::set<KT>::end() {
  return tree_.end();
}

// Method to check, is set empty
template <typename KT>
bool s21::set<KT>::empty() {
  return size_ == 0;
}

// Destroy the all set
template <typename KT>
void s21::set<KT>::clear() {
  tree_.destroy(tree_.getRoot());
  size_ = 0;
}

// Insert a new unique value into set
template <typename KT>
std::pair<typename s21::set<KT>::iterator, bool> s21::set<KT>::insert(
    const KT &value) {
  if (tree_.search(value) != nullptr) {
    return std::pair<iterator, bool>{nullptr, false};
  }
  auto it = tree_.insert(value, value);
  size_++;
  return std::pair<iterator, bool>{it, true};
}

// Delete one node by getting iterator
template <typename KT>
void s21::set<KT>::erase(typename s21::set<KT>::iterator pos) {
  auto node = pos.getNode();
  tree_.removeNode(node, node->key);
  size_--;
}

// Swap two sets
template <typename KT>
void s21::set<KT>::swap(set &other) {
  using std::swap;
  swap(size_, other.size_);
  swap(tree_, other.tree_);
}

// Merge two sets
template <typename KT>
void s21::set<KT>::merge(set &other) {
  for (auto it = other.tree_.begin(); it != other.tree_.end(); ++it) {
    insert(it.getNode()->key);
  }
}

// Check is key containing in set
template <typename KT>
bool s21::set<KT>::contains(const KT &key) {
  return (tree_.search(key) != nullptr);
}

}  // namespace s21

// mintimir izvrachenec - on lubit VIM
#endif  // CPP2_S21_CONTAINERS_S21_SET_H_
