class Node {
  int key;
  int value;
  Node *left = nullptr;
  Node *right = nullptr;
  Node(int key, int value) {
    this->key = key;
    this->value = value;
  };
  private:
    void insert(Node node, int key, int value);

};

void Node::insert(Node node, int key, int value) {
  if (key < node.key) {
    if (node.left == nullptr) {
      node.left = new Node(key, value);
    } else {
      insert(*node.left, key, value);
    }
  } else if (key >= node.key) {
    if (node.right == nullptr) {
      node.right = new Node(key, value);
    } else {
      insert(*node.right, key, value);
    }
  }
}