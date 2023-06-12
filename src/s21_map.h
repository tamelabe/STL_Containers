#ifndef CPP2_S21_CONTAINERS_S21_MAP_H_
#define CPP2_S21_CONTAINERS_S21_MAP_H_

#include "helpers/BinaryTree.h"

#include <initializer_list>
#include <utility>
#include <limits>

namespace s21 {
  
template<typename KT, typename VT>
class map {
  using difference_type = std::ptrdiff_t;
  using key_type        = KT;
  using mapped_type     = VT;
  using value_type      = std::pair<const key_type, mapped_type>;
  using reference       = value_type &;
  using const_reference = const value_type &;
  using tree_type       = s21::BinaryTree<KT, VT>;
  using iterator        = typename tree_type::iterator;
  // using const_iterator  = typename tree_type::const_iterator;
  using size_type       = size_t;

 public:
  // Member functions (constructors, destructor)
  map();
  explicit map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  ~map();
  map& operator=(map &&m);

  // Element access methods
  VT& at(const KT& key);
  VT& operator[](const KT& key);

  // Iterators
  iterator begin();
  iterator end();

  // // Capacity
  bool empty();
  size_type size();
  size_type max_size() const noexcept;

  // // Modifiers
  // void clear();
  // std::pair<iterator, bool> insert(const value_type& value);
  // std::pair<iterator, bool> insert(const Key& key, const T& obj);
  // std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  // void erase(iterator pos);
  void swap(map& other);
  // void merge(map& other);

  // // Lookup
  // bool contains(const Key& key);

  // helpers
  void print_map();

 private:
  s21::BinaryTree<KT, VT> tree_;
  size_type size_;
};

// Base constructor
template <typename KT, typename VT>
s21::map<KT, VT>::map() : tree_(), size_(0) {}

// Initializer list constructor
template <typename KT, typename VT>
s21::map<KT, VT>::map(std::initializer_list<value_type> const &items) : tree_(), size_(0) {
  for (auto item : items) {
    tree_.insert(item.first, item.second);
    size_++;
  }
}

// Copy constructor
template <typename KT, typename VT>
s21::map<KT, VT>::map(const map &other) : size_(0) {
  for (auto it = other.tree_.begin(); it != other.tree_.end(); ++it) {
    tree_.insert(it.getNode()->key, *it);
    size_++;
  }
}

// Move constructor
template <typename KT, typename VT>
s21::map<KT, VT>::map(map &&other) : map() {
  swap(other);
}

// Destructor
template <typename KT, typename VT>
s21::map<KT, VT>::~map() {
  size_ = 0;
  tree_.destroy(tree_.getRoot());
}

// Move operator
template <typename KT, typename VT>
s21::map<KT, VT>& s21::map<KT, VT>::operator=(map &&m) {
  swap(m);
}

// At element access method
template <typename KT, typename VT>
VT& s21::map<KT, VT>::at(const KT& key) {
  return *(tree_.search(key));
}

// operator [] access method
template <typename KT, typename VT>
VT& s21::map<KT, VT>::operator[](const KT& key) {
  return *(tree_.search(key));
}

// returns an iterator to the beginning
template <typename KT, typename VT>
typename s21::map<KT, VT>::iterator
s21::map<KT, VT>::begin() {
  return tree_.begin();
}

// returns an iterator to the end
template <typename KT, typename VT>
typename s21::map<KT, VT>::iterator
s21::map<KT, VT>::end() {
  return tree_.end();
}

// Empty
template <typename KT, typename VT>
bool s21::map<KT, VT>::empty() {
  return size_ == 0;
}

// Size
template <typename KT, typename VT>
typename s21::map<KT, VT>::size_type 
s21::map<KT, VT>::size() {
  return size_;
}

// Max size
template <typename KT, typename VT>
typename s21::map<KT, VT>::size_type 
s21::map<KT, VT>::max_size() const noexcept {
  return std::numeric_limits<difference_type>::max() / (sizeof(Node<KT, VT>));
}

// swaps the contents
template <typename KT, typename VT>
void s21::map<KT, VT>::swap(map &other) {
  using std::swap;
  swap(size_, other.size_);
  swap(tree_, other.tree_);
}

// HELPER: print_map
template <typename KT, typename VT>
void s21::map<KT, VT>::print_map() {
  tree_.print(tree_.getRoot());
}


}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_H_
