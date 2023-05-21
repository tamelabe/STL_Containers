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
        using value_type = T2;
        using value_reference = T1 &;
        using size_type = size_t;
        // private methods
    private:

        // public methods
    public:
        // Добавление пары (key, value) в дерево
        void insert(T1 key, T2 value);
        // Исключение из дерева значения по ключу
        void remove(T1 key);
        // Получение значения по ключу key
        T2 find(T1 key);
};

#endif  //  S21_TREE_H