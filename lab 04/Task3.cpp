#include <iostream>
#include <string>
using namespace std;
struct Node 
{
    string productID;
    Node* next;

    Node(string id) 
    {
        productID = id;
        next = nullptr;
    }
};
class ShoppingCart {
private:
    Node* head;

public:
    ShoppingCart() 
    {
        head = nullptr;
    }

    void addProduct(string id) 
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

    void removeProduct(string id) 
    {
        if (head == nullptr) 
        {
            cout << "Cart is empty." << endl;
            return;
        }

        if (head->productID == id) 
        {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Product " << id << " removed successfully." << endl;
            return;
        }

        Node* current = head;
        Node* previous = nullptr;

        while (current != nullptr && current->productID != id) 
        {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) 
        {
            cout << "Product " << id << " not found in the cart." << endl;
            return;
        }

        previous->next = current->next;
        delete current;
        cout << "Product " << id << " removed successfully." << endl;
    }

    void displayCart() {
        if (head == nullptr) 
        {
            cout << "Cart is empty." << endl;
            return;
        }
        Node* temp = head;
        while (temp != nullptr) 
        {
            cout << temp->productID;
            if (temp->next != nullptr) 
            {
                cout << " -> ";
            }
            temp = temp->next;
        }
        cout << endl;
    }

    ~ShoppingCart() {
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
    ShoppingCart cart;
    int count;

    cout << "How many products do you want to add to the cart? ";
    cin >> count;

    for (int i = 1; i <= count; i++) {
        string id;
        cout << "Enter Product ID " << i << ": ";
        cin >> id;
        cart.addProduct(id);
    }

    cout << "\nShopping Cart:" << endl;
    cart.displayCart();
    cout << endl;

    string removeID;
    cout << "Enter Product ID to Remove: ";
    cin >> removeID;

    cart.removeProduct(removeID);
    cout << endl;

    cout << "Updated Cart:" << endl;
    cart.displayCart();

    return 0;
}