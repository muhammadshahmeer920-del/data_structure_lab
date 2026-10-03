#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string imageName;
    Node* prev;
    Node* next;

    Node(string name) {
        imageName = name;
        prev = NULL;
        next = NULL;
    }
};

class ImageGallery {
private:
    Node* head;
    Node* tail;

public:
    ImageGallery() {
        head = NULL;
        tail = NULL;
    }

    void addImage(string name) {
        Node* newNode = new Node(name);
        if (head == NULL) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void displayForward() {
        cout << "Gallery (First -> Last):\n";
        Node* temp = head;
        while (temp != NULL) {
            cout << temp->imageName << " -> ";
            temp = temp->next;
        }
        cout << "END\n\n";
    }

    void displayBackward() {
        cout << "Gallery (Last -> First):\n";
        Node* temp = tail;
        while (temp != NULL) {
            cout << temp->imageName << " -> ";
            temp = temp->prev;
        }
        cout << "END\n\n";
    }
};

int main() {
    ImageGallery gallery;
    gallery.addImage("image1.jpg");
    gallery.addImage("image2.png");
    gallery.addImage("image3.jpeg");
    gallery.addImage("image4.webp");
    gallery.addImage("image5.png");

    gallery.displayForward();
    gallery.displayBackward();

    return 0;
}