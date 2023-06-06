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

// #include <cstddef>
#include <iostream>
#include <string>
#include <utility>

namespace s21 {
// Структура узла дерева
template <class TP>
struct Node {
  TP key;
  Node<TP> *left;
  Node<TP> *right;
  Node<TP> *parent;

  // Конструктор с параметром
  Node(TP& key) 
    : key{key}, left{nullptr}, right{nullptr}, parent{nullptr} {}
  // Конструктор с const параметром
  Node(const TP& key) 
    : key{key}, left{nullptr}, right{nullptr}, parent{nullptr} {}
  // Конструктор по-умолчанию
  Node()
    : key(TP{}), left{nullptr}, right{nullptr}, parent{nullptr} {}

};

// Структура дерева
template <typename T>
class BSTree {
 public:
  using node_type = Node<T>;
  // constructor
  BSTree();
  // destructor
  // ~BSTree();
  // copy
  // BSTree(const BSTree& other);
  // BSTree<T, Compare>& operator=(BSTree&& other) noexcept;

  void insert(T data);
  // T find(T data);
  // Получение значения по ключу key
  // T2 find(T1 key);
  // private methods
  node_type *root = nullptr;

 private:
  void insert(node_type *, T data);
  // node_type *find(node_type *, T data);
  // node_type *successor(node_type *);
  // void remove(node_type *, T data);

};

template <typename T>
BSTree<T>::BSTree() : root(nullptr) {}

// template <typename T, typename Compare>
// BSTree<T, Compare>::BSTree(const BSTree &other) : {
//   
// };

// private
template <typename T>
void BSTree<T>::insert(BSTree<T>::node_type *node, T data) {
  
  if (root == nullptr) {
    root = new node_type(data);
    std::cout << "first: " << root->key.first << std::endl;
    std::cout << "second: " << root->key.second << std::endl;
    return;
  }
  
  if (data.first < node->key.first) {  // <
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

// public
template <typename T>
void BSTree<T>::insert(T data) {
  insert(root, data);
}

// template <typename T, typename Compare>
// typename BSTree<T, Compare>::node_type* BSTree<T, Compare>::find(BSTree<T, Compare>::node_type *node, T data) {
//   if (root == nullptr || data == root->key) {
//     return root;
//   }
//   if (Compare{}(data, node->key)) { // <
//       return find(node->left, data);
//   } else { // >=
//       return find(node->right, data);
//   }
// }

// template <typename T, typename Compare>
// T BSTree<T, Compare>::find(T data) {
//   BSTree<T, Compare>::node_type* result = find(root, data);
//   if (result != nullptr) {
//     return result->key;
//   }
// }


// // private
// template <class T1, class T2>
// Node<T1, T2> *BSTree<T, Compare>::successor(Node<T1, T2> *n) {
//   Node<T1, T2> *r = n->right;
//   while (r->left != nullptr) r = r->left;
//   return r;
// }

// private
// template <class T1, class T2>
// void BSTree<T, Compare>::remove(Node<T1, T2> *&n, T1 key) {
//   if (n == nullptr) {
//     return;
//   }
//   if (key == n->key_) {
//     if (n->left_ == nullptr || n->right_ == nullptr) {
//       Node<T1, T2> *child = (n->left != nullptr ? n->left_ : n->right_);
//       delete n;
//       n = child;
//     } else {
//       Node<T1, T2> *success = successor(n);
//       n->key = success->key_;
//       n->data = success->data_;
//       remove(n->right_, success->key_);
//     }
//     return;
//   }
//   if (key < n->key_) {
//     remove(n->left_, key);
//   } else {
//     remove(n->right_, key);
//   }
// }

// // public
// template <class T1, class T2>
// void BSTree<T, Compare>::remove(T1 key) {
//   remove(root, key);
// }

// // private
// template <class T1, class T2>
// Node<T1, T2> *BSTree<T, Compare>::find(T1 key, Node<T1, T2> *n) {
//   if (n == nullptr || key == n->key_) {
//     return n;
//   }
//   if (key < n->key_) {
//     return find(n->left_, key);
//   } else {
//     return find(n->right_, key);
//   }
// }
//
// // public
// template <class T1, class T2>
// T2 BSTree<T, Compare>::find(T1 key) {
//   Node<T1, T2> *n = find(key, root);
//   if (n != nullptr) {
//     return n->getData();
//   } else {
//     return T2{};
//   }
// }
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_TREE_H
