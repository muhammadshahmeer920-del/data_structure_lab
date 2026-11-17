#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int flightNumber;
    string destination;
    string departureTime;
    Node* left;
    Node* right;

    Node(int fn, string dest, string time) {
        flightNumber = fn;
        destination = dest;
        departureTime = time;
        left = nullptr;
        right = nullptr;
    }
};

class FlightBST {
private:
    Node* root;

    Node* insert(Node* node, int fn, string dest, string time) {
        if (node == nullptr) {
            return new Node(fn, dest, time);
        }
        if (fn < node->flightNumber) {
            node->left = insert(node->left, fn, dest, time);
        }
        else if (fn > node->flightNumber) {
            node->right = insert(node->right, fn, dest, time);
        }
        return node;
    }

    Node* search(Node* node, int fn) {
        if (node == nullptr || node->flightNumber == fn) {
            return node;
        }
        if (fn < node->flightNumber) {
            return search(node->left, fn);
        }
        return search(node->right, fn);
    }

    Node* findMinNode(Node* node) {
        Node* current = node;
        while (current != nullptr && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* deleteNode(Node* node, int fn) {
        if (node == nullptr) {
            return node;
        }
        if (fn < node->flightNumber) {
            node->left = deleteNode(node->left, fn);
        }
        else if (fn > node->flightNumber) {
            node->right = deleteNode(node->right, fn);
        }
        else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            else {
                Node* temp = findMinNode(node->right);
                node->flightNumber = temp->flightNumber;
                node->destination = temp->destination;
                node->departureTime = temp->departureTime;
                node->right = deleteNode(node->right, temp->flightNumber);
            }
        }
        return node;
    }

    void inorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left);
        cout << "Flight: " << node->flightNumber
             << " | Destination: " << node->destination
             << " | Departure: " << node->departureTime << endl;
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        cout << "Flight: " << node->flightNumber
             << " | Destination: " << node->destination
             << " | Departure: " << node->departureTime << endl;
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        postorder(node->left);
        postorder(node->right);
        cout << "Flight: " << node->flightNumber
             << " | Destination: " << node->destination
             << " | Departure: " << node->departureTime << endl;
    }

    int countFlights(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countFlights(node->left) + countFlights(node->right);
    }

    int getHeight(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
        if (leftHeight > rightHeight) {
            return 1 + leftHeight;
        }
        return 1 + rightHeight;
    }

    void showStructure(Node* node) {
        if (node == nullptr) {
            return;
        }
        cout << "Flight: " << node->flightNumber
             << " (" << node->destination << ", " << node->departureTime << ")";
        if (node->left != nullptr) {
            cout << " | Left: " << node->left->flightNumber;
        }
        else {
            cout << " | Left: NULL";
        }
        if (node->right != nullptr) {
            cout << " | Right: " << node->right->flightNumber;
        }
        else {
            cout << " | Right: NULL";
        }
        cout << endl;
        showStructure(node->left);
        showStructure(node->right);
    }

public:
    FlightBST() {
        root = nullptr;
    }

    void insertFlight(int fn, string dest, string time) {
        root = insert(root, fn, dest, time);
    }

    void searchFlight(int fn) {
        Node* res = search(root, fn);
        if (res != nullptr) {
            cout << "Found -> Flight: " << res->flightNumber
                 << " | Destination: " << res->destination
                 << " | Departure: " << res->departureTime << endl;
        }
        else {
            cout << "Flight " << fn << " not found!" << endl;
        }
    }

    void deleteFlight(int fn) {
        if (search(root, fn) == nullptr) {
            cout << "Flight " << fn << " not found for deletion!" << endl;
            return;
        }
        root = deleteNode(root, fn);
        cout << "Deleted Flight: " << fn << endl;
    }

    void displayTraversals() {
        cout << "\n--- In-order Traversal ---" << endl;
        inorder(root);
        cout << "\n--- Pre-order Traversal ---" << endl;
        preorder(root);
        cout << "\n--- Post-order Traversal ---" << endl;
        postorder(root);
    }

    void displayMinMax() {
        if (root == nullptr) {
            cout << "Tree is empty!" << endl;
            return;
        }
        Node* minNode = root;
        while (minNode->left != nullptr) {
            minNode = minNode->left;
        }
        Node* maxNode = root;
        while (maxNode->right != nullptr) {
            maxNode = maxNode->right;
        }
        cout << "Minimum Flight Number: " << minNode->flightNumber << endl;
        cout << "Maximum Flight Number: " << maxNode->flightNumber << endl;
    }

    void displayStats() {
        cout << "Total Flights: " << countFlights(root) << endl;
        cout << "Tree Height: " << getHeight(root) << endl;
    }

    void displayFinalTree() {
        cout << "\n--- Final BST Structure ---" << endl;
        if (root != nullptr) {
            cout << "Root Flight: " << root->flightNumber << endl;
        }
        showStructure(root);
    }
};

int main() {
    FlightBST bst;

    bst.insertFlight(500, "London", "08:00 AM");
    bst.insertFlight(300, "Dubai", "09:30 AM");
    bst.insertFlight(700, "New York", "11:00 AM");
    bst.insertFlight(200, "Istanbul", "12:15 PM");
    bst.insertFlight(400, "Doha", "01:45 PM");
    bst.insertFlight(600, "Toronto", "03:00 PM");
    bst.insertFlight(800, "Tokyo", "04:30 PM");
    bst.insertFlight(150, "Jeddah", "05:15 PM");
    bst.insertFlight(250, "Riyadh", "06:00 PM");
    bst.insertFlight(350, "Paris", "07:20 PM");
    bst.insertFlight(650, "Frankfurt", "08:40 PM");
    bst.insertFlight(750, "Sydney", "10:00 PM");
    bst.insertFlight(850, "Beijing", "11:30 PM");

    bst.displayTraversals();

    cout << "\n--- Search Operations ---" << endl;
    bst.searchFlight(350);
    bst.searchFlight(999);

    cout << "\n--- Tree Info Before Deletion ---" << endl;
    bst.displayMinMax();
    bst.displayStats();

    cout << "\n--- Deletion Operations (All 3 Cases) ---" << endl;
    bst.deleteFlight(150);
    bst.deleteFlight(400);
    bst.deleteFlight(300);

    cout << "\n--- Tree Info After Deletion ---" << endl;
    bst.displayMinMax();
    bst.displayStats();
    bst.displayFinalTree();

    return 0;
}