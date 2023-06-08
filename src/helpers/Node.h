namespace s21 {

template <typename K, typename V = K>
class Node {
 public:
  K key;
  V value;
  Node<K, V> *left;
  Node<K, V> *right;
  Node<K, V> *parent;

  Node(K& key) 
    : key{key}, value{}, left{nullptr}, right{nullptr}, parent{nullptr} {}
  
  Node(K& key, V& value) 
    : key{key}, value{value}, left{nullptr}, right{nullptr}, parent{nullptr} {}

  Node() 
    : key(K{}), value(V{}), left{nullptr}, right{nullptr}, parent{nullptr} {}

};

}
