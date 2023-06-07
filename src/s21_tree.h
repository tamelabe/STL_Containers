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

#ifndef CPP2_S21_CONTAINERS_S21_TREE_H
#define CPP2_S21_CONTAINERS_S21_TREE_H

#include "helpers/Node.h"

#include <iostream>
#include <string>
#include <utility>
#include <stack>

namespace s21 {

template <typename T>
class BSTree {
 
 public: 
  using node_type = Node<T>;

  BSTree();
  
  void insert(T);
  node_type *getRoot();
  void print(node_type *);

  class Iterator {
   public:
    explicit Iterator(Node<T>* node) {
      if (node) {
        stack.push(node);
        current = node;
      }
    }

    Iterator& operator++() {
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

    T& operator*() const {
      return current->value;
    }

    bool operator==(const Iterator& other) const {
      return current == other.current;
    }

    bool operator!=(const Iterator& other) const {
      return !(*this == other);
    }

   private:
    Node<T>* current;
    std::stack<Node<T>*> stack;
  };

  Iterator begin() const {
    return Iterator(root);
  }

  Iterator end() const {
    return Iterator(nullptr);
  }

 private:
  node_type *root = nullptr;
  void insert(node_type *, T);
};

template <typename T>
BSTree<T>::BSTree() : root(nullptr) {}

template <typename T>
typename BSTree<T>::node_type* BSTree<T>::getRoot() {
  return root;
}

template <typename T>
void BSTree<T>::insert(T data) {
  insert(root, data);
}

template <typename T>
void BSTree<T>::insert(T data) {
  insert(root, data);
}

template <typename T>
void BSTree<T>::print(node_type *node) {
  if (node == nullptr) {
    return;
  }
  std::cout << "key: " << node->value.first << std::endl;
  std::cout << "value: " << node->value.second << std::endl;
  print(node->left);
  print(node->right);
}

template <typename T>
void BSTree<T>::insert(BSTree<T>::node_type *node, T data) {
  
  if (root == nullptr) {
    root = new node_type(data);
    return;
  }
  
  if (std::less<T>{}(data, node->value)) {  // <
    if (node->left == nullptr) {
      node->left = new node_type(data);
    } else {
      insert(node->left, data);
    }
  } else {  // >=
    if (node->right == nullptr) {
      node->right = new node_type(data);
    } else {
      insert(node->right, data);
    }
  }
}



}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_TREE_H
