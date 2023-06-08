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

template <typename K, typename V = K>
class BinaryTree {
 
 public: 
  using node_type = Node<K, V>;

  BinaryTree();
  
  void insert(K key, V value);
  node_type *getRoot();
  void print(node_type *);
  node_type *search();

  class iterator {
   public:
    explicit iterator(Node<K, V>* node) {
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

    V& operator*() const {
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
    explicit const_iterator(Node<K, V>* node) {
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
  void insert(node_type *, K, V);
};

template <typename K, typename V>
BinaryTree<K, V>::BinaryTree() : root(nullptr) {}

template <typename K, typename V>
typename BinaryTree<K, V>::node_type* BinaryTree<K, V>::getRoot() {
  return root;
}

template <typename K, typename V>
void BinaryTree<K, V>::insert(K key, V value) {
  insert(root, key, value);
}

template <typename K, typename V>
typename BinaryTree<K, V>::node_type* BinaryTree<K, V>::search() {
  return nullptr;
}

template <typename K, typename V>
void BinaryTree<K, V>::print(node_type *node) {
  if (node == nullptr) {
    return;
  }
  std::cout << "key: " << node->value.first << std::endl;
  std::cout << "value: " << node->value.second << std::endl;
  print(node->left);
  print(node->right);
}

template <typename K, typename V>
void BinaryTree<K, V>::insert(BinaryTree<K, V>::node_type *node, K key, V value) {
  
  if (root == nullptr) {
    root = new node_type(key, value);
    return;
  }
  
  if (std::less<K>{}(key, node->key)) {  // <
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



}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_TREE_H
