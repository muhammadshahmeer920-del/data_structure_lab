#include <iostream>
#include <string>
using namespace std;

class Stack
{
    string a[10];
    int top;

public:
    Stack()
    {
        top = -1;
    }

    void push(string s)
    {
        if (top == 9)
        {
            cout << "Stack is full\n";
            return;
        }

        a[++top] = s;
    }

    void pop()
    {
        if (top == -1)
        {
            cout << "Stack is empty\n";
            return;
        }

        top--;
    }

    void display()
    {
        if (top == -1)
        {
            cout << "No actions remaining\n";
            return;
        }

        for (int i = top; i >= 0; i--)
        {
            cout << a[i] << endl;
        }
    }

    void show()
    {
        if (top == -1)
            cout << "No current action\n";
        else
            cout << a[top] << endl;
    }
};

int main()
{
    Stack s;

    s.push("Type \"Hello\"");
    s.push("Type \"World\"");
    s.push("Add !");
    s.push("Delete \"!\"");

    cout << "Actions (TOP to BOTTOM):\n";
    s.display();

    cout << "\nPerforming first Undo...\n";
    s.pop();

    cout << "Performing second Undo...\n";
    s.pop();

    cout << "\nCurrent TOP Action:\n";
    s.show();

    cout << "\nRemaining Actions:\n";
    s.display();

    return 0;
}