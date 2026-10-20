#include <iostream>
using namespace std;

class Deque {
private:
    int arr[10];
    int front;
    int rear;
    int capacity;

public:
    Deque() {
        capacity = 10;
        front = -1;
        rear = -1;
    }

    bool isFull() {
        return (front == 0 && rear == capacity - 1) || (front == rear + 1);
    }

    bool isEmpty() {
        return front == -1;
    }

    void insertFront(int val) {
        if (isFull()) {
            cout << "Deque Overflow!\n";
            return;
        }
        if (isEmpty()) {
            front = 0;
            rear = 0;
        } else if (front == 0) {
            front = capacity - 1;
        } else {
            front--;
        }
        arr[front] = val;
        cout << "Inserted " << val << " at front.\n";
    }

    void insertRear(int val) {
        if (isFull()) {
            cout << "Deque Overflow!\n";
            return;
        }
        if (isEmpty()) {
            front = 0;
            rear = 0;
        } else if (rear == capacity - 1) {
            rear = 0;
        } else {
            rear++;
        }
        arr[rear] = val;
        cout << "Inserted " << val << " at rear.\n";
    }

    void deleteFront() {
        if (isEmpty()) {
            cout << "Deque Underflow!\n";
            return;
        }
        cout << "Removed " << arr[front] << " from front.\n";
        if (front == rear) {
            front = -1;
            rear = -1;
        } else if (front == capacity - 1) {
            front = 0;
        } else {
            front++;
        }
    }

    void deleteRear() {
        if (isEmpty()) {
            cout << "Deque Underflow!\n";
            return;
        }
        cout << "Removed " << arr[rear] << " from rear.\n";
        if (front == rear) {
            front = -1;
            rear = -1;
        } else if (rear == 0) {
            rear = capacity - 1;
        } else {
            rear--;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "Deque is empty.\n";
            return;
        }
        cout << "Front -> ";
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear) break;
            i = (i + 1) % capacity;
        }
        cout << "<- Rear\n";
    }
};

int main() {
    Deque dq;

    dq.insertRear(301);
    dq.insertRear(302);
    dq.insertFront(300);

    dq.display();

    dq.deleteFront();
    dq.display();

    dq.deleteRear();
    dq.display();

    return 0;
}