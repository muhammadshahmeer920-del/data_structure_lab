#include <iostream>
using namespace std;

class CircularQueue {
private:
    int arr[5];
    int front;
    int rear;
    int capacity;

public:
    CircularQueue() {
        capacity = 5;
        front = -1;
        rear = -1;
    }

    bool isFull() {
        return (rear + 1) % capacity == front;
    }

    bool isEmpty() {
        return front == -1;
    }

    void enqueue(int packetId) {
        if (isFull()) {
            cout << "Buffer Overflow! Packet " << packetId << " dropped.\n";
            return;
        }
        if (isEmpty()) {
            front = 0;
            rear = 0;
        } else {
            rear = (rear + 1) % capacity;
        }
        arr[rear] = packetId;
        cout << "Packet " << packetId << " inserted into buffer.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Buffer Underflow! No packets to transmit.\n";
            return;
        }
        cout << "Transmitting packet: " << arr[front] << "\n";
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % capacity;
        }
    }

    void display() {
        if (isEmpty()) {
            cout << "No packets waiting for transmission.\n";
            return;
        }
        cout << "Waiting packets: ";
        int i = front;
        while (true) {
            cout << arr[i] << " ";
            if (i == rear) break;
            i = (i + 1) % capacity;
        }
        cout << "\n";
    }
};

int main() {
    CircularQueue q;

    q.enqueue(201);
    q.enqueue(202);
    q.enqueue(203);

    q.display();

    q.dequeue();

    q.display();

    q.enqueue(204);
    q.enqueue(205);
    q.enqueue(206);

    q.display();

    return 0;
}