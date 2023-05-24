#include "s21_tree.h"

// private
template<class T1, class T2>
void BSTree<T1, T2>::insert(Node<T1, T2> *&n, T1 key, T2 data)
{
    if (n == nullptr) {
        n = new Node(key, data);
    } else if (key < n->key_) {
        insert(n->left_, key, data);
    } else {
        insert(n->right_, key, data);
    }
}

// public
template<class T1, class T2>
void BSTree<T1, T2>::insert(T1 key, T2 data)
{
    insert(root, key, data);
}

// private
template<class T1, class T2>
Node<T1, T2> *BSTree<T1, T2>::successor(Node<T1, T2> *n)
{
    Node *r = n->right;
    while (r->left != nullptr)
        r = r->left;
    return r;
}

// private
template<class T1, class T2>
void BSTree<T1, T2>::remove(Node<T1, T2> *&n, T1 key)
{
    if (n == nullptr) {
        return;
    }
    if (key == n->key_) {
        if (n->left_ == nullptr || n->right_ == nullptr) {
            Node *child = (n->left != nullptr ?
            n->left_
            :
            n->right_);
            delete n;
            n = child;
        } else {
            Node<T1, T2> *success = successor(n);
            n->key = success->key_;
            n->data = success->data_;
            remove(n->right_, success->key_)
        }
        return;
    }
    if (key < n->key_) {
        remove(n->left_, key);
    } else {
        remove(n->right_, key);
    }
}

// public
template<class T1, class T2>
void BSTree<T1, T2>::remove(T1 key)
{
    remove(root, key);
}

// public
template<class T1, class T2>
void BSTree<T1, T2>::traverse(Node<T1, T2> *n)
{
    if (n == nullptr) {
        return;
    }
    traverse(n->left_);
    // do something
    traverse(n->right_);
}


// private
template<class T1, class T2>
Node<T1, T2> *BSTree<T1, T2>::find(T1 key, Node<T1, T2> *n)
{
    if (n == nullptr || key == n->key_) {
        return n;
    }
    if (key < n->key_) {
        return find(n->left_, key);
    } else {
        return find(n->right_, key);
    }
}

// public
template<class T1, class T2>
T2 BSTree<T1, T2>::find(T1 key)
{
    Node<T1, T2> *n = find(root, key);
    if (n != nullptr) {
        return n->data_;
    } else {
        return -1;
    }
}






        // Node<T>* root;

        // Node<T>* insert(T val, Node<T>*temp)
        // {
        //     if (temp == nullptr) {
        //         temp = new Node<T>(val);
        //     } else if (val < temp->data) {
        //         temp->left = insert(val, temp->left);
        //     } else if (val > temp->data) {
        //         temp->right = insert(val, temp->right);
        //     }
        //     return temp;
        // };

        // void inorder(Node<T>* temp)
        // {
        //     if(temp == nullptr) {
        //         return;
        //     }
        //     inorder(temp->left);
        //     cout<<temp->data<<" ";
        //     inorder(temp->right);
        // }

        // public:
        //     BSTree()
        //     {
        //         root = nullptr;
        //     }

        //     ~BSTree()
        //     {
        //         delete root;
        //     }
            
        //     void insert(T1 key, T2 value)
        //     {
        //         root = insert(val, root);
        //     }

        //     void remove(T1 key)
        //     {
                
        //     }

        //     T2 find(T1 key) {

        //     }
            
        //     void inorder()
        //     {
        //         cout<<"Root Data : "<<root->data<<endl<<endl;
        //         inorder(root);
        //         cout<<endl;
        //     }