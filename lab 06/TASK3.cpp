#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
    string id;
    Node* next;

    Node(string s)
    {
        id = s;
        next = NULL;
    }
};

class Stack
{
    Node* top;

public:
    Stack()
    {
        top = NULL;
    }

    void push(string s)
    {
        Node* n = new Node(s);
        n->next = top;
        top = n;
    }

    void pop()
    {
        if (top == NULL)
        {
            cout << "No requests available\n";
            return;
        }

        Node* t = top;
        top = top->next;
        delete t;
    }

    void display()
    {
        if (top == NULL)
        {
            cout << "No requests remaining\n";
            return;
        }

        Node* t = top;

        while (t != NULL)
        {
            cout << t->id << endl;
            t = t->next;
        }
    }

    void show()
    {
        if (top == NULL)
            cout << "No current request\n";
        else
            cout << top->id << endl;
    }

    ~Stack()
    {
        while (top != NULL)
        {
            Node* t = top;
            top = top->next;
            delete t;
        }
    }
};

int main()
{
    Stack s;

    s.push("P101");
    s.push("P102");
    s.push("P103");
    s.push("P104");

    cout << "Patient Requests (TOP to BOTTOM):\n";
    s.display();

    cout << "\nHandling Latest Request...\n";
    s.pop();

    cout << "\nCurrent TOP Request:\n";
    s.show();

    cout << "\nRemaining Requests:\n";
    s.display();

    return 0;
}