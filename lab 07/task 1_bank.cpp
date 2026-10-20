#include <iostream>
using namespace std;

class LinearQueue {
private:
    int arr[10];
    int front;
    int rear;
    int capacity;

public:
    LinearQueue() {
        capacity = 10;
        front = -1;
        rear = -1;
    }

    bool isFull() {
        return rear == capacity - 1;
    }

    bool isEmpty() {
        return front == -1 || front > rear;
    }

    void enqueue(int token) {
        if (isFull()) {
            cout << "Queue Overflow! Cannot add customer token " << token << ".\n";
            return;
        }
        if (front == -1) {
            front = 0;
        }
        rear++;
        arr[rear] = token;
        cout << "Customer token " << token << " added to queue.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow! No customers to serve.\n";
            return;
        }
        cout << "Serving customer token: " << arr[front] << "\n";
        front++;
        if (front > rear) {
            front = -1;
            rear = -1;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "No waiting customers in the queue.\n";
            return;
        }
        cout << "Waiting customers (Front to Rear): ";
        for (int i = front; i <= rear; i++) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }

    void countWaiting() {
        if (isEmpty()) {
            cout << "Number of waiting customers: 0\n";
        } else {
            cout << "Number of waiting customers: " << (rear - front + 1) << "\n";
        }
    }
};

int main() {
    LinearQueue q;

    q.enqueue(101);
    q.enqueue(102);
    q.enqueue(103);

    q.display();
    q.countWaiting();

    q.dequeue();

    q.display();
    q.countWaiting();

    return 0;
}