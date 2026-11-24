#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class Patient {
public:
    string name;
    int id;
    int priority;
    Patient* left;
    Patient* right;

    Patient(string n, int i, int p) {
        name = n;
        id = i;
        priority = p;
        left = nullptr;
        right = nullptr;
    }
};

class EmergencyHeap {
private:
    Patient* root;
    int size;

    void swapData(Patient* a, Patient* b) {
        swap(a->name, b->name);
        swap(a->id, b->id);
        swap(a->priority, b->priority);
    }

    vector<Patient*> getPath(int pos) {
        vector<int> bits;
        while (pos > 0) {
            bits.push_back(pos % 2);
            pos /= 2;
        }
        vector<Patient*> path;
        Patient* cur = root;
        path.push_back(cur);
        for (int i = (int)bits.size() - 2; i >= 0; i--) {
            cur = (bits[i] == 0) ? cur->left : cur->right;
            path.push_back(cur);
        }
        return path;
    }

    void heapifyUp(vector<Patient*>& path) {
        for (int i = (int)path.size() - 1; i > 0; i--) {
            if (path[i]->priority > path[i - 1]->priority)
                swapData(path[i], path[i - 1]);
            else
                break;
        }
    }

    void heapifyDown(Patient* node) {
        while (node) {
            Patient* largest = node;
            if (node->left && node->left->priority > largest->priority)
                largest = node->left;
            if (node->right && node->right->priority > largest->priority)
                largest = node->right;
            if (largest == node)
                break;
            swapData(node, largest);
            node = largest;
        }
    }

public:
    EmergencyHeap() {
        root = nullptr;
        size = 0;
    }

    void insert(string name, int id, int priority) {
        Patient* node = new Patient(name, id, priority);
        size++;
        if (size == 1) {
            root = node;
            return;
        }
        vector<Patient*> path = getPath(size / 2);
        Patient* parent = path.back();
        if (size % 2 == 0)
            parent->left = node;
        else
            parent->right = node;
        path.push_back(node);
        heapifyUp(path);
    }

    void showHighestPriority() {
        if (!root) {
            cout << "No patients waiting\n";
            return;
        }
        cout << "Highest priority: " << root->name << " (ID " << root->id << ", Priority " << root->priority << ")\n";
    }

    void treatPatient() {
        if (!root) {
            cout << "No patients waiting\n";
            return;
        }
        vector<Patient*> path = getPath(size);
        Patient* last = path.back();
        cout << "Treated: " << root->name << " (ID " << root->id << ", Priority " << root->priority << ")\n";
        if (size == 1) {
            delete root;
            root = nullptr;
            size--;
            return;
        }
        Patient* parent = path[path.size() - 2];
        root->name = last->name;
        root->id = last->id;
        root->priority = last->priority;
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
            cout << "No patients waiting\n";
            return;
        }
        queue<Patient*> q;
        q.push(root);
        int level = 0;
        while (!q.empty()) {
            int count = q.size();
            cout << "Level " << level++ << ": ";
            while (count--) {
                Patient* cur = q.front();
                q.pop();
                cout << "[" << cur->name << ", " << cur->id << ", P" << cur->priority << "] ";
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
            cout << endl;
        }
    }
};

int main() {
    EmergencyHeap heap;
    heap.insert("Zain", 201, 4);
    heap.insert("Mariam", 202, 9);
    heap.insert("Kamran", 203, 6);
    heap.insert("Hina", 204, 2);
    heap.insert("Rizwan", 205, 10);
    heap.insert("Noor", 206, 7);
    heap.insert("Tariq", 207, 5);

    cout << "Waiting Patients (Level Order):\n";
    heap.display();

    cout << "\n";
    heap.showHighestPriority();

    cout << "\nTreating patient...\n";
    heap.treatPatient();

    cout << "\nUpdated Waiting Patients (Level Order):\n";
    heap.display();

    cout << "\nNext patient to be treated:\n";
    heap.showHighestPriority();
    return 0;
}
