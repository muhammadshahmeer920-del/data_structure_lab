#include <iostream>
using namespace std;

struct Node
{
    int roll;
    Node* next;
};

void add(Node*& head, int r)
{
    Node* n = new Node;
    n->roll = r;
    n->next = NULL;

    if (head == NULL)
    {
        head = n;
    }
    else
    {
        Node* t = head;

        while (t->next != NULL)
        {
            t = t->next;
        }

        t->next = n;
    }

    cout << "Student " << r << " successfully added." << endl;
}

void display(Node* head)
{
    Node* t = head;

    cout << "Registered Students: ";

    while (t != NULL)
    {
        cout << t->roll << " ";
        t = t->next;
    }

    cout << endl;
}

void search(Node* head, int r)
{
    Node* t = head;

    while (t != NULL)
    {
        if (t->roll == r)
        {
            cout << "Student Found" << endl;
            return;
        }

        t = t->next;
    }

    cout << "Student Not Found" << endl;
}

int main()
{
    Node* head = NULL;

    add(head, 101);
    add(head, 105);
    add(head, 108);
    add(head, 112);

    cout << "\n--- Current List ---" << endl;
    display(head);

    int newRoll;
    cout << "\nEnter a new Roll Number to add at the end: ";
    cin >> newRoll;

    add(head, newRoll);

    cout << "\n--- Updated List ---" << endl;
    display(head);

    int r;
    cout << "\nEnter Roll Number to Search: ";
    cin >> r;

    search(head, r);

    return 0;
}