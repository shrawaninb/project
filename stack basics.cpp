// PROGRAM A: BASIC STACK USING DYNAMICAL ALLOCATION (LINKED LIST)
// Covers: Q1 (stack of plates), Q8 (browser history), Q9 (undo in text editor)

#include <iostream>
#include <string>
using namespace std;

// Node structure dynamically allocated in heap memory
struct Node {
    string item;
    Node* next;

    Node(string val) {
        item = val;
        next = NULL;
    }
};

class Stack {
    Node* top; // points to the top element of the stack

public:
    Stack() {
        top = NULL;
    }

    // Destructor to free dynamically allocated nodes when object is destroyed
    ~Stack() {
        while (!isEmpty()) {
            popSilent();
        }
    }

    bool isEmpty() {
        return top == NULL;
    }

    // Push: dynamically create a node and insert at the top
    void push(string item) {
        Node* newNode = new Node(item);
        newNode->next = top;
        top = newNode;
        cout << "'" << item << "' pushed.\n";
    }

    // Pop: remove and delete the top node
    void pop() {
        if (isEmpty()) {
            cout << "Stack Underflow! The stack is empty.\n";
            return;
        }
        Node* temp = top;
        cout << "'" << temp->item << "' popped.\n";
        top = top->next;
        delete temp; // free memory
    }

    // Peek: show the top item without removing it
    void peek() {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return;
        }
        cout << "Top item is: " << top->item << endl;
    }

    // Display: show all items from top to bottom
    void display() {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return;
        }
        cout << "\nStack (top to bottom):\n";
        Node* temp = top;
        while (temp != NULL) {
            cout << "| " << temp->item << " |\n";
            temp = temp->next;
        }
        cout << "------\n";
    }

private:
    // Helper to clear memory without printing output
    void popSilent() {
        if (top != NULL) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

int main() {
    Stack s;
    int choice;
    string item;

    do {
        cout << "\n===== STACK MENU =====\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Peek\n";
        cout << "4. Display\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // clears the Enter key so getline works

        switch (choice) {
            case 1:
                cout << "Enter item (plate / URL / action): ";
                getline(cin, item);
                s.push(item);
                break;

            case 2:
                s.pop();
                break;

            case 3:
                s.peek();
                break;

            case 4:
                s.display();
                break;

            case 0:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}