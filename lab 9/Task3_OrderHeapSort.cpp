#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Order {
public:
    int id;
    string customer;
    double amount;
    Order* left;
    Order* right;

    Order(int i, string c, double a) {
        id = i;
        customer = c;
        amount = a;
        left = nullptr;
        right = nullptr;
    }
};

class OrderHeap {
private:
    Order* root;
    int size;

    void swapData(Order* a, Order* b) {
        swap(a->id, b->id);
        swap(a->customer, b->customer);
        swap(a->amount, b->amount);
    }

    vector<Order*> getPath(int pos) {
        vector<int> bits;
        while (pos > 0) {
            bits.push_back(pos % 2);
            pos /= 2;
        }
        vector<Order*> path;
        Order* cur = root;
        path.push_back(cur);
        for (int i = (int)bits.size() - 2; i >= 0; i--) {
            cur = (bits[i] == 0) ? cur->left : cur->right;
            path.push_back(cur);
        }
        return path;
    }

    void heapifyUp(vector<Order*>& path) {
        for (int i = (int)path.size() - 1; i > 0; i--) {
            if (path[i]->amount > path[i - 1]->amount)
                swapData(path[i], path[i - 1]);
            else
                break;
        }
    }

    void heapifyDown(Order* node) {
        while (node) {
            Order* largest = node;
            if (node->left && node->left->amount > largest->amount)
                largest = node->left;
            if (node->right && node->right->amount > largest->amount)
                largest = node->right;
            if (largest == node)
                break;
            swapData(node, largest);
            node = largest;
        }
    }

public:
    OrderHeap() {
        root = nullptr;
        size = 0;
    }

    int getSize() {
        return size;
    }

    void insert(int id, string customer, double amount) {
        Order* node = new Order(id, customer, amount);
        size++;
        if (size == 1) {
            root = node;
            return;
        }
        vector<Order*> path = getPath(size / 2);
        Order* parent = path.back();
        if (size % 2 == 0)
            parent->left = node;
        else
            parent->right = node;
        path.push_back(node);
        heapifyUp(path);
    }

    double deleteMax() {
        double maxAmount = root->amount;
        vector<Order*> path = getPath(size);
        Order* last = path.back();
        if (size == 1) {
            delete root;
            root = nullptr;
            size--;
            return maxAmount;
        }
        Order* parent = path[path.size() - 2];
        root->id = last->id;
        root->customer = last->customer;
        root->amount = last->amount;
        if (parent->right == last)
            parent->right = nullptr;
        else
            parent->left = nullptr;
        delete last;
        size--;
        heapifyDown(root);
        return maxAmount;
    }

    vector<double> heapSort() {
        int n = size;
        vector<double> sorted(n);
        for (int i = n - 1; i >= 0; i--)
            sorted[i] = deleteMax();
        return sorted;
    }
};

int main() {
    OrderHeap heap;
    heap.insert(1, "Ahmed", 4500.0);
    heap.insert(2, "Sana", 12000.0);
    heap.insert(3, "Omar", 750.0);
    heap.insert(4, "Laiba", 8300.0);
    heap.insert(5, "Danish", 2100.0);
    heap.insert(6, "Iqra", 15600.0);
    heap.insert(7, "Faisal", 3300.0);

    vector<double> sorted = heap.heapSort();

    cout << "Order amounts in ascending order:\n";
    for (double amt : sorted)
        cout << amt << " ";
    cout << endl;
    return 0;
}
