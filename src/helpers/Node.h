namespace s21 {

template <typename KT, typename V = KT>
class Node {
 public:
  KT key;
  V value;
  Node<KT, V> *left;
  Node<KT, V> *right;
  Node<KT, V> *parent;

  Node(KT& key) 
    : key{key}, value{}, left{nullptr}, right{nullptr}, parent{nullptr} {}
  
  Node(KT& key, V& value) 
    : key{key}, value{value}, left{nullptr}, right{nullptr}, parent{nullptr} {}

  Node() 
    : key(KT{}), value(V{}), left{nullptr}, right{nullptr}, parent{nullptr} {}

};

}
