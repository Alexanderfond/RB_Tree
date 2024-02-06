#include <iostream>
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLACK   "\033[33m"
#define WHITE   "\033[37m"

enum Color { RED_COLOR, BLACK_COLOR };

struct Node {
    int data;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int val) : data(val), color(RED_COLOR), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;

    void insertFix(Node* newNode) {
        while (newNode != root && newNode->parent->color == RED_COLOR) {
            Node* grandparent = newNode->parent->parent;
            Node* uncle = (newNode->parent == grandparent->left) ? grandparent->right : grandparent->left;

            if (uncle != nullptr && uncle->color == RED_COLOR) {
                newNode->parent->color = BLACK_COLOR;
                uncle->color = BLACK_COLOR;
                grandparent->color = RED_COLOR;
                newNode = grandparent;
            }
            else {
                if (newNode->parent == grandparent->left) {
                    if (newNode == newNode->parent->right) {
                        newNode = newNode->parent;
                        leftRotate(newNode);
                    }
                    newNode->parent->color = BLACK_COLOR;
                    grandparent->color = RED_COLOR;
                    rightRotate(grandparent);
                }
                else {
                    if (newNode == newNode->parent->left) {
                        newNode = newNode->parent;
                        rightRotate(newNode);
                    }
                    newNode->parent->color = BLACK_COLOR;
                    grandparent->color = RED_COLOR;
                    leftRotate(grandparent);
                }
            }
        }
        root->color = BLACK_COLOR;
    }

    void leftRotate(Node* node) {
        Node* rightChild = node->right;
        node->right = rightChild->left;
        if (rightChild->left != nullptr) {
            rightChild->left->parent = node;
        }
        rightChild->parent = node->parent;
        if (node->parent == nullptr) {
            root = rightChild;
        }
        else if (node == node->parent->left) {
            node->parent->left = rightChild;
        }
        else {
            node->parent->right = rightChild;
        }
        rightChild->left = node;
        node->parent = rightChild;
    }

    void rightRotate(Node* node) {
        Node* leftChild = node->left;
        node->left = leftChild->right;
        if (leftChild->right != nullptr) {
            leftChild->right->parent = node;
        }
        leftChild->parent = node->parent;
        if (node->parent == nullptr) {
            root = leftChild;
        }
        else if (node == node->parent->left) {
            node->parent->left = leftChild;
        }
        else {
            node->parent->right = leftChild;
        }
        leftChild->right = node;
        node->parent = leftChild;
    }

    void insert(int data, Node* node) {
        if (data < node->data) {
            if (node->left != nullptr) {
                insert(data, node->left);
            }
            else {
                node->left = new Node(data);
                node->left->parent = node;
                insertFix(node->left);
            }
        }
        else if (data > node->data) {
            if (node->right != nullptr) {
                insert(data, node->right);
            }
            else {
                node->right = new Node(data);
                node->right->parent = node;
                insertFix(node->right);
            }
        }
    }

    void printTreeWithColor(Node* node, int space) const {
        const int COUNT = 5;
        if (node == nullptr) return;

        space += COUNT;

        printTreeWithColor(node->right, space);

        cout << endl;
        for (int i = COUNT; i < space; ++i) cout << " ";
        if (node->data == 0) {
            cout << BLACK << "NULL" << RESET << " (BLACK)" << endl;
        }
        else if (node->color == BLACK_COLOR) {
            cout << BLACK << node->data << RESET << " (BLACK)" << endl;
        }
        else {
            cout << RED << node->data << RESET << " (RED)" << endl;
        }

        printTreeWithColor(node->left, space);
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int data) {
        if (root == nullptr) {
            root = new Node(data);
            root->color = BLACK_COLOR;
        }
        else {
            insert(data, root);
        }
    }

    void printTree() const {
        if (root == nullptr) {
            cout << "Дерево порожнє." << endl;
            return;
        }
        cout << "Вигляд червоно-чорного дерева:" << endl << endl;
        printTreeWithColor(root, 0);
        cout << endl;
    }
};

int main() {

    RedBlackTree tree;

    cout << "Введіть елементи для вставки у червоно-чорне дерево (-1 для завершення вводу):" << endl;
    int element;
    while (true) {
        cin >> element;
        if (element == -1) break;
        tree.insert(element);
    }

    tree.printTree();

    return 0;
}
