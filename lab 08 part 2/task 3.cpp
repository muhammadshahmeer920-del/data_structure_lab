#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string folder;
    Node* left;
    Node* right;

    Node(string val) {
        folder = val;
        left = nullptr;
        right = nullptr;
    }
};

void preOrder(Node* root) {
    if (root == nullptr) return;
    cout << root->folder << " ";
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(Node* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    cout << root->folder << " ";
    inOrder(root->right);
}

void postOrder(Node* root) {
    if (root == nullptr) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->folder << " ";
}

int main() {
    Node* root = new Node("C_Drive");
    root->left = new Node("Documents");
    root->right = new Node("Pictures");

    root->left->left = new Node("Work");
    root->left->right = new Node("Personal");

    root->right->left = new Node("Vacation");
    root->right->right = new Node("Family");

    cout << "Pre-order Traversal: ";
    preOrder(root);
    cout << "\n\nIn-order Traversal: ";
    inOrder(root);
    cout << "\n\nPost-order Traversal: ";
    postOrder(root);
    cout << endl;

    return 0;
}