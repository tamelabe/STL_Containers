#include "s21_tree.h"

namespace s21 {
    template<typename Key, typename V>
    class CCompare {
      public:
        bool isLess(std::pair<Key, V> p1, std::pair<Key, V> p2) {
            return p1.first < p2.first;
        }
    };

    template<typename Key, typename V, typename Compare = std::less<Key>>
    class map : public s21::BSTree<std::pair<Key, V>, Compare> {
        V operator[](Key k) {
            find(std::make_pair(k, V{}));
        }

    };

    template<typename V, typename Compare = std::less<V>>
    class set : public s21::BSTree<V, Compare> {

    };
}
