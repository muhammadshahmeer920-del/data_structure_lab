#include <iostream>
#include <string>

using namespace std;

class GeneralNode {
public:
    string name;
    GeneralNode* left;
    GeneralNode* right;

    GeneralNode(string val) {
        name = val;
        left = nullptr;
        right = nullptr;
    }
};

class GeneralTree {
public:
    GeneralNode* root;

    GeneralTree() {
        root = nullptr;
    }

    void displayNodes(GeneralNode* node) {
        if (node == nullptr) return;
        
        cout << "Staff: " << node->name << " | Left Child: ";
        if (node->left != nullptr) cout << node->left->name;
        else cout << "NULL";
        
        cout << " | Right Child: ";
        if (node->right != nullptr) cout << node->right->name;
        else cout << "NULL";
        cout << endl;

        displayNodes(node->left);
        displayNodes(node->right);
    }
};

class BSTNode {
public:
    int id;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int val) {
        id = val;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    BSTNode* root;

    BSTNode* insertHelper(BSTNode* node, int val, bool &inserted) {
        if (node == nullptr) {
            inserted = true;
            return new BSTNode(val);
        }
        if (val < node->id) {
            node->left = insertHelper(node->left, val, inserted);
        } else if (val > node->id) {
            node->right = insertHelper(node->right, val, inserted);
        } else {
            inserted = false;
        }
        return node;
    }

    BSTNode* copyHelper(BSTNode* node) {
        if (node == nullptr) return nullptr;
        BSTNode* newNode = new BSTNode(node->id);
        newNode->left = copyHelper(node->left);
        newNode->right = copyHelper(node->right);
        return newNode;
    }

    void destroyHelper(BSTNode* node) {
        if (node == nullptr) return;
        destroyHelper(node->left);
        destroyHelper(node->right);
        delete node;
    }

    BSTNode* findMin(BSTNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    BSTNode* deleteHelper(BSTNode* node, int val, bool &found) {
        if (node == nullptr) {
            found = false;
            return nullptr;
        }
        if (val < node->id) {
            node->left = deleteHelper(node->left, val, found);
        } else if (val > node->id) {
            node->right = deleteHelper(node->right, val, found);
        } else {
            found = true;
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            } else if (node->left == nullptr) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            } else {
                BSTNode* temp = findMin(node->right);
                node->id = temp->id;
                node->right = deleteHelper(node->right, temp->id, found);
            }
        }
        return node;
    }

    void inOrderHelper(BSTNode* node) {
        if (node == nullptr) return;
        inOrderHelper(node->left);
        cout << node->id << " ";
        inOrderHelper(node->right);
    }

public:
    BST() {
        root = nullptr;
    }

    BST(const BST &other) {
        root = copyHelper(other.root);
    }

    ~BST() {
        destroyHelper(root);
    }

    bool insert(int val) {
        bool inserted = false;
        root = insertHelper(root, val, inserted);
        return inserted;
    }

    bool search(int val, int &visits) {
        visits = 0;
        BSTNode* current = root;
        while (current != nullptr) {
            visits++;
            if (current->id == val) return true;
            if (val < current->id) current = current->left;
            else current = current->right;
        }
        return false;
    }

    bool remove(int val) {
        bool found = false;
        root = deleteHelper(root, val, found);
        return found;
    }

    void displayInOrder() {
        inOrderHelper(root);
        cout << endl;
    }
};

int main() {
    GeneralTree gt;
    gt.root = new GeneralNode("Alice");
    gt.root->left = new GeneralNode("Bob");
    gt.root->right = new GeneralNode("Charlie");
    gt.root->left->left = new GeneralNode("David");
    gt.root->left->right = new GeneralNode("Emma");
    gt.root->right->left = new GeneralNode("Frank");
    gt.root->right->right = new GeneralNode("Grace");

    cout << "=== General Binary Tree Structure ===" << endl;
    gt.displayNodes(gt.root);
    cout << endl;

    BST bst;
    int initialIDs[] = {48, 28, 68, 18, 38, 58, 78};
    for (int id : initialIDs) {
        bst.insert(id);
    }

    cout << "=== Initial BST In-Order Traversal ===" << endl;
    bst.displayInOrder();
    cout << endl;

    cout << "=== Enter 3 Additional Staff IDs ===" << endl;
    for (int i = 0; i < 3; i++) {
        int newID;
        cout << "Enter Staff ID " << i + 1 << ": ";
        cin >> newID;
        if (!bst.insert(newID)) {
            cout << "Duplicate ID " << newID << " rejected." << endl;
        } else {
            cout << "ID " << newID << " inserted successfully." << endl;
        }
    }

    cout << "\nUpdated BST In-Order Traversal: ";
    bst.displayInOrder();
    cout << endl;

    cout << "=== Searching Staff IDs ===" << endl;
    int visits = 0;
    int testIDs[] = {38, 99, 5};
    for (int id : testIDs) {
        bool found = bst.search(id, visits);
        cout << "Search ID " << id << ": " << (found ? "Found" : "Not Found")
             << " | Node Visits: " << visits << endl;
    }
    cout << endl;

    cout << "=== Testing Deletion Cases (Fresh Copies) ===" << endl;

    BST copyLeaf = bst;
    cout << "1. Deleting Leaf Node (18):" << endl;
    copyLeaf.remove(18);
    cout << "   Result: ";
    copyLeaf.displayInOrder();

    BST copyOneChild = bst;
    cout << "2. Deleting Node with One Child (38):" << endl;
    copyOneChild.remove(38);
    cout << "   Result: ";
    copyOneChild.displayInOrder();

    BST copyTwoChildren = bst;
    cout << "3. Deleting Node with Two Children (28):" << endl;
    copyTwoChildren.remove(28);
    cout << "   Result: ";
    copyTwoChildren.displayInOrder();

    return 0;
}