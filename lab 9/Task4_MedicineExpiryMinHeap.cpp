#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class Medicine {
public:
    string name;
    int id;
    int expiry;
    Medicine* left;
    Medicine* right;

    Medicine(string n, int i, int e) {
        name = n;
        id = i;
        expiry = e;
        left = nullptr;
        right = nullptr;
    }
};

class MinHeap {
private:
    Medicine* root;
    int size;

    void swapData(Medicine* a, Medicine* b) {
        swap(a->name, b->name);
        swap(a->id, b->id);
        swap(a->expiry, b->expiry);
    }

    vector<Medicine*> getPath(int pos) {
        vector<int> bits;
        while (pos > 0) {
            bits.push_back(pos % 2);
            pos /= 2;
        }
        vector<Medicine*> path;
        Medicine* cur = root;
        path.push_back(cur);
        for (int i = (int)bits.size() - 2; i >= 0; i--) {
            cur = (bits[i] == 0) ? cur->left : cur->right;
            path.push_back(cur);
        }
        return path;
    }

    void heapifyUp(vector<Medicine*>& path) {
        for (int i = (int)path.size() - 1; i > 0; i--) {
            if (path[i]->expiry < path[i - 1]->expiry)
                swapData(path[i], path[i - 1]);
            else
                break;
        }
    }

    void heapifyDown(Medicine* node) {
        while (node) {
            Medicine* smallest = node;
            if (node->left && node->left->expiry < smallest->expiry)
                smallest = node->left;
            if (node->right && node->right->expiry < smallest->expiry)
                smallest = node->right;
            if (smallest == node)
                break;
            swapData(node, smallest);
            node = smallest;
        }
    }

public:
    MinHeap() {
        root = nullptr;
        size = 0;
    }

    void insert(string name, int id, int expiry) {
        Medicine* node = new Medicine(name, id, expiry);
        size++;
        if (size == 1) {
            root = node;
            return;
        }
        vector<Medicine*> path = getPath(size / 2);
        Medicine* parent = path.back();
        if (size % 2 == 0)
            parent->left = node;
        else
            parent->right = node;
        path.push_back(node);
        heapifyUp(path);
    }

    void showNearestExpiry() {
        if (!root) {
            cout << "No medicines in stock\n";
            return;
        }
        cout << "Nearest expiry: " << root->name << " (ID " << root->id << ", Expiry " << root->expiry << ")\n";
    }

    void deleteMin() {
        if (!root) {
            cout << "No medicines in stock\n";
            return;
        }
        vector<Medicine*> path = getPath(size);
        Medicine* last = path.back();
        cout << "Deleted: " << root->name << " (ID " << root->id << ", Expiry " << root->expiry << ")\n";
        if (size == 1) {
            delete root;
            root = nullptr;
            size--;
            return;
        }
        Medicine* parent = path[path.size() - 2];
        root->name = last->name;
        root->id = last->id;
        root->expiry = last->expiry;
        if (parent->right == last)
            parent->right = nullptr;
        else
            parent->left = nullptr;
        delete last;
        size--;
        heapifyDown(root);
    }

    void display() {
        if (!root) {
            cout << "No medicines in stock\n";
            return;
        }
        queue<Medicine*> q;
        q.push(root);
        int level = 0;
        while (!q.empty()) {
            int count = q.size();
            cout << "Level " << level++ << ": ";
            while (count--) {
                Medicine* cur = q.front();
                q.pop();
                cout << "[" << cur->name << ", " << cur->id << ", " << cur->expiry << "] ";
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
            cout << endl;
        }
    }
};

int main() {
    MinHeap heap;
    heap.insert("Paracetamol", 301, 20270315);
    heap.insert("Amoxicillin", 302, 20261120);
    heap.insert("Ibuprofen", 303, 20280601);
    heap.insert("Cetirizine", 304, 20270910);
    heap.insert("Omeprazole", 305, 20261005);
    heap.insert("Metformin", 306, 20271231);
    heap.insert("Azithromycin", 307, 20260830);

    cout << "Medicine Heap (Level Order):\n";
    heap.display();

    cout << "\n";
    heap.showNearestExpiry();

    cout << "\nDeleting nearest expiry medicine...\n";
    heap.deleteMin();

    cout << "\nUpdated Medicine Heap (Level Order):\n";
    heap.display();
    return 0;
}
