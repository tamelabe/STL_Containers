#include "s21_tree.h"

namespace s21 {

template<typename K, typename T>
class MapIterator {

};

template<typename K, typename T>
class MapConstIterator {
    
};

template<typename Key, typename T>
class map : public s21::BSTree<std::pair<Key, T>> {
  
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
  // map(std::initializer_list<value_type> const &items);
  // map(const map &m);
  // map(map &&m);
  // ~map();
  // Map& operator=(map &&m);

  // // Element access methods
  // T& at(const Key& key);
  // T& operator[](const Key& key);
  // // V operator[](Key k) {
  // //     return find(std::make_pair(k, V{}));
  // // }

  // // Iterators
  // iterator begin();
  // iterator end();

  // // Capacity
  // bool empty();
  // size_type size();
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
  void print_tree(typename s21::Node<std::pair<Key, T>>);
};

template <typename Key, typename T>
s21::map<Key, T>::map() {
  
}

template <typename Key, typename T>
void s21::map<Key, T>::print_map() {
  print_tree(*this->root);
}

template <typename Key, typename T>
void s21::map<Key, T>::print_tree(typename s21::Node<std::pair<Key, T>> node) {
  if (node == nullptr) {
    return;
  }

  std::cout << "key: " << node.key->first << std::endl;
  std::cout << "value: " << node.key->second << std::endl;

  print_tree(node->left);
  print_tree(node->right);
}


}  // namespace s21
