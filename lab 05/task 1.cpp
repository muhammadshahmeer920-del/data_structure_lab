#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string url;
    Node* prev;
    Node* next;

    Node(string val) {
        url = val;
        prev = NULL;
        next = NULL;
    }
};

class BrowserHistory {
private:
    Node* head;
    Node* tail;

public:
    BrowserHistory() {
        head = NULL;
        tail = NULL;
    }

    void addWebsite(string url) {
        Node* newNode = new Node(url);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void displayForward() {
        cout << "Browser History (First -> Last):\n";
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->url << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n\n";
    }

    void displayBackward() {
        cout << "Browser History (Last -> First):\n";
        Node* temp = tail;
        while (temp != NULL) {
            cout << temp->url << " -> ";
            temp = temp->prev;
        }
        cout << "NULL\n\n";
    }
};

int main() {
    BrowserHistory history;
    history.addWebsite("google.com");
    history.addWebsite("github.com");
    history.addWebsite("youtube.com");
    history.addWebsite("stackoverflow.com");
    history.addWebsite("linkedin.com");

    history.displayForward();
    history.displayBackward();

    return 0;
}