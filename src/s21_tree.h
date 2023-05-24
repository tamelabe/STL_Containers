#ifndef S21_TREE_H
#define S21_TREE_H

#include <iostream>

/*
  HEADER FILE
*/

// Структура узла дерева
template <class T1, class T2>
class Node
{
    T1 key_;
    T2 data_;
    size_t size_;
    Node<T1, T2> *left_;
    Node<T1, T2> *right_;
    Node<T1, T2> *parent_;

    Node(T1 key, T2 data) {
        key_ = key;
        data_ = data;
        left_ = right_ = nullptr;
    }
};

// Структура дерева
template <class T1, class T2>
class BSTree
{   
    // private attributes
    private:
        size_t size;
        size_t capacity;
        Node <T1, T2>* root;

    // public methods
    public:
        // Добавление пары (key, value) в дерево
        void insert(T1 key, T2 data);
        // Исключение из дерева значения по ключу
        void remove(T1 key);
        // Получение значения по ключу key
        T2 find(T1 key);
        // Рекурсивный обход с выводом значений
        void traverse(Node<T1, T2> *n);
    // private methods
    private:
        void insert(Node<T1, T2> *&n, T1 key, T2 data);
        Node<T1, T2> *find(T1 key, Node<T1, T2> *root);
        Node<T1, T2> *successor(Node<T1, T2> *n);
        void remove(Node<T1, T2> *&n, T1 key);
};

#endif  //  S21_TREE_H