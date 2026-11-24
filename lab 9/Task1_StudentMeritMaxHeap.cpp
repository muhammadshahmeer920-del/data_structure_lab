#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class Student {
public:
    string name;
    int roll;
    float marks;
    Student* left;
    Student* right;

    Student(string n, int r, float m) {
        name = n;
        roll = r;
        marks = m;
        left = nullptr;
        right = nullptr;
    }
};

class MaxHeap {
private:
    Student* root;
    int size;

    void swapData(Student* a, Student* b) {
        swap(a->name, b->name);
        swap(a->roll, b->roll);
        swap(a->marks, b->marks);
    }

    vector<Student*> getPath(int pos) {
        vector<int> bits;
        while (pos > 0) {
            bits.push_back(pos % 2);
            pos /= 2;
        }
        vector<Student*> path;
        Student* cur = root;
        path.push_back(cur);
        for (int i = (int)bits.size() - 2; i >= 0; i--) {
            cur = (bits[i] == 0) ? cur->left : cur->right;
            path.push_back(cur);
        }
        return path;
    }

    void heapifyUp(vector<Student*>& path) {
        for (int i = (int)path.size() - 1; i > 0; i--) {
            if (path[i]->marks > path[i - 1]->marks)
                swapData(path[i], path[i - 1]);
            else
                break;
        }
    }

    void heapifyDown(Student* node) {
        while (node) {
            Student* largest = node;
            if (node->left && node->left->marks > largest->marks)
                largest = node->left;
            if (node->right && node->right->marks > largest->marks)
                largest = node->right;
            if (largest == node)
                break;
            swapData(node, largest);
            node = largest;
        }
    }

public:
    MaxHeap() {
        root = nullptr;
        size = 0;
    }

    void insert(string name, int roll, float marks) {
        Student* node = new Student(name, roll, marks);
        size++;
        if (size == 1) {
            root = node;
            return;
        }
        vector<Student*> path = getPath(size / 2);
        Student* parent = path.back();
        if (size % 2 == 0)
            parent->left = node;
        else
            parent->right = node;
        path.push_back(node);
        heapifyUp(path);
    }

    void deleteMax() {
        if (!root) {
            cout << "Heap is empty\n";
            return;
        }
        vector<Student*> path = getPath(size);
        Student* last = path.back();
        cout << "Deleted: " << root->name << " (Roll " << root->roll << ", Marks " << root->marks << ")\n";
        if (size == 1) {
            delete root;
            root = nullptr;
        } else {
            Student* parent = path[path.size() - 2];
            root->name = last->name;
            root->roll = last->roll;
            root->marks = last->marks;
            if (parent->right == last)
                parent->right = nullptr;
            else
                parent->left = nullptr;
            delete last;
            size--;
            heapifyDown(root);
            return;
        }
        size--;
    }

    void display() {
        if (!root) {
            cout << "Heap is empty\n";
            return;
        }
        queue<Student*> q;
        q.push(root);
        int level = 0;
        while (!q.empty()) {
            int count = q.size();
            cout << "Level " << level++ << ": ";
            while (count--) {
                Student* cur = q.front();
                q.pop();
                cout << "[" << cur->name << ", " << cur->roll << ", " << cur->marks << "] ";
                if (cur->left) q.push(cur->left);
                if (cur->right) q.push(cur->right);
            }
            cout << endl;
        }
    }
};

int main() {
    MaxHeap heap;
    heap.insert("Ali", 101, 78.5);
    heap.insert("Sara", 102, 91.0);
    heap.insert("Hamza", 103, 85.0);
    heap.insert("Ayesha", 104, 66.5);
    heap.insert("Usman", 105, 95.5);
    heap.insert("Fatima", 106, 88.0);
    heap.insert("Bilal", 107, 72.0);

    cout << "Merit List (Level Order):\n";
    heap.display();

    cout << "\nDeleting top student...\n";
    heap.deleteMax();

    cout << "\nUpdated Merit List (Level Order):\n";
    heap.display();
    return 0;
}
