#ifndef S21_TREE_H
#define S21_TREE_H

#include <iostream>

/*
  HEADER FILE
*/


template <class T1, class T2>
class BSTree
{   
    // private attributes
    private:
        size_t size;
        size_t capacity;

    // public types of members
    public:
        using key_type = T1;
        using key_reference = T1 &;
        using data_type = T2;
        using data_reference = T1 &;
        using size_type = size_t;
        
    private:    // private methods
        
    public:     // public methods
        // Добавление пары (key, value) в дерево
        void insert(T1 key, T2 value);
        // Исключение из дерева значения по ключу
        void remove(T1 key);
        // Получение значения по ключу key
        T2 find(T1 key);
        // Структура узла дерева
    private:
        struct TreeNode
        {
            key_type key_;
            data_type data_;
            TreeNode *left_, *right_;
            TreeNode(key_type key, data_type data) {
                key_ = key;
                data_ = data;
                left_ = right_ = nullptr;
            }
        }
};

#endif  //  S21_TREE_H