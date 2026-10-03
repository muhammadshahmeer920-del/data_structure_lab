#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string playerName;
    Node* next;

    Node(string name) {
        playerName = name;
        next = NULL;
    }
};

class CircularPlayerList {
private:
    Node* head;
    Node* tail;

public:
    CircularPlayerList() {
        head = NULL;
        tail = NULL;
    }

    void addPlayer(string name) {
        Node* newNode = new Node(name);
        if (head == NULL) {
            head = tail = newNode;
            newNode->next = head;
        } else {
            tail->next = newNode;
            tail = newNode;
            tail->next = head; // Circular connection
        }
    }

    void displayTurns() {
        if (head == NULL) return;

        cout << "Players Turn (1 Full Cycle):\n";
        Node* temp = head;
        do {
            cout << "Player Turn: " << temp->playerName << endl;
            temp = temp->next;
        } while (temp != head);

        cout << "\nDemonstrating turn return after last player:\n";
        cout << "Current Player: " << tail->playerName << endl;
        cout << "Next Player (After Last): " << tail->next->playerName << "\n\n";
    }
};

int main() {
    CircularPlayerList game;
    game.addPlayer("Ali");
    game.addPlayer("Sara");
    game.addPlayer("Hamza");
    game.addPlayer("Usman");
    game.addPlayer("Zainab");

    game.displayTurns();

    return 0;
}