#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int val) {
        key = val;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

int getHeight(Node* n) {
    if (n == nullptr) return 0;
    return n->height;
}

int getBalanceFactor(Node* n) {
    if (n == nullptr) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}

Node* insert(Node* node, int key) {
    if (node == nullptr)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalanceFactor(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void inOrder(Node* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    cout << root->key << " ";
    inOrder(root->right);
}

void printTree(Node* root, int space = 0, int height = 10) {
    if (root == nullptr) return;

    space += height;

    printTree(root->right, space);

    cout << endl;
    for (int i = height; i < space; i++)
        cout << " ";
    cout << root->key << "\n";

    printTree(root->left, space);
}

int main() {
    Node* root = nullptr;
    int tokens[] = {15, 25, 35, 45, 55, 65, 75};

    for (int token : tokens) {
        root = insert(root, token);
    }

    cout << "In-order Traversal of Tokens: ";
    inOrder(root);
    cout << "\n\nBalanced AVL Tree Structure (Rotated 90 degrees left):" << endl;
    printTree(root);

    return 0;
}