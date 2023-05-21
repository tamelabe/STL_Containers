#include "s21_tree.h"

template<class T>
struct Node 
{
    T data;
    Node *left;
    Node *right;

    Node(T val)
    {
        data = val;
        left = right = nullptr;
    }
};

template<class T>
class BSTree
{
    private:
        Node<T>* root;

        Node<T>* insert(T val, Node<T>*temp)
        {
            if (temp == nullptr) {
                temp = new Node<T>(val);
            } else if (val < temp->data) {
                temp->left = insert(val, temp->left);
            } else if (val > temp->data) {
                temp->right = insert(val, temp->right);
            }
            return temp;
        };

        void inorder(Node<T>* temp)
        {
            if(temp == nullptr) {
                return;
            }
            inorder(temp->left);
            cout<<temp->data<<" ";
            inorder(temp->right);
        }

        public:
            BSTree()
            {
                root = nullptr;
            }

            ~BSTree()
            {
                delete root;
            }
            
            void insert(T1 key, T2 value)
            {
                root = insert(val, root);
            }

            void remove(T1 key)
            {
                
            }

            T2 find(T1 key) {

            }
            
            void inorder()
            {
                cout<<"Root Data : "<<root->data<<endl<<endl;
                inorder(root);
                cout<<endl;
            }
};

int main()
{
    BSTree <char> tree;

    tree.insert('A');
    tree.insert('C');
    tree.insert('B');
    tree.insert('Z');
    tree.insert('K');
    tree.insert('F');

    tree.inorder();
}
