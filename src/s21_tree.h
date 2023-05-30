/**
Copyright 2023 darrpama@student.21-school.ru

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

using namespace std::string_literals;
namespace s21 {
// Структура узла дерева
template <class T1>
struct Node {
  T1 key;
  Node<T1> *left;
  Node<T1> *right;
  Node<T1> *parent;

  Node(const T1 key = T1{}, Node<T1> *left = nullptr, Node<T1> *right = nullptr,
       Node<T1> *parent = nullptr)
      : key{key}, left{left}, right{right}, parent{parent} {}
};

// Структура дерева
template <class T1, class T2>
class BSTree {
 public:
  using node_type = Node<std::pair<T1, T2>>;
  void insert(T1 key, T2 data);
  // void remove(T1 key);
  // Получение значения по ключу key
  // T2 find(T1 key);
  // private methods
  void printBT(std::string prefix, node_type *node, bool isLeft);
  void printBT(BSTree tree);

 private:
  void insert(node_type *, T1 key, T2 data);
  // Node<T1, T2> *find(T1 key, Node<T1, T2> *root);
  // node_type *successor(node_type *);
  // void remove(node_type *, T1 key);

  node_type *root = nullptr;
};

// private
template <class T1, class T2>
void BSTree<T1, T2>::insert(typename BSTree<T1, T2>::node_type *node, T1 key,
                            T2 data) {
  if (root == nullptr) {
    root = new node_type(std::make_pair(key, data));
    return;
  }
  if (key < node->key.first) {
    if (node->left == nullptr) {
      node->left = new node_type(std::make_pair(key, data));
    } else {
      insert(node->left, key, data);
    }
  } else if (key >= node->key.first) {
    if (node->right == nullptr) {
      node->right = new node_type(std::make_pair(key, data));
    } else {
      insert(node->right, key, data);
    }
  }
}

// public
template <class T1, class T2>
void BSTree<T1, T2>::insert(T1 key, T2 data) {
  insert(root, key, data);
}

template <class T1, class T2>
void BSTree<T1, T2>::printBT(std::string prefix,
                             typename BSTree<T1, T2>::node_type *node,
                             bool isLeft) {
  if (node != nullptr) {
    std::cout << prefix;

    std::cout << (isLeft ? "├──" : "└──");

    // print the value of the node
    std::cout << node->key.first << " " << node->key.second << std::endl;

    // enter the next tree level - left and right branch
    printBT(prefix + (isLeft ? "│   " : "    "), node->left, true);
    printBT(prefix + (isLeft ? "│   " : "    "), node->right, false);
  }
}

template <class T1, class T2>
void BSTree<T1, T2>::printBT(BSTree<T1, T2> tree) {
  printBT(std::string{}, tree.root, false);
}

// // private
// template <class T1, class T2>
// Node<T1, T2> *BSTree<T1, T2>::successor(Node<T1, T2> *n) {
//   Node<T1, T2> *r = n->right;
//   while (r->left != nullptr) r = r->left;
//   return r;
// }

// private
// template <class T1, class T2>
// void BSTree<T1, T2>::remove(Node<T1, T2> *&n, T1 key) {
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
// void BSTree<T1, T2>::remove(T1 key) {
//   remove(root, key);
// }

// // private
// template <class T1, class T2>
// Node<T1, T2> *BSTree<T1, T2>::find(T1 key, Node<T1, T2> *n) {
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
// T2 BSTree<T1, T2>::find(T1 key) {
//   Node<T1, T2> *n = find(key, root);
//   if (n != nullptr) {
//     return n->getData();
//   } else {
//     return T2{};
//   }
// }
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_TREE_H
