
#include <iostream>
#include <string>
using namespace std;

// ---------- One coach = one node ----------
class Coach {
public:
    int number;
    string type;
    Coach* next;
    Coach* prev;

    Coach(int n, string t) {
        number = n;
        type = t;
        next = NULL;
        prev = NULL;
    }
};

// ---------- The whole train = doubly linked list ----------
class Train {
    Coach* head;
    Coach* tail;
    int count;

public:
    Train() {
        head = NULL;
        tail = NULL;
        count = 0;
    }

    // 1a. Add at front
    void addFront(int number, string type) {
        Coach* newCoach = new Coach(number, type);
        if (head == NULL) {
            head = newCoach;
            tail = newCoach;
        } else {
            newCoach->next = head;
            head->prev = newCoach;
            head = newCoach;
        }
        count++;
        cout << "Coach " << number << " added at front.\n";
    }

    // 1b. Add at rear
    void addRear(int number, string type) {
        Coach* newCoach = new Coach(number, type);
        if (tail == NULL) {
            head = newCoach;
            tail = newCoach;
        } else {
            tail->next = newCoach;
            newCoach->prev = tail;
            tail = newCoach;
        }
        count++;
        cout << "Coach " << number << " added at rear.\n";
    }

    // 1c. Add at a specific position (position 1 = front)
    void addAtPosition(int number, string type, int position) {
        if (position < 1 || position > count + 1) {
            cout << "Invalid position. Choose 1 to " << count + 1 << ".\n";
            return;
        }
        if (position == 1) {
            addFront(number, type);
            return;
        }
        if (position == count + 1) {
            addRear(number, type);
            return;
        }

        // middle insertion: stop at the coach just BEFORE the position
        Coach* before = head;
        for (int i = 1; i < position - 1; i++) {
            before = before->next;
        }
        Coach* after = before->next;

        Coach* newCoach = new Coach(number, type);
        newCoach->prev = before;
        newCoach->next = after;
        before->next = newCoach;
        after->prev = newCoach;

        count++;
        cout << "Coach " << number << " added at position " << position << ".\n";
    }

    // 2. Remove a coach by number
    void removeCoach(int number) {
        if (head == NULL) {
            cout << "Train is empty.\n";
            return;
        }

        Coach* temp = head;
        while (temp != NULL && temp->number != number) {
            temp = temp->next;
        }
        if (temp == NULL) {
            cout << "Coach not found.\n";
            return;
        }

        if (temp == head && temp == tail) {        // only one coach
            head = NULL;
            tail = NULL;
        } else if (temp == head) {                 // first coach
            head = head->next;
            head->prev = NULL;
        } else if (temp == tail) {                 // last coach
            tail = tail->prev;
            tail->next = NULL;
        } else {                                   // middle coach
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
        count--;
        cout << "Coach " << number << " removed.\n";
    }

    // 3. Search a coach number
    void search(int number) {
        Coach* temp = head;
        int position = 1;
        while (temp != NULL) {
            if (temp->number == number) {
                cout << "Found! Coach " << temp->number << " (" << temp->type
                     << ") at position " << position << " from the engine.\n";
                return;
            }
            temp = temp->next;
            position++;
        }
        cout << "Coach " << number << " not found.\n";
    }

    // 4. Display from LAST coach to ENGINE
    void displayLastToEngine() {
        if (tail == NULL) {
            cout << "Train is empty.\n";
            return;
        }
        cout << "\nLast Coach -> ... -> Engine\n";
        Coach* temp = tail;
        while (temp != NULL) {
            cout << "[ " << temp->number << " | " << temp->type << " ] -> ";
            temp = temp->prev;
        }
        cout << "ENGINE\n";
    }

    // Extra: Engine to last coach
    void displayEngineToLast() {
        if (head == NULL) {
            cout << "Train is empty.\n";
            return;
        }
        cout << "\nEngine -> ... -> Last Coach\n";
        cout << "ENGINE -> ";
        Coach* temp = head;
        while (temp != NULL) {
            cout << "[ " << temp->number << " | " << temp->type << " ] -> ";
            temp = temp->next;
        }
        cout << "END\n";
    }
};

string chooseType() {
    int typeChoice;
    cout << "Coach type: 1. AC  2. Sleeper  3. General\n";
    cout << "Enter type choice: ";
    cin >> typeChoice;
    if (typeChoice == 1) return "AC";
    if (typeChoice == 2) return "Sleeper";
    return "General";
}

int main() {
    Train train;
    int choice, number, position;
    string type;

    do {
        cout << "\n===== RAILWAY COACH MANAGEMENT =====\n";
        cout << "1. Add coach at front\n";
        cout << "2. Add coach at rear\n";
        cout << "3. Add coach at specific position\n";
        cout << "4. Remove a coach\n";
        cout << "5. Search a coach\n";
        cout << "6. Display last coach to engine\n";
        cout << "7. Display engine to last coach\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter coach number: ";
                cin >> number;
                type = chooseType();
                train.addFront(number, type);
                break;

            case 2:
                cout << "Enter coach number: ";
                cin >> number;
                type = chooseType();
                train.addRear(number, type);
                break;

            case 3:
                cout << "Enter coach number: ";
                cin >> number;
                type = chooseType();
                cout << "Enter position: ";
                cin >> position;
                train.addAtPosition(number, type, position);
                break;

            case 4:
                cout << "Enter coach number to remove: ";
                cin >> number;
                train.removeCoach(number);
                break;

            case 5:
                cout << "Enter coach number to search: ";
                cin >> number;
                train.search(number);
                break;

            case 6:
                train.displayLastToEngine();
                break;

            case 7:
                train.displayEngineToLast();
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

```