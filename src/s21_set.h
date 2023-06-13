#ifndef CPP2_S21_CONTAINERS_S21_SET_H_
#define CPP2_S21_CONTAINERS_S21_SET_H_
#include "helpers/BinaryTree.h"

namespace s21 {

template<typename KT>
class set {
  using key_type        = KT;
  using value_type      = KT;
  using reference       = value_type &;
  using const_reference = const value_type &;
  using tree_type       = s21::BinaryTree<KT>;
  using iterator        = typename tree_type::iterator;
  // using const_iterator  = SetConstIterator<key_type>;
  using size_type       = size_t;

public:
  set();
  explicit set(std::initializer_list<value_type> const &items);
//  set(const set &s);
//  set(set &&s);
  ~set();
//  operator=(set &&s);

  iterator begin();
  iterator end();

  bool empty();
  size_type size();
  // size_type max_size();

  // void clear();
  // std::pair<iterator, bool> insert(const value_type& value);
  // void erase(iterator pos);
  // void swap(set& other);
  // void merge(set& other);

  iterator find(const KT& key);
  // bool contains(const Key& key);

private:
  s21::BinaryTree<key_type, value_type> tree_;
  size_type size_;
};

// Default constructor
template <typename KT>
s21::set<KT>::set() : tree_(), size_(0) {}

// Constructor for initializer list
template <typename KT>
s21::set<KT>::set(std::initializer_list<value_type> const &items) : tree_(), size_(0) {
  for (auto item : items) {
    tree_.insert(item, item);
    size_++;
  }
}

// Destructor
template <typename KT>
s21::set<KT>::~set() {
  if (size_ > 0 && tree_.getRoot()) {
    size_ = 0;
    tree_.destroy(tree_.getRoot());
  }
}

template <typename KT>
typename s21::set<KT>::size_type
s21::set<KT>::size() {
  return size_;
}

template <typename KT>
typename s21::set<KT>::iterator
s21::set<KT>::find(const KT& key) {
  return tree_.searchNode(key);
}

template <typename KT>
typename s21::set<KT>::iterator
s21::set<KT>::begin() {
  return tree_.begin();
}

template <typename KT>
typename s21::set<KT>::iterator
s21::set<KT>::end() {
  return tree_.end();
}

template <typename KT>
bool s21::set<KT>::empty() {
  return size_ == 0;
}


}  // namespace s21


// mintimir izvrachenec - on lubit VIM
#endif  // CPP2_S21_CONTAINERS_S21_SET_H_