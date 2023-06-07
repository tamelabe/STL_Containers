#include "s21_tree.h"
#include "helpers/MapIterator.h"
#include "helpers/MapConstIterator.h"

namespace s21 {
  
template<typename Key, typename T>
class map {
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = MapIterator<key_type, mapped_type>;
  using const_iterator = MapConstIterator<key_type, mapped_type>;
  using size_type = size_t;

 public:
  // Member functions (constructors, destructor)
  map();
  map(std::initializer_list<value_type> const &items);
  // map(const map &m);
  // map(map &&m);
  // ~map();
  // Map& operator=(map &&m);

  // // Element access methods
  T& at(const Key& key);
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
  s21::BSTree<std::pair<Key, T>> tree_;
  size_type size_;
  
};

template <typename Key, typename T>
s21::map<Key, T>::map()  : tree_(), size_() {}

template <typename Key, typename T>
s21::map<Key, T>::map(std::initializer_list<value_type> const &items) : tree_(), size_() {
  for (auto item : items) {
    tree_.insert(item);
    size_++;
  }
}

template <typename Key, typename T>
typename s21::map<Key, T>::size_type 
s21::map<Key, T>::size() {
  return size_;
}

template <typename Key, typename T>
T& at(const Key& key) {
  tree_.
}

template <typename Key, typename T>
std::pair<MapIterator<Key, T>, bool> insert(const std::pair<const Key, T>& value) {}

template <typename Key, typename T>
void s21::map<Key, T>::print_map() {
  tree_.print(tree_.getRoot());
}

}  // namespace s21
