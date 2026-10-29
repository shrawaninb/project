QUEUE

#include <iostream>
#include <string>
using namespace std;

// 1. Node Class
class node {
public:
    int id;
    string name;
    node* next;

    node(int i, string n) {
        id = i;
        name = n;
        next = NULL;
    }
};

// 2. Queue Class
class queue {
private:
    node* front;
    node* rear;

public:
    queue() {
        front = rear = NULL;
    }

    bool isEmpty() {
        return front == NULL;
    }

    // Enqueue
    void enqueue(int id, string name) {
        node* nn = new node(id, name);
        if (isEmpty()) {
            front = rear = nn;
        } else {
            rear->next = nn;
            rear = nn;
        }
        cout << "Added: " << name << " (ID: " << id << ")\n";
    }

    // Dequeue from front
    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow! No elements.\n";
            return;
        }
        node* temp = front;
        cout << "Removed: " << temp->name << " (ID: " << temp->id << ")\n";
        front = front->next;
        if (front == NULL) {
            rear = NULL; // Reset rear when queue becomes empty
        }
        delete temp;
    }

    // Peek
    void peek() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return;
        }
        cout << "Front element -> ID: " << front->id << ", Name: " << front->name << "\n";
    }

    // Display
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return;
        }
        node* curr = front;
        int pos = 1;
        cout << "\n--- Queue Elements ---\n";
        while (curr != NULL) {
            cout << pos++ << ". ID: " << curr->id << " | Name: " << curr->name << "\n";
            curr = curr->next;
        }
        cout << "----------------------\n";
    }

    // Delete specific node by ID
    void dequeuewithid(int target) {
        if (isEmpty()) {
            cout << "Queue is empty!\n";
            return;
        }

        // Case 1: Target is at the front
        if (front->id == target) {
            dequeue();
            return;
        }

        // Case 2: Target is in the middle or rear
        node* prev = front;
        node* curr = front->next;

        while (curr != NULL && curr->id != target) {
            prev = curr;
            curr = curr->next;
        }

        if (curr == NULL) {
            cout << "ID " << target << " not found in queue.\n";
            return;
        }

        prev->next = curr->next;
        if (curr == rear) {
            rear = prev; // Update rear if last element was deleted
        }
        cout << "Removed ID " << curr->id << " (" << curr->name << ") from queue.\n";
        delete curr;
    }
};

// 3. Main Function
int main() {
    queue q;
    int choice;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Enqueue\n";
        cout << "2. Dequeue\n";
        cout << "3. Dequeue by ID\n";
        cout << "4. Peek\n";
        cout << "5. Display\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string name;
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter Name: ";
                cin >> name;
                q.enqueue(id, name);
                break;
            }
            case 2:
                q.dequeue();
                break;

            case 3: {
                int target;
                cout << "Enter ID to remove: ";
                cin >> target;
                q.dequeuewithid(target);
                break;
            }
            case 4:
                q.peek();
                break;

            case 5:
                q.display();
                break;

            case 0:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice! Please re-enter.\n";
        }
    } while (choice != 0);

    return 0;
}



#include <iostream>
#include <string>
using namespace std;

// Node representing a single driver in the queue
class DriverNode {
public:
    int driverId;
    string carTier; // e.g., Sedan, SUV, Premier, XL
    DriverNode* next;

    DriverNode(int id, string tier) {
        driverId = id;
        carTier = tier;
        next = NULL;
    }
};

// Queue class implemented using a Singly Linked List
class AirportDispatchQueue {
private:
    DriverNode* front;
    DriverNode* rear;
    int count;

public:
    AirportDispatchQueue() {
        front = rear = NULL;
        count = 0;
    }

    ~AirportDispatchQueue() {
        while (!isEmpty()) {
            DriverNode* temp = front;
            front = front->next;
            delete temp;
        }
    }

    bool isEmpty() {
        return front == NULL;
    }

    // 1. Add a driver to the rear of the queue (Enqueue)
    void addDriver(int id, string tier) {
        DriverNode* newDriver = new DriverNode(id, tier);
        if (isEmpty()) {
            front = rear = newDriver;
        } else {
            rear->next = newDriver;
            rear = newDriver;
        }
        count++;
        cout << ">> Driver [" << id << " | " << tier << "] added to the dispatch line.\n";
    }

    // 2. Display the number of waiting drivers in the queue
    void displayDriverCount() {
        cout << ">> Number of waiting drivers in queue: " << count << "\n";
    }

    // 3. Remove the driver waiting the longest and assign them to a rider (Dequeue)
    void dispatchDriver() {
        if (isEmpty()) {
            cout << ">> No drivers available for dispatch (Queue is empty)!\n";
            return;
        }

        DriverNode* temp = front;
        cout << ">> Assigned Ride to Driver ID: " << temp->driverId 
             << " (" << temp->carTier << ") [Longest waiting driver]\n";

        front = front->next;
        if (front == NULL) {
            rear = NULL; // Reset rear when queue becomes completely empty
        }

        delete temp;
        count--;
    }

    // 4. Search for and remove a driver if app disconnects or GPS goes offline
    void removeOfflineDriver(int targetId) {
        if (isEmpty()) {
            cout << ">> Queue is empty. No driver to remove.\n";
            return;
        }

        // Case A: The offline driver is at the front
        if (front->driverId == targetId) {
            DriverNode* temp = front;
            front = front->next;
            if (front == NULL) {
                rear = NULL;
            }
            cout << ">> Driver ID " << targetId << " (at front) went offline and was removed.\n";
            delete temp;
            count--;
            return;
        }

        // Case B: Search in the middle or at the rear
        DriverNode* prev = front;
        DriverNode* curr = front->next;

        while (curr != NULL && curr->driverId != targetId) {
            prev = curr;
            curr = curr->next;
        }

        if (curr == NULL) {
            cout << ">> Driver ID " << targetId << " not found in the queue.\n";
            return;
        }

        // Unlink the node
        prev->next = curr->next;

        // If the removed driver was at the rear, update rear to prev
        if (curr == rear) {
            rear = prev;
        }

        cout << ">> Driver ID " << targetId << " went offline and was removed from the queue.\n";
        delete curr;
        count--;
    }

    // Helper: Display all waiting drivers in order
    void displayQueue() {
        if (isEmpty()) {
            cout << ">> Queue is currently empty.\n";
            return;
        }

        DriverNode* curr = front;
        int pos = 1;
        cout << "\n--- Current Waiting Queue (" << count << " drivers) ---\n";
        while (curr != NULL) {
            cout << pos++ << ". Driver ID: " << curr->driverId 
                 << " | Car Tier: " << curr->carTier;
            if (curr == front) cout << "  <-- [NEXT TO DISPATCH]";
            if (curr == rear) cout << "  <-- [LAST JOINED]";
            cout << "\n";
            curr = curr->next;
        }
        cout << "-------------------------------------------\n";
    }
};

int main() {
    AirportDispatchQueue dispatchQ;
    int choice;

    do {
        cout << "\n===== AIRPORT DRIVER DISPATCH SYSTEM =====\n";
        cout << "1. Add Driver to Queue (Arrived at Airport)\n";
        cout << "2. Display Total Waiting Drivers Count\n";
        cout << "3. Dispatch Longest Waiting Driver to Rider\n";
        cout << "4. Remove Disconnected/Offline Driver by ID\n";
        cout << "5. Display Active Driver Queue\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string tier;
                cout << "Enter Driver ID: ";
                cin >> id;
                cout << "Enter Car Tier (e.g., Sedan, SUV, Premier, XL): ";
                cin >> tier;
                dispatchQ.addDriver(id, tier);
                break;
            }
            case 2:
                dispatchQ.displayDriverCount();
                break;

            case 3:
                dispatchQ.dispatchDriver();
                break;

            case 4: {
                int id;
                cout << "Enter Driver ID who went offline: ";
                cin >> id;
                dispatchQ.removeOfflineDriver(id);
                break;
            }

            case 5:
                dispatchQ.displayQueue();
                break;

            case 0:
                cout << "Shutting down dispatch system.\n";
                break;

            default:
                cout << "Invalid choice! Please select again.\n";
        }
    } while (choice != 0);

    return 0;
}