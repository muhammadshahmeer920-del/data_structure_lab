#include <iostream>
#include <string>
#include <queue>
using namespace std;

class Node {
public:
    int emergencyId;
    string location;
    int severity;
    Node* left;
    Node* right;
    int height;

    Node(int id, string loc, int sev) {
        emergencyId = id;
        location = loc;
        severity = sev;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class EmergencyAVL {
private:
    Node* root;

    int getMax(int a, int b) {
        if (a > b) {
            return a;
        }
        return b;
    }

    int getHeight(Node* n) {
        if (n == nullptr) {
            return 0;
        }
        return n->height;
    }

    int getBalance(Node* n) {
        if (n == nullptr) {
            return 0;
        }
        return getHeight(n->left) - getHeight(n->right);
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* temp = y->left;
        y->left = x;
        x->right = temp;
        x->height = 1 + getMax(getHeight(x->left), getHeight(x->right));
        y->height = 1 + getMax(getHeight(y->left), getHeight(y->right));
        return y;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* temp = x->right;
        x->right = y;
        y->left = temp;
        y->height = 1 + getMax(getHeight(y->left), getHeight(y->right));
        x->height = 1 + getMax(getHeight(x->left), getHeight(x->right));
        return x;
    }

    Node* insert(Node* node, int id, string loc, int sev) {
        if (node == nullptr) {
            return new Node(id, loc, sev);
        }
        if (id < node->emergencyId) {
            node->left = insert(node->left, id, loc, sev);
        }
        else if (id > node->emergencyId) {
            node->right = insert(node->right, id, loc, sev);
        }
        else {
            return node;
        }

        node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && id < node->left->emergencyId) {
            cout << "LL Rotation at ID " << node->emergencyId << endl;
            return rightRotate(node);
        }
        if (balance < -1 && id > node->right->emergencyId) {
            cout << "RR Rotation at ID " << node->emergencyId << endl;
            return leftRotate(node);
        }
        if (balance > 1 && id > node->left->emergencyId) {
            cout << "LR Rotation at ID " << node->emergencyId << endl;
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && id < node->right->emergencyId) {
            cout << "RL Rotation at ID " << node->emergencyId << endl;
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* findMinNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* deleteNode(Node* node, int id) {
        if (node == nullptr) {
            return node;
        }
        if (id < node->emergencyId) {
            node->left = deleteNode(node->left, id);
        }
        else if (id > node->emergencyId) {
            node->right = deleteNode(node->right, id);
        }
        else {
            if (node->left == nullptr || node->right == nullptr) {
                Node* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                }
                else {
                    *node = *temp;
                }
                delete temp;
            }
            else {
                Node* temp = findMinNode(node->right);
                node->emergencyId = temp->emergencyId;
                node->location = temp->location;
                node->severity = temp->severity;
                node->right = deleteNode(node->right, temp->emergencyId);
            }
        }

        if (node == nullptr) {
            return node;
        }

        node->height = 1 + getMax(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) {
            cout << "LL Rotation after delete at ID " << node->emergencyId << endl;
            return rightRotate(node);
        }
        if (balance > 1 && getBalance(node->left) < 0) {
            cout << "LR Rotation after delete at ID " << node->emergencyId << endl;
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && getBalance(node->right) <= 0) {
            cout << "RR Rotation after delete at ID " << node->emergencyId << endl;
            return leftRotate(node);
        }
        if (balance < -1 && getBalance(node->right) > 0) {
            cout << "RL Rotation after delete at ID " << node->emergencyId << endl;
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* search(Node* node, int id) {
        if (node == nullptr || node->emergencyId == id) {
            return node;
        }
        if (id < node->emergencyId) {
            return search(node->left, id);
        }
        return search(node->right, id);
    }

    void inorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left);
        cout << "ID: " << node->emergencyId
             << " | Location: " << node->location
             << " | Severity: " << node->severity << endl;
        inorder(node->right);
    }

    void levelOrder(Node* node) {
        if (node == nullptr) {
            return;
        }
        queue<Node*> q;
        q.push(node);
        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();
            cout << "ID: " << curr->emergencyId
                 << " | Location: " << curr->location
                 << " | Severity: " << curr->severity << endl;
            if (curr->left != nullptr) {
                q.push(curr->left);
            }
            if (curr->right != nullptr) {
                q.push(curr->right);
            }
        }
    }

    void showTreeDetails(Node* node) {
        if (node == nullptr) {
            return;
        }
        cout << "ID: " << node->emergencyId
             << " | Location: " << node->location
             << " | Severity: " << node->severity
             << " | Height: " << node->height
             << " | BF: " << getBalance(node);
        if (node->left != nullptr) {
            cout << " | Left: " << node->left->emergencyId;
        }
        else {
            cout << " | Left: NULL";
        }
        if (node->right != nullptr) {
            cout << " | Right: " << node->right->emergencyId;
        }
        else {
            cout << " | Right: NULL";
        }
        cout << endl;
        showTreeDetails(node->left);
        showTreeDetails(node->right);
    }

public:
    EmergencyAVL() {
        root = nullptr;
    }

    void insertRecord(int id, string loc, int sev) {
        root = insert(root, id, loc, sev);
    }

    void searchRecord(int id) {
        Node* res = search(root, id);
        if (res != nullptr) {
            cout << "Found -> ID: " << res->emergencyId
                 << " | Location: " << res->location
                 << " | Severity: " << res->severity << endl;
        }
        else {
            cout << "Emergency ID " << id << " not found!" << endl;
        }
    }

    void deleteRecord(int id) {
        if (search(root, id) == nullptr) {
            cout << "Emergency ID " << id << " not found for deletion!" << endl;
            return;
        }
        root = deleteNode(root, id);
        cout << "Deleted Emergency ID: " << id << endl;
    }

    void display() {
        cout << "\n--- Records Sorted by Emergency ID (In-order) ---" << endl;
        inorder(root);
        cout << "\n--- Level-order (BFS) Traversal ---" << endl;
        levelOrder(root);
        cout << "\n--- Final Balanced AVL Tree Structure ---" << endl;
        if (root != nullptr) {
            cout << "Root ID: " << root->emergencyId << endl;
        }
        showTreeDetails(root);
    }
};

int main() {
    EmergencyAVL avl;

    avl.insertRecord(50, "Islamabad", 5);
    avl.insertRecord(80, "Lahore", 4);
    avl.insertRecord(60, "Karachi", 5);
    avl.insertRecord(90, "Peshawar", 3);
    avl.insertRecord(100, "Quetta", 4);
    avl.insertRecord(30, "Multan", 2);
    avl.insertRecord(20, "Rawalpindi", 5);
    avl.insertRecord(10, "Faisalabad", 3);
    avl.insertRecord(15, "Sialkot", 4);
    avl.insertRecord(70, "Gujranwala", 2);
    avl.insertRecord(40, "Hyderabad", 1);
    avl.insertRecord(85, "Bahawalpur", 3);

    cout << "\n--- Search Operations ---" << endl;
    avl.searchRecord(60);
    avl.searchRecord(999);

    cout << "\n--- Deletion Operations ---" << endl;
    avl.deleteRecord(100);
    avl.deleteRecord(60);

    avl.display();

    return 0;
}