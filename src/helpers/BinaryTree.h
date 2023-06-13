/**
Copyright 2023 darrpama@student.21-school.ru, myregree@student.21-school.ru

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

#ifndef CPP2_S21_CONTAINERS_BINARY_TREE_H
#define CPP2_S21_CONTAINERS_BINARY_TREE_H

#include "Node.h"

#include <iostream>
#include <string>
#include <utility>
#include <stack>

namespace s21 {

template <typename KT, typename VT = KT>
class BinaryTree {
 
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
      } else {
        Node<KT, VT>* prev = current;
        current = current->parent;
        while (current && current->right == prev) {
            prev = current;
            current = current->parent;
        }
      }
      return *this;
    }

    VT& operator*() const {
      return current->value;
    }

    bool operator==(const iterator& other) const {
      return current == other.current;
    }

    bool operator!=(const iterator& other) const {
      return !(*this == other);
    }

    node_type* getNode() {
      return current;
    }

   private:
    node_type* current;
  };

  BinaryTree();
  
  iterator insert(KT key, VT value);
  node_type *getRoot();
  VT* search(const KT& key);
  iterator searchNode(const KT& key);
  void print(node_type *);
  void destroy(node_type *node);

  // TODO: const_iterator

  iterator begin() const {
    if (root == nullptr) {
      return iterator(root);
    }
    node_type *current = root;
    while (current->left) {
      current = current->left;
    }
    return iterator(current);
  }

  iterator end() const {
    return iterator(nullptr);
  }

 private:
  node_type *root;

  iterator insert(node_type *, KT, VT);
};

template <typename KT, typename VT>
BinaryTree<KT, VT>::BinaryTree() : root(nullptr) {}

// public
template <typename KT, typename VT>
typename BinaryTree<KT, VT>::iterator
BinaryTree<KT, VT>::insert(KT key, VT value) {
  return insert(root, key, value);
}

template <typename KT, typename VT>
void BinaryTree<KT, VT>::destroy(node_type *node) {
  if (!node) {
      return;
  }
  destroy(node->left);
  destroy(node->right);

  delete node;
}

// private
template <typename KT, typename VT>
typename BinaryTree<KT, VT>::iterator 
BinaryTree<KT, VT>::insert(BinaryTree<KT, VT>::node_type *node, KT key, VT value) {
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

template <typename KT, typename VT>
typename BinaryTree<KT, VT>::node_type* 
BinaryTree<KT, VT>::getRoot() {
  return root;
}

template <typename KT, typename VT>
VT* BinaryTree<KT, VT>::search(const KT& key) {
  node_type *current = root;
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

template <typename KT, typename VT>
typename BinaryTree<KT, VT>::iterator 
BinaryTree<KT, VT>::searchNode(const KT& key) {
  node_type *current = root;
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

template <typename KT, typename VT>
void BinaryTree<KT, VT>::print(node_type *node) {
  if (node == nullptr) {
    return;
  }
  std::cout << "key: " << node->key << std::endl;
  std::cout << "value: " << node->value << std::endl;
  print(node->left);
  print(node->right);
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_TREE_H
