#ifndef CPP2_S21_CONTAINERS_S21_MAP_H_
#define CPP2_S21_CONTAINERS_S21_MAP_H_

#include <initializer_list>
#include <utility>
#include <limits>

#include "BTree.h"

#define TREE_MAX_SIZE 1024

namespace s21 {
  
template<typename KT, typename VT>
class map {
  using difference_type = std::ptrdiff_t;
  using key_type        = KT;
  using mapped_type     = VT;
  using value_type      = std::pair<const key_type, mapped_type>;
  using reference       = value_type &;
  using const_reference = const value_type &;
  using tree_type       = s21::BTree<KT, VT>;
  using iterator        = typename tree_type::iterator;
  // using const_iterator  = typename tree_type::const_iterator;
  using size_type       = size_t;

 public:
  //
  map() : tree_(), size_(0) {}

  //
  explicit map(std::initializer_list<value_type> const &items) : tree_(), size_(0) {
    for (auto item : items) {
      tree_.insert(item.first, item.second);
      size_++;
    }
  }

  //
  map(const map &other) : size_(0) {
    for (auto it = other.tree_.begin(); it != other.tree_.end(); ++it) {
      tree_.insert(it.getNode()->key, *it);
      size_++;
    }
  }

  //
  map(map &&other) : map() {
    swap(other);
  }

  //
  ~map() {
    if (size_ > 0 && tree_.getRoot()) {
      size_ = 0;
      tree_.destroy(tree_.getRoot());
    }
  }

  //
  map& operator=(map &&m) {
    swap(m);
  }

  //
  VT& at(const KT& key) {
    return *(tree_.search(key));
  }

  //
  iterator find(const KT& key) {
    return tree_.searchNode(key);
  }

  //
  VT& operator[](const KT& key) {
    return at(key);
  }

  //
  iterator begin() {
    return tree_.begin();
  }

  //
  iterator end() {
    return tree_.end();
  }

  //
  bool empty() {
    return size_ == 0;
  }

  //
  size_type size() {
    return size_;
  }

  //
  size_type max_size() const noexcept {
    return TREE_MAX_SIZE;  // TODO: 
    // return std::numeric_limits<difference_type>::max() / (sizeof(Node<KT, VT>));
  }

  //
  void clear() {
    tree_.destroy(tree_.getRoot());
    size_ = 0;
  }

  //
  std::pair<iterator, bool> insert(const value_type& v) {
    return insert(v.first, v.second);
  }

  std::pair<iterator, bool> insert(const KT& key, const VT& value) {
    if (tree_.search(key) != nullptr) {
      return std::pair<iterator, bool> {nullptr, false};
    }
    if (size_ >= TREE_MAX_SIZE) {
      return std::pair<iterator, bool> {nullptr, false};
    }
    auto it = tree_.insert(key, value);
    size_++;
    return std::pair<iterator, bool> {it, true};
  }

  //
  std::pair<iterator, bool> insert_or_assign(const KT& key, const VT& value) {
    auto it = tree_.searchNode(key);
    if (it.getNode() != nullptr) {
      (*this)[key] = value;
      return std::pair<iterator, bool> {it, true};
    }
    return insert(key, value);
  }

  //
  void erase(iterator pos) {
    auto node = pos.getNode();
    tree_.removeNode(node, node->key);
    size_--;
  }

  //
  void swap(map &other) {
    using std::swap;
    swap(size_, other.size_);
    swap(tree_, other.tree_);
  }

  //
  void merge(map &other) {
    for (auto it = other.tree_.begin(); it != other.tree_.end(); ++it) {
      insert(it.getNode()->key, *it);
    }
  }

  //
  bool contains(const KT& key) {
    return (tree_.search(key) != nullptr);
  }

  // helpers
  void print_map() {
    tree_.print(tree_.getRoot());
  }

 private:
  s21::BTree<KT, VT> tree_;
  size_type size_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_H_
