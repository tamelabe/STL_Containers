#ifndef CPP2_S21_CONTAINERS_BINARY_TREE_H
#define CPP2_S21_CONTAINERS_BINARY_TREE_H

#include <stack>
#include <string>
#include <utility>

#include "Node.h"

namespace s21 {

template <typename KT, typename VT = KT>
class BTree {
 public:
  using node_type = Node<KT, VT>;

  class iterator {
   public:
    explicit iterator(Node<KT, VT>* node) : current(nullptr) {
      if (node) {
        current = node;
      }
    }

    iterator& operator++() {
      if (!current) {
        return *this;
      }
      if (current->right) {
        current = current->right;
        while (current->left) {
          current = current->left;
        }
        return *this;
      }
      Node<KT, VT>* prev = current;
      current = current->parent;
      while (current && current->right == prev) {
        prev = current;
        current = current->parent;
      }
      return *this;
    }

    VT& operator*() const { return current->value; }

    bool operator==(const iterator& other) const {
      return current == other.current;
    }

    bool operator!=(const iterator& other) const { return !(*this == other); }

    node_type* getNode() { return current; }

   private:
    node_type* current;
  };

  class const_iterator {
   public:
    explicit const_iterator(Node<KT, VT>* node) : current(nullptr) {
      if (node) {
        current = node;
      }
    }

    const_iterator& operator++() {
      if (!current) {
        return *this;
      }
      if (current->right) {
        current = current->right;
        while (current->left) {
          current = current->left;
        }
        return *this;
      }
      Node<KT, VT>* prev = current;
      current = current->parent;
      while (current && current->right == prev) {
        prev = current;
        current = current->parent;
      }
      return *this;
    }

    VT& operator*() const { return current->value; }

    bool operator==(const iterator& other) const {
      return current == other.current;
    }

    bool operator!=(const iterator& other) const { return !(*this == other); }

    node_type* getNode() { return current; }

   private:
    node_type* current;
  };

  BTree() : root(nullptr) {}

  iterator insert(KT key, VT value) { return insert(root, key, value); }

  node_type* getRoot() { return root; }

  VT* search(const KT& key) {
    node_type* current = root;
    while (current) {
      if (current->key == key) {
        return &current->value;
      }
      if (std::less<KT>{}(key, current->key)) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return nullptr;
  }

  iterator searchNode(const KT& key) {
    node_type* current = root;
    while (current) {
      if (current->key == key) {
        return iterator(current);
      }
      if (std::less<KT>{}(key, current->key)) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
    return iterator(nullptr);
  }

  void removeNode(node_type* node, KT key) {
    if (node == nullptr) {
      return;
    }
    // case 1
    if (node->hasNoChild()) {
      if (node->key != key) {
        auto dNode = searchNode(key).getNode();
        node->swap(*dNode);
      }
      updateParent(node, nullptr);
      delete node;
      return;
    }
    // case 2
    if (node->hasOneChild()) {
      node_type* successor = (node->left != nullptr) ? node->left : node->right;
      removeNode(successor, key);
    }
    // case 3
    if (node->hasTwoChild()) {
      if (node->key > key) {
        removeNode(node->left, key);
      } else {
        removeNode(node->right, key);
      }
    }
  }

  void destroy(node_type* node) {
    if (!node) {
      return;
    }
    destroy(node->left);
    destroy(node->right);

    delete node;
  }

  iterator begin() const {
    if (root == nullptr) {
      return iterator(root);
    }
    node_type* current = root;
    while (current->left) {
      current = current->left;
    }
    return iterator(current);
  }

  iterator end() const { return iterator(nullptr); }

  void print(node_type* node) {
    if (node == nullptr) {
      return;
    }
    std::cout << "NODE: " << node->key << " value: " << node->value
              << " parent: "
              << ((node->parent != nullptr) ? node->parent->key : 0)
              << std::endl;
    print(node->left);
    print(node->right);
  }

 private:
  node_type* root;

  void updateParent(node_type* node, node_type* successor) {
    (node->key == node->parent->left->key) ? node->parent->left = successor
                                           : node->parent->right = successor;
  }

  iterator insert(node_type* node, KT key, VT value) {
    if (root == nullptr) {
      root = new node_type(key, value, *node);
      return iterator(root);
    }
    if (std::less<KT>{}(key, node->key)) {  // <
      if (node->left == nullptr) {
        node->left = new node_type(key, value, *node);
        return iterator(node->left);
      } else {
        return insert(node->left, key, value);
      }
    } else {  // >=
      if (node->right == nullptr) {
        node->right = new node_type(key, value, *node);
        return iterator(node->right);
      } else {
        return insert(node->right, key, value);
      }
    }
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_TREE_H
