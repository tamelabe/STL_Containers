namespace s21 {

template <typename KT, typename VT = KT>
class Node {
 public:
  KT key;
  VT value;
  Node<KT, VT> *left;
  Node<KT, VT> *right;
  Node<KT, VT> *parent;

  explicit Node(KT& key) 
    : key{key}, value{}, left{nullptr}, right{nullptr}, parent{nullptr} {}
  
  Node(KT& key, VT& value, Node<KT, VT>& parent) 
    : key{key}, value{value}, left{nullptr}, right{nullptr}, parent(&parent) {}

  Node() 
    : key(KT{}), value(VT{}), left{nullptr}, right{nullptr}, parent{nullptr} {}

};

}
