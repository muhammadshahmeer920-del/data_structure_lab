#include <iostream>
#include <string>
using namespace std;
struct Node {
    string patientID;
    Node* next;

    Node(string id) 
    {
        patientID = id;
        next = nullptr;
    }
};

class PatientQueue {
private:
    Node* head;

public:
    PatientQueue() 
    {
        head = nullptr;
    }

    void enqueue(string id) 
    {
        Node* newNode = new Node(id);
        if (head == nullptr) 
        {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) 
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void dequeue() {
        if (head == nullptr) 
        {
            cout << "No patients in the queue." << endl;
            return;
        }
        Node* temp = head;
        cout << "Patient " << temp->patientID << " is being served." << endl;
        head = head->next;
        delete temp;
    }

    void displayQueue() {
        if (head == nullptr) 
        {
            cout << "Queue is empty." << endl;
            return;
        }
        Node* temp = head;
        while (temp != nullptr) 
        {
            cout << temp->patientID;
            if (temp->next != nullptr) 
            {
                cout << " -> ";
            }
            temp = temp->next;
        }
        cout << endl;
    }

    ~PatientQueue() {
        while (head != nullptr) 
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() 
{
    PatientQueue queue;

    queue.enqueue("P101");
    queue.enqueue("P102");
    queue.enqueue("P103");
    queue.enqueue("P104");

    cout << "Waiting Patients:" << endl;
    queue.displayQueue();
    cout << endl;

    queue.dequeue();
    cout << endl;

    cout << "Updated Queue:" << endl;
    queue.displayQueue();
    cout << endl;

    string newPatient;
    cout << "Enter new Patient ID to add at the end: ";
    cin >> newPatient;

    queue.enqueue(newPatient);

    cout << "\nQueue after adding new patient:" << endl;
    queue.displayQueue();

    return 0;
}