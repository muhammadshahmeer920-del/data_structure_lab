#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    string id;
    Node* nxt;
    Node(string s, Node* n = nullptr) {
        id = s;
        nxt = n;
    }
};

class Stack {
private:
    Node* tp;
public:
    Stack() {
        tp = nullptr;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(string s) {
        tp = new Node(s, tp);
    }

    void pop() {
        if (isEmpty()) return;
        Node* t = tp;
        tp = tp->nxt;
        delete t;
    }

    string peek() {
        if (isEmpty()) return "";
        return tp->id;
    }

    bool isEmpty() {
        return tp == nullptr;
    }

    void display() {
        Node* c = tp;
        while (c != nullptr) {
            cout << c->id << "\n";
            c = c->nxt;
        }
    }
};

int main() {
    Stack st;

    st.push("ORD-101");
    st.push("ORD-102");
    st.push("ORD-103");
    st.push("ORD-104");

    cout << "All orders (TOP to bottom):\n";
    st.display();

    cout << "\nProcessing two orders:\n";
    cout << "Processed: " << st.peek() << "\n";
    st.pop();
    cout << "Processed: " << st.peek() << "\n";
    st.pop();

    cout << "\nCurrent TOP order: " << st.peek() << "\n";

    cout << "\nRemaining orders:\n";
    st.display();

    cout << "\nIs stack empty: " << (st.isEmpty() ? "Yes" : "No") << "\n";

    return 0;
}