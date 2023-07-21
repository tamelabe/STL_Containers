#ifndef CPP2_S21_CONTAINERS_S21_MAP_H_
#define CPP2_S21_CONTAINERS_S21_MAP_H_

#include <initializer_list>
#include <limits>
#include <utility>
#include <vector>

#include "BTree.h"

namespace s21 {

template <typename KT, typename VT>
class Map {
  using difference_type = std::ptrdiff_t;
  using key_type = KT;
  using mapped_type = VT;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using tree_type = s21::BTree<KT, VT>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::const_iterator;
  using size_type = size_t;

 public:
  Map();
  explicit Map(std::initializer_list<value_type> const &);
  Map(const Map &);
  Map(Map &&);
  ~Map();
  Map &operator=(Map &&);
  VT &at(const KT &);
  iterator find(const KT &);
  VT &operator[](const KT &);
  iterator begin();
  iterator end();
  bool empty();
  size_type size() noexcept;
  size_type max_size() const noexcept;
  void clear();
  std::pair<iterator, bool> insert(const value_type &);
  std::pair<iterator, bool> insert(const KT &, const VT &);
  std::pair<iterator, bool> insert_or_assign(const KT &, const VT &);
  void erase(iterator);
  void swap(Map &);
  void merge(Map &);
  bool contains(const KT &);

  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  s21::BTree<KT, VT> tree_;
  size_type size_;
};

// default constructor, creates empty Map
template <typename KT, typename VT>
Map<KT, VT>::Map() : tree_(), size_(0) {}

// initializer list constructor,
// creates the Map initizialized using std::initializer_list
template <typename KT, typename VT>
Map<KT, VT>::Map(std::initializer_list<value_type> const &items)
    : tree_(), size_(0) {
  for (auto item : items) {
    tree_.insert(item.first, item.second);
    size_++;
  }
}

// copy constructor
template <typename KT, typename VT>
Map<KT, VT>::Map(const Map &other) : size_(0) {
  for (auto it = other.tree_.begin(); it != other.tree_.end(); ++it) {
    tree_.insert(it.getNode()->key, *it);
    size_++;
  }
}

// move constructor
template <typename KT, typename VT>
Map<KT, VT>::Map(Map &&other) : Map() {
  swap(other);
}

// destructor
template <typename KT, typename VT>
Map<KT, VT>::~Map() {
  if (size_ > 0 && tree_.getRoot()) {
    size_ = 0;
    tree_.destroy(tree_.getRoot());
  }
}

// assignment operator overload for moving object
template <typename KT, typename VT>
Map<KT, VT> &Map<KT, VT>::operator=(Map &&m) {
  swap(m);
}

// access specified element with bounds checking
template <typename KT, typename VT>
VT &Map<KT, VT>::at(const KT &key) {
  return *(tree_.search(key));
}

// find node by key
template <typename KT, typename VT>
typename Map<KT, VT>::iterator Map<KT, VT>::find(const KT &key) {
  return tree_.searchNode(key);
}

// access or insert specified element
template <typename KT, typename VT>
VT &Map<KT, VT>::operator[](const KT &key) {
  VT* result = tree_.search(key);
  if (result == nullptr) {
    insert(key, VT());
    result = &operator[](key);
  }
  return *result;
}

// returns an iterator to the beginning
template <typename KT, typename VT>
typename s21::Map<KT, VT>::iterator s21::Map<KT, VT>::begin() {
  return tree_.begin();
}

// returns an iterator to the end
template <typename KT, typename VT>
typename s21::Map<KT, VT>::iterator s21::Map<KT, VT>::end() {
  return tree_.end();
}

// checks whether the container is empty
template <typename KT, typename VT>
bool s21::Map<KT, VT>::empty() {
  return size_ == 0;
}

// returns the number of elements
template <typename KT, typename VT>
typename s21::Map<KT, VT>::size_type s21::Map<KT, VT>::size() {
  return size_;
}

// returns the maximum possible number of elements
template <typename KT, typename VT>
typename s21::Map<KT, VT>::size_type s21::Map<KT, VT>::max_size()
    const noexcept {
  return std::numeric_limits<difference_type>::max() / (sizeof(Node<KT, VT>));
}

// clears the contents
template <typename KT, typename VT>
void s21::Map<KT, VT>::clear() {
  tree_.destroy(tree_.getRoot());
  size_ = 0;
}

// inserts node and returns iterator to where the element is in the container
// and bool denoting whether the insertion took place
template <typename KT, typename VT>
std::pair<typename Map<KT, VT>::iterator, bool> s21::Map<KT, VT>::insert(
    const value_type &v) {
  return insert(v.first, v.second);
}

// inserts value by key and returns iterator to where the element is in the
// container and bool denoting whether the insertion took place
template <typename KT, typename VT>
std::pair<typename Map<KT, VT>::iterator, bool> s21::Map<KT, VT>::insert(
    const KT &key, const VT &value) {
  if (tree_.search(key) || size_ >= max_size()) {
    return std::pair<iterator, bool>{nullptr, false};
  }
  auto it = tree_.insert(key, value);
  size_++;
  return std::pair<iterator, bool>{it, true};
}

// inserts an element or assigns to the current element if the key already
// exists
template <typename KT, typename VT>
std::pair<typename Map<KT, VT>::iterator, bool>
s21::Map<KT, VT>::insert_or_assign(const KT &key, const VT &value) {
  auto it = tree_.searchNode(key);
  if (it.getNode() != nullptr) {
    (*this)[key] = value;
    return std::pair<iterator, bool>{it, true};
  }
  return insert(key, value);
}

// erases element at pos
template <typename KT, typename VT>
void s21::Map<KT, VT>::erase(iterator pos) {
  auto node = pos.getNode();
  tree_.removeNode(node, node->key);
  size_--;
}

// swaps the contents
template <typename KT, typename VT>
void s21::Map<KT, VT>::swap(Map &other) {
  using std::swap;
  swap(size_, other.size_);
  swap(tree_, other.tree_);
}

// splices nodes from another container
template <typename KT, typename VT>
void s21::Map<KT, VT>::merge(Map &other) {
  for (auto it = other.tree_.begin(); it != other.tree_.end(); ++it) {
    insert(it.getNode()->key, *it);
  }
}

// checks if there is an element with key equivalent to key in the container
template <typename KT, typename VT>
bool s21::Map<KT, VT>::contains(const KT &key) {
  return (tree_.search(key) != nullptr);
}

template <typename KT, typename VT>
template <class... Args>
std::vector<std::pair<typename Map<KT, VT>::iterator, bool>>
s21::Map<KT, VT>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool>> result;
  for (auto &val : {args...}) {
    result.push_back(insert(val.first, val.second));
  }
  return result;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_H_
