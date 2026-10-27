#include <iostream>
#include <algorithm>

using namespace std;

class Node {
public:
    int id;
    Node* left;
    Node* right;

    Node(int val) {
        id = val;
        left = nullptr;
        right = nullptr;
    }
};

class HospitalBST {
private:
    Node* root;

    Node* insertHelper(Node* node, int val, bool &inserted) {
        if (node == nullptr) {
            inserted = true;
            return new Node(val);
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

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* deleteHelper(Node* node, int val, bool &found) {
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
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            } else {
                Node* temp = findMin(node->right);
                node->id = temp->id;
                node->right = deleteHelper(node->right, temp->id, found);
            }
        }
        return node;
    }

    void inOrderHelper(Node* node) {
        if (node == nullptr) return;
        inOrderHelper(node->left);
        cout << node->id << " ";
        inOrderHelper(node->right);
    }

    void preOrderHelper(Node* node) {
        if (node == nullptr) return;
        cout << node->id << " ";
        preOrderHelper(node->left);
        preOrderHelper(node->right);
    }

    void postOrderHelper(Node* node) {
        if (node == nullptr) return;
        postOrderHelper(node->left);
        postOrderHelper(node->right);
        cout << node->id << " ";
    }

    int countNodesHelper(Node* node) {
        if (node == nullptr) return 0;
        return 1 + countNodesHelper(node->left) + countNodesHelper(node->right);
    }

    int calculateHeightHelper(Node* node) {
        if (node == nullptr) return 0;
        return 1 + max(calculateHeightHelper(node->left), calculateHeightHelper(node->right));
    }

    void destroyTree(Node* node) {
        if (node == nullptr) return;
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    HospitalBST() {
        root = nullptr;
    }

    ~HospitalBST() {
        destroyTree(root);
    }

    void insert(int val) {
        bool inserted = false;
        root = insertHelper(root, val, inserted);
        if (inserted) {
            cout << "ID " << val << " inserted successfully." << endl;
        } else {
            cout << "Duplicate ID " << val << " rejected." << endl;
        }
    }

    void search(int val) {
        if (root == nullptr) {
            cout << "Tree is empty. ID not found." << endl;
            return;
        }
        Node* current = root;
        int visits = 0;
        while (current != nullptr) {
            visits++;
            if (current->id == val) {
                cout << "ID " << val << " found after " << visits << " node visit(s)." << endl;
                return;
            }
            if (val < current->id) current = current->left;
            else current = current->right;
        }
        cout << "ID " << val << " does not exist in the system (Visits: " << visits << ")." << endl;
    }

    void remove(int val) {
        if (root == nullptr) {
            cout << "Tree is empty. Cannot delete." << endl;
            return;
        }
        bool found = false;
        root = deleteHelper(root, val, found);
        if (found) {
            cout << "ID " << val << " successfully deleted." << endl;
            cout << "Updated In-Order IDs: ";
            displayInOrder();
        } else {
            cout << "ID " << val << " does not exist in the system." << endl;
        }
    }

    void displayInOrder() {
        if (root == nullptr) {
            cout << "Tree is empty.";
        } else {
            inOrderHelper(root);
        }
        cout << endl;
    }

    void displayPreOrder() {
        if (root == nullptr) {
            cout << "Tree is empty.";
        } else {
            preOrderHelper(root);
        }
        cout << endl;
    }

    void displayPostOrder() {
        if (root == nullptr) {
            cout << "Tree is empty.";
        } else {
            postOrderHelper(root);
        }
        cout << endl;
    }

    int countNodes() {
        return countNodesHelper(root);
    }

    int calculateHeight() {
        return calculateHeightHelper(root);
    }
};

int main() {
    HospitalBST bst;

    int initialIDs[] = {55, 35, 75, 25, 45, 65, 85, 40, 50};
    for (int id : initialIDs) {
        bst.insert(id);
    }

    int choice = 0;
    while (choice != 9) {
        cout << "\n============================================" << endl;
        cout << " Hospital & Emergency Inventory Management" << endl;
        cout << "============================================" << endl;
        cout << "1. Insert an ID" << endl;
        cout << "2. Search for an ID" << endl;
        cout << "3. Delete an ID" << endl;
        cout << "4. Display In-Order Traversal" << endl;
        cout << "5. Display Pre-Order Traversal" << endl;
        cout << "6. Display Post-Order Traversal" << endl;
        cout << "7. Count Total Number of Nodes" << endl;
        cout << "8. Calculate Height of BST" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice (1-9): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number from 1 to 9." << endl;
            continue;
        }

        switch (choice) {
            case 1: {
                int id;
                cout << "Enter ID to insert: ";
                cin >> id;
                bst.insert(id);
                break;
            }
            case 2: {
                int id;
                cout << "Enter ID to search: ";
                cin >> id;
                bst.search(id);
                break;
            }
            case 3: {
                int id;
                cout << "Enter ID to delete: ";
                cin >> id;
                bst.remove(id);
                break;
            }
            case 4: {
                cout << "In-Order Traversal: ";
                bst.displayInOrder();
                break;
            }
            case 5: {
                cout << "Pre-Order Traversal: ";
                bst.displayPreOrder();
                break;
            }
            case 6: {
                cout << "Post-Order Traversal: ";
                bst.displayPostOrder();
                break;
            }
            case 7: {
                cout << "Total Number of Nodes: " << bst.countNodes() << endl;
                break;
            }
            case 8: {
                cout << "Height of BST: " << bst.calculateHeight() << endl;
                break;
            }
            case 9: {
                cout << "Exiting application." << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please enter a number between 1 and 9." << endl;
                break;
            }
        }
    }

    return 0;
}