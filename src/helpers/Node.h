namespace s21 {

template <class T>
class Node {
 public:
  T value;
  Node<T> *left;
  Node<T> *right;
  Node<T> *parent;

  Node(T& value) 
      : value{value}, left{nullptr}, right{nullptr}, parent{nullptr} {}

  Node(const T& value) 
      : value{value}, left{nullptr}, right{nullptr}, parent{nullptr} {}

  Node()
      : value(T{}), left{nullptr}, right{nullptr}, parent{nullptr} {}

};

}
