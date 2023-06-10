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

  BinaryTree();
  
  void insert(KT key, VT value);
  node_type *getRoot();
  VT* search(const KT& key);
  void print(node_type *);

  class iterator {
   public:
    explicit iterator(Node<KT, VT>* node) {
      if (node) {
        stack.push(node);
        current = node;
      }
    }

    iterator& operator++() {
      if (stack.empty()) {
        current = nullptr;
        return *this;
      }

      current = stack.top();
      stack.pop();

      if (current->right) {
        stack.push(current->right);
      }
      if (current->left) {
        stack.push(current->left);
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

   private:
    node_type* current;
    std::stack<node_type*> stack;
  };

  class const_iterator {
   public:
    explicit const_iterator(Node<KT, VT>* node) {
      if (node) {
        stack.push(node);
        current = node;
      }
    }

    const_iterator& operator++() {
      if (stack.empty()) {
        current = nullptr;
        return *this;
      }

      current = stack.top();
      stack.pop();

      if (current->right) {
        stack.push(current->right);
      }
      if (current->left) {
        stack.push(current->left);
      }

      return *this;
    }

    node_type& operator*() const {
      return current->value;
    }

    bool operator==(const const_iterator& other) const {
      return current == other.current;
    }

    bool operator!=(const const_iterator& other) const {
      return !(*this == other);
    }

   private:
    node_type* current;
    std::stack<node_type*> stack;
  };

  iterator begin() const {
    return iterator(root);
  }

  iterator end() const {
    return iterator(nullptr);
  }

 private:
  node_type *root = nullptr;
  void insert(node_type *, KT, VT);
};

template <typename KT, typename VT>
BinaryTree<KT, VT>::BinaryTree() : root(nullptr) {}

template <typename KT, typename VT>
typename BinaryTree<KT, VT>::node_type* BinaryTree<KT, VT>::getRoot() {
  return root;
}

template <typename KT, typename VT>
VT* BinaryTree<KT, VT>::search(const KT& key) {
  node_type *current = root;
  while (current) {
    if (current->key == key) {
      return &current->value;
    } else if (std::less<KT>{}(key, current->key)) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return nullptr;
}

template <typename KT, typename VT>
void BinaryTree<KT, VT>::insert(KT key, VT value) {
  insert(root, key, value);
}

template <typename KT, typename VT>
void BinaryTree<KT, VT>::insert(BinaryTree<KT, VT>::node_type *node, KT key, VT value) {
  if (root == nullptr) {
    root = new node_type(key, value);
    return;
  }
  if (std::less<KT>{}(key, node->key)) {  // <
    if (node->left == nullptr) {
      node->left = new node_type(key, value);
    } else {
      insert(node->left, key, value);
    }
  } else {  // >=
    if (node->right == nullptr) {
      node->right = new node_type(key, value);
    } else {
      insert(node->right, key, value);
    }
  }
}

template <typename KT, typename VT>
void BinaryTree<KT, VT>::print(node_type *node) {
  if (node == nullptr) {
    return;
  }
  std::cout << "key: " << node->value.first << std::endl;
  std::cout << "value: " << node->value.second << std::endl;
  print(node->left);
  print(node->right);
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_TREE_H
