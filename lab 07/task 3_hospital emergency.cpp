#include <iostream>
#include <string>
using namespace std;

struct Patient {
    string id;
    int priority;
};

class PriorityQueue {
private:
    Patient arr[10];
    int count;
    int capacity;

public:
    PriorityQueue() {
        capacity = 10;
        count = 0;
    }

    bool isFull() {
        return count == capacity;
    }

    bool isEmpty() {
        return count == 0;
    }

    void enqueue(string id, int priority) {
        if (isFull()) {
            cout << "Queue Full! Cannot insert patient " << id << ".\n";
            return;
        }
        arr[count].id = id;
        arr[count].priority = priority;
        count++;
        cout << "Patient " << id << " with priority " << priority << " added.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Empty! No patients to treat.\n";
            return;
        }

        int highestPriorityIndex = 0;
        for (int i = 1; i < count; i++) {
            if (arr[i].priority < arr[highestPriorityIndex].priority) {
                highestPriorityIndex = i;
            }
        }

        cout << "Treating patient: " << arr[highestPriorityIndex].id << " (Priority " << arr[highestPriorityIndex].priority << ")\n";

        for (int i = highestPriorityIndex; i < count - 1; i++) {
            arr[i] = arr[i + 1];
        }
        count--;
    }

    void display() {
        if (isEmpty()) {
            cout << "No patients waiting.\n";
            return;
        }
        cout << "Waiting Patients:\n";
        for (int i = 0; i < count; i++) {
            cout << "Patient ID: " << arr[i].id << " | Priority: " << arr[i].priority << "\n";
        }
    }
};

int main() {
    PriorityQueue pq;

    pq.enqueue("P101", 3);
    pq.enqueue("P102", 1);
    pq.enqueue("P103", 2);

    pq.display();

    pq.dequeue();

    pq.display();

    return 0;
}