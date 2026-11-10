#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string name;
    Node* left;
    Node* right;

    Node(string val) {
        name = val;
        left = nullptr;
        right = nullptr;
    }
};

void displayHierarchy(Node* root) {
    if (root == nullptr) return;

    cout << "Member: " << root->name << endl;
    cout << "  Left Child: " << (root->left ? root->left->name : "None") << endl;
    cout << "  Right Child: " << (root->right ? root->right->name : "None") << endl;
    cout << "-----------------------------------" << endl;

    displayHierarchy(root->left);
    displayHierarchy(root->right);
}

int main() {
    Node* root = new Node("HOD Usman");
    root->left = new Node("Coord CS");
    root->right = new Node("Coord SE");

    root->left->left = new Node("Dr. Ali");
    root->left->right = new Node("Dr. Zara");

    root->right->left = new Node("Prof. Umar");
    root->right->right = new Node("Prof. Sana");

    displayHierarchy(root);

    return 0;
}