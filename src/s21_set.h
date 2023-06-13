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
  using iterator        = SetIterator<key_type>;
  using const_iterator  = SetConstIterator<key_type>;
  using size_type       = size_t;

public:
  set();
  set(std::initializer_list<value_type> const &items);
// | set(const set &s);
// | set(set &&s);
// | ~set();
// | operator=(set &&s);

  // iterator begin();
  // iterator end();

  // bool empty();
  // size_type size();
  // size_type max_size();

  // void clear();
  // std::pair<iterator, bool> insert(const value_type& value);
  // void erase(iterator pos);
  // void swap(set& other);
  // void merge(set& other);

  // iterator find(const Key& key);
  // bool contains(const Key& key);

private:
  s21::BinaryTree<key_type, value_type> tree_;
  size_type size_;
};

template <typename KT>
s21::set<KT>::set() : tree_(), size_(0) {}

template <typename KT>
s21::set<KT>::set(std::initializer_list<value_type> const &items) : tree_(), size_(0) {
  for (auto item : items) {
    tree_.insert(item, 0);
    size_++;
  }
}

}  // namespace s21


// mintimir izvrachenec - on lubit VIM
#endif  // CPP2_S21_CONTAINERS_S21_SET_H_