#include "s21_tree.h"

namespace s21 {

template<typename V, typename Compare = std::less<V>>
class set : public s21::BSTree<V, Compare> {

};


}
