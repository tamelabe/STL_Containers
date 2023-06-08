#ifndef CPP2_S21_CONTAINERS_S21_MAP_H_
#define CPP2_S21_CONTAINERS_S21_MAP_H_

#include "helpers/BinaryTree.h"

#include <initializer_list>
#include <utility>

namespace s21 {
  
template<typename KT, typename VT>
class map {
  using key_type        = KT;
  using mapped_type     = VT;
  using value_type      = std::pair<const key_type, mapped_type>;
  using reference       = value_type &;
  using const_reference = const value_type &;
  using tree_type       = s21::BinaryTree<KT, VT>;
  using iterator        = typename tree_type::iterator;
  using const_iterator  = typename tree_type::const_iterator;
  using size_type       = size_t;

 public:
  // Member functions (constructors, destructor)
  map();
  explicit map(std::initializer_list<value_type> const &items);
  // map(const map &m);
  // map(map &&m);
  // ~map();
  // Map& operator=(map &&m);

  // // Element access methods
  // VT& at(const KT& key);
  // T& operator[](const Key& key);
  // // V operator[](Key k) {
  // //     return find(std::make_pair(k, V{}));
  // // }

  // // Iterators
  // iterator begin();
  // iterator end();

  // // Capacity
  // bool empty();
  size_type size();
  // size_type max_size();

  // // Modifiers
  // void clear();
  // std::pair<iterator, bool> insert(const value_type& value);
  // std::pair<iterator, bool> insert(const Key& key, const T& obj);
  // std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  // void erase(iterator pos);
  // void swap(map& other);
  // void merge(map& other);

  // // Lookup
  // bool contains(const Key& key);

  // helpers
  void print_map();

 private:
  s21::BinaryTree<KT, VT> tree_;
  size_type size_;
};

template <typename KT, typename VT>
s21::map<KT, VT>::map()  : tree_(), size_(0) {}

template <typename KT, typename VT>
s21::map<KT, VT>::map(std::initializer_list<value_type> const &items) : tree_(), size_(0) {
  for (auto item : items) {
    tree_.insert(item.first, item.second);
    size_++;
  }
}

template <typename KT, typename VT>
typename s21::map<KT, VT>::size_type 
s21::map<KT, VT>::size() {
  return size_;
}

// template <typename KT, typename VT>
// VT& s21::map<KT, VT>::at(const KT& key) {
//   return NULL;
// }

template <typename KT, typename VT>
void s21::map<KT, VT>::print_map() {
  tree_.print(tree_.getRoot());
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_H_
