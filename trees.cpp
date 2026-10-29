#include <iostream>
using namespace std;

// Node representing a book in the Binary Search Tree
class BookNode {
public:
    int bookId;
    BookNode* left;
    BookNode* right;

    BookNode(int id) {
        bookId = id;
        left = right = NULL;
    }
};

// Custom Queue for level-by-level traversal (Zero STL)
class QueueNode {
public:
    BookNode* treeNode;
    QueueNode* next;

    QueueNode(BookNode* node) {
        treeNode = node;
        next = NULL;
    }
};

class LLQueue {
private:
    QueueNode* front;
    QueueNode* rear;

public:
    LLQueue() {
        front = rear = NULL;
    }

    bool isEmpty() {
        return front == NULL;
    }

    void enqueue(BookNode* node) {
        QueueNode* nn = new QueueNode(node);
        if (isEmpty()) {
            front = rear = nn;
        } else {
            rear->next = nn;
            rear = nn;
        }
    }

    BookNode* dequeue() {
        if (isEmpty()) return NULL;
        QueueNode* temp = front;
        BookNode* res = temp->treeNode;
        front = front->next;
        if (front == NULL) rear = NULL;
        delete temp;
        return res;
    }
};

// Binary Search Tree class
class LibraryBST {
private:
    BookNode* root;

    // Recursive helper for insertion
    BookNode* insertHelper(BookNode* node, int id) {
        if (node == NULL) {
            return new BookNode(id);
        }
        if (id < node->bookId) {
            node->left = insertHelper(node->left, id);
        } else if (id > node->bookId) {
            node->right = insertHelper(node->right, id);
        }
        return node;
    }

    // Inorder traversal produces ascending order
    void inorderHelper(BookNode* node) {
        if (node == NULL) return;
        inorderHelper(node->left);
        cout << node->bookId << " ";
        inorderHelper(node->right);
    }

    // Finds the minimum node in a given subtree (Inorder Successor)
    BookNode* findMin(BookNode* node) {
        while (node != NULL && node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    // Deletion helper for 0 or 1 child
    BookNode* deleteZeroOrOneChildHelper(BookNode* node, int id, bool& status) {
        if (node == NULL) return NULL;

        if (id < node->bookId) {
            node->left = deleteZeroOrOneChildHelper(node->left, id, status);
        } else if (id > node->bookId) {
            node->right = deleteZeroOrOneChildHelper(node->right, id, status);
        } else {
            // Node found: verify child count
            if (node->left != NULL && node->right != NULL) {
                cout << ">> Error: Book ID " << id << " has TWO children. Operation 3 only allows 0 or 1 child.\n";
                status = false;
                return node;
            }

            status = true;
            // Case 1: 0 children (Leaf node)
            if (node->left == NULL && node->right == NULL) {
                delete node;
                return NULL;
            }
            // Case 2: 1 child (Right only)
            else if (node->left == NULL) {
                BookNode* temp = node->right;
                delete node;
                return temp;
            }
            // Case 3: 1 child (Left only)
            else {
                BookNode* temp = node->left;
                delete node;
                return temp;
            }
        }
        return node;
    }

    // Deletion helper for 2 children using Inorder Successor
    BookNode* deleteTwoChildrenHelper(BookNode* node, int id, bool& status) {
        if (node == NULL) return NULL;

        if (id < node->bookId) {
            node->left = deleteTwoChildrenHelper(node->left, id, status);
        } else if (id > node->bookId) {
            node->right = deleteTwoChildrenHelper(node->right, id, status);
        } else {
            // Node found: verify it has two children
            if (node->left == NULL || node->right == NULL) {
                cout << ">> Error: Book ID " << id << " does not have two children. Operation 4 requires 2 children.\n";
                status = false;
                return node;
            }

            status = true;
            // Find Inorder Successor (smallest value in right subtree)
            BookNode* succ = findMin(node->right);
            cout << ">> Inorder Successor of " << node->bookId << " is " << succ->bookId << "\n";
            node->bookId = succ->bookId;
            // Delete the successor from the right subtree
            bool dummy = false;
            node->right = deleteZeroOrOneChildHelper(node->right, succ->bookId, dummy);
        }
        return node;
    }

public:
    LibraryBST() {
        root = NULL;
    }

    // 1. Insert book ID
    void insert(int id) {
        root = insertHelper(root, id);
    }

    // 2. Print IDs in ascending order
    void printAscending() {
        if (root == NULL) {
            cout << "[Library catalog is empty]\n";
            return;
        }
        inorderHelper(root);
        cout << "\n";
    }

    // Print tree level-by-level using custom Linked-List Queue
    void printLevelByLevel() {
        if (root == NULL) {
            cout << "[Library catalog is empty]\n";
            return;
        }

        LLQueue q;
        q.enqueue(root);
        int currentLevel = 1;

        while (!q.isEmpty()) {
            int nodesAtCurrentLevel = 0;
            // Use an auxiliary queue to handle level formatting without STL
            LLQueue nextLevelQ;

            cout << "Level " << currentLevel++ << ": ";
            while (!q.isEmpty()) {
                BookNode* curr = q.dequeue();
                cout << curr->bookId << " ";

                if (curr->left != NULL) nextLevelQ.enqueue(curr->left);
                if (curr->right != NULL) nextLevelQ.enqueue(curr->right);
            }
            cout << "\n";

            while (!nextLevelQ.isEmpty()) {
                q.enqueue(nextLevelQ.dequeue());
            }
        }
    }

    // 3. Remove book with 0 or 1 child
    void removeZeroOrOneChild(int id) {
        bool status = false;
        root = deleteZeroOrOneChildHelper(root, id, status);
        if (status) {
            cout << ">> Book ID " << id << " successfully removed.\n";
            cout << "Ascending order after removal: ";
            printAscending();
        }
    }

    // 4. Remove book with 2 children using Inorder Successor
    void removeTwoChildren(int id) {
        cout << "\n--- Tree Level by Level BEFORE Removal ---\n";
        printLevelByLevel();

        bool status = false;
        root = deleteTwoChildrenHelper(root, id, status);

        if (status) {
            cout << "\n--- Tree Level by Level AFTER Removal ---\n";
            printLevelByLevel();
            cout << "Ascending order after removal: ";
            printAscending();
        }
    }
};

int main() {
    LibraryBST library;
    int choice;

    do {
        cout << "\n================ LIBRARY BST MANAGEMENT ================\n";
        cout << "1. Insert Book IDs\n";
        cout << "2. Print Book IDs in Ascending Order (Inorder)\n";
        cout << "3. Remove Book with 0 or 1 Child (Print Ascending After)\n";
        cout << "4. Remove Book with 2 Children using Inorder Successor (Print Levels)\n";
        cout << "5. Display Tree Level by Level\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int n, id;
                cout << "How many books arrived? ";
                cin >> n;
                cout << "Enter " << n << " Book IDs: ";
                for (int i = 0; i < n; i++) {
                    cin >> id;
                    library.insert(id);
                }
                cout << ">> Books inserted successfully.\n";
                break;
            }
            case 2:
                cout << "Book IDs in Ascending Order: ";
                library.printAscending();
                break;

            case 3: {
                int id;
                cout << "Enter Book ID to remove (0 or 1 child): ";
                cin >> id;
                library.removeZeroOrOneChild(id);
                break;
            }

            case 4: {
                int id;
                cout << "Enter Book ID to remove (2 children): ";
                cin >> id;
                library.removeTwoChildren(id);
                break;
            }

            case 5:
                library.printLevelByLevel();
                break;

            case 0:
                cout << "Exiting system.\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}

#include <iostream>
#include <string>
using namespace std;

// 1. Threaded BST Node
class TBSTNode {
public:
    int ticketNo;
    TBSTNode* left;
    TBSTNode* right;
    bool lthread; // true if left points to inorder predecessor (thread), false if real left child
    bool rthread; // true if right points to inorder successor (thread), false if real right child

    TBSTNode(int val) {
        ticketNo = val;
        left = right = NULL;
        lthread = rthread = true; // Initially, both links are threads
    }
};

// 2. Threaded BST Class
class RailwayCounterTBST {
private:
    TBSTNode* root;

public:
    RailwayCounterTBST() {
        root = NULL;
    }

    // 1. Insert ticket numbers setting threads correctly
    void insert(int key) {
        TBSTNode* nn = new TBSTNode(key);

        // Case 1: First ticket (root node)
        if (root == NULL) {
            root = nn;
            cout << ">> Ticket " << key << " inserted as root.\n";
            return;
        }

        TBSTNode* curr = root;
        TBSTNode* parent = NULL;

        // Traverse down the tree while following real child links
        while (curr != NULL) {
            if (key == curr->ticketNo) {
                cout << ">> Duplicate ticket number " << key << " not allowed!\n";
                delete nn;
                return;
            }

            parent = curr;

            if (key < curr->ticketNo) {
                if (!curr->lthread) {
                    curr = curr->left; // Move to real left child
                } else {
                    break; // Reached insertion position
                }
            } else {
                if (!curr->rthread) {
                    curr = curr->right; // Move to real right child
                } else {
                    break; // Reached insertion position
                }
            }
        }

        // Link the new node to its parent and assign thread pointers
        if (key < parent->ticketNo) {
            nn->left = parent->left;    // Predecessor of nn is predecessor of parent
            nn->right = parent;         // Successor of nn is parent
            parent->lthread = false;    // Parent now has a real left child
            parent->left = nn;
        } else {
            nn->left = parent;          // Predecessor of nn is parent
            nn->right = parent->right;  // Successor of nn is successor of parent
            parent->rthread = false;    // Parent now has a real right child
            parent->right = nn;
        }

        cout << ">> Ticket " << key << " successfully inserted.\n";
    }

    // 4. Inorder Successor using Threads (O(1) auxiliary space)
    TBSTNode* inorderSuccessor(TBSTNode* node) {
        // If right link is a thread, it directly points to the inorder successor!
        if (node->rthread) {
            return node->right;
        }

        // If right link is a real child, successor is the leftmost node in the right subtree
        node = node->right;
        while (!node->lthread) {
            node = node->left;
        }
        return node;
    }

    // 3. Print ticket numbers in ascending order (No recursion, No stack)
    void inorderTraversal() {
        if (root == NULL) {
            cout << ">> No tickets booked yet (Tree is empty).\n";
            return;
        }

        // Step A: Reach the leftmost (smallest) node in the tree
        TBSTNode* curr = root;
        while (!curr->lthread) {
            curr = curr->left;
        }

        // Step B: Follow inorder successors repeatedly
        cout << "\n>> Booked Tickets in Ascending Order (Inorder): ";
        while (curr != NULL) {
            cout << curr->ticketNo << " ";
            curr = inorderSuccessor(curr);
        }
        cout << "\n";
    }

    // 2. Print every node's left and right links, marking real child vs thread
    void printLinks() {
        if (root == NULL) {
            cout << ">> Tree is empty.\n";
            return;
        }

        // Find leftmost node to start inorder scan
        TBSTNode* curr = root;
        while (!curr->lthread) {
            curr = curr->left;
        }

        cout << "\n--- Ticket Node Links Specification ---\n";
        while (curr != NULL) {
            cout << "Ticket [" << curr->ticketNo << "]: ";

            // Left link specification
            cout << "Left -> ";
            if (curr->left != NULL) cout << curr->left->ticketNo;
            else cout << "NULL";
            cout << (curr->lthread ? " (Thread)" : " (Real Child)");

            // Right link specification
            cout << " | Right -> ";
            if (curr->right != NULL) cout << curr->right->ticketNo;
            else cout << "NULL";
            cout << (curr->rthread ? " (Thread)" : " (Real Child)") << "\n";

            curr = inorderSuccessor(curr);
        }
        cout << "----------------------------------------\n";
    }

    // Search for a ticket and find its inorder successor using threads
    void findSuccessorOfTicket(int key) {
        if (root == NULL) {
            cout << ">> Tree is empty.\n";
            return;
        }

        TBSTNode* curr = root;
        while (curr != NULL) {
            if (curr->ticketNo == key) {
                TBSTNode* succ = inorderSuccessor(curr);
                if (succ != NULL) {
                    cout << ">> Inorder Successor of Ticket " << key << " is: " << succ->ticketNo << "\n";
                } else {
                    cout << ">> Ticket " << key << " is the highest ticket; it has NO inorder successor (NULL).\n";
                }
                return;
            }

            if (key < curr->ticketNo) {
                if (!curr->lthread) curr = curr->left;
                else break;
            } else {
                if (!curr->rthread) curr = curr->right;
                else break;
            }
        }

        cout << ">> Ticket number " << key << " not found in the booking system.\n";
    }
};

// 3. Menu-Driven Main Function
int main() {
    RailwayCounterTBST railway;
    int choice;

    do {
        cout << "\n===== RAILWAY TICKET COUNTER (THREADED BST) =====\n";
        cout << "1. Book Ticket(s) (Insert into TBST)\n";
        cout << "2. Print Node Links (Identify Real Child vs Thread)\n";
        cout << "3. Display Booked Tickets in Ascending Order (Inorder)\n";
        cout << "4. Find Inorder Successor of a Ticket\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int n, ticket;
                cout << "How many tickets to insert? ";
                cin >> n;
                cout << "Enter " << n << " ticket numbers: ";
                for (int i = 0; i < n; i++) {
                    cin >> ticket;
                    railway.insert(ticket);
                }
                break;
            }
            case 2:
                railway.printLinks();
                break;

            case 3:
                railway.inorderTraversal();
                break;

            case 4: {
                int ticket;
                cout << "Enter Ticket Number to find its successor: ";
                cin >> ticket;
                railway.findSuccessorOfTicket(ticket);
                break;
            }

            case 0:
                cout << "Exiting Railway Counter System.\n";
                break;

            default:
                cout << "Invalid choice! Please select again.\n";
        }
    } while (choice != 0);

    return 0;
}

#include <iostream>
using namespace std;

// 1. Binary Search Tree Node
class PermitNode {
public:
    int permitNo;
    PermitNode* left;
    PermitNode* right;

    PermitNode(int val) {
        permitNo = val;
        left = right = NULL;
    }
};

// 2. Custom Singly Linked-List Queue for Level-by-Level Traversal (Zero STL)
class QueueNode {
public:
    PermitNode* treeNode;
    QueueNode* next;

    QueueNode(PermitNode* node) {
        treeNode = node;
        next = NULL;
    }
};

class LLQueue {
private:
    QueueNode* front;
    QueueNode* rear;

public:
    LLQueue() {
        front = rear = NULL;
    }

    bool isEmpty() {
        return front == NULL;
    }

    void enqueue(PermitNode* node) {
        QueueNode* nn = new QueueNode(node);
        if (isEmpty()) {
            front = rear = nn;
        } else {
            rear->next = nn;
            rear = nn;
        }
    }

    PermitNode* dequeue() {
        if (isEmpty()) return NULL;
        QueueNode* temp = front;
        PermitNode* res = temp->treeNode;
        front = front->next;
        if (front == NULL) rear = NULL;
        delete temp;
        return res;
    }
};

// 3. Parking Lot BST Class
class ParkingLotBST {
private:
    PermitNode* root;

    // Helper: Recursive Insert
    PermitNode* insertHelper(PermitNode* node, int val) {
        if (node == NULL) {
            return new PermitNode(val);
        }
        if (val < node->permitNo) {
            node->left = insertHelper(node->left, val);
        } else if (val > node->permitNo) {
            node->right = insertHelper(node->right, val);
        } else {
            cout << ">> Duplicate permit number " << val << " not allowed!\n";
        }
        return node;
    }

    // Helper: Find Minimum Node in Subtree (Inorder Successor)
    PermitNode* findMin(PermitNode* node) {
        while (node != NULL && node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    // Helper: Recursive Deletion (handles 0, 1, or 2 children)
    PermitNode* deleteHelper(PermitNode* node, int val, bool& found) {
        if (node == NULL) return NULL;

        if (val < node->permitNo) {
            node->left = deleteHelper(node->left, val, found);
        } else if (val > node->permitNo) {
            node->right = deleteHelper(node->right, val, found);
        } else {
            // Node found
            found = true;

            // Case 1: No child (Leaf node)
            if (node->left == NULL && node->right == NULL) {
                delete node;
                return NULL;
            }
            // Case 2: One child (Right only)
            else if (node->left == NULL) {
                PermitNode* temp = node->right;
                delete node;
                return temp;
            }
            // Case 2: One child (Left only)
            else if (node->right == NULL) {
                PermitNode* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: Two children (Replace with Inorder Successor)
            else {
                PermitNode* succ = findMin(node->right);
                node->permitNo = succ->permitNo;
                // Delete the successor from right subtree
                bool dummy = false;
                node->right = deleteHelper(node->right, succ->permitNo, dummy);
            }
        }
        return node;
    }

public:
    ParkingLotBST() {
        root = NULL;
    }

    // 1. Insert permit numbers one by one
    void insert(int val) {
        root = insertHelper(root, val);
    }

    // 2. Print permit numbers level by level, from the root downwards
    void printLevelByLevel() {
        if (root == NULL) {
            cout << "[Parking lot database is empty]\n";
            return;
        }

        LLQueue q;
        q.enqueue(root);
        int level = 1;

        cout << "\n--- Parking Permits Level by Level ---\n";
        while (!q.isEmpty()) {
            LLQueue nextLevelQ;
            cout << "Level " << level++ << ": ";

            while (!q.isEmpty()) {
                PermitNode* curr = q.dequeue();
                cout << curr->permitNo << " ";

                if (curr->left != NULL) nextLevelQ.enqueue(curr->left);
                if (curr->right != NULL) nextLevelQ.enqueue(curr->right);
            }
            cout << "\n";

            // Transfer nodes for the next level
            while (!nextLevelQ.isEmpty()) {
                q.enqueue(nextLevelQ.dequeue());
            }
        }
        cout << "--------------------------------------\n";
    }

    // 3. Remove an expired permit and show the tree level by level after removal
    void removePermit(int val) {
        if (root == NULL) {
            cout << ">> Parking lot database is empty!\n";
            return;
        }

        bool found = false;
        root = deleteHelper(root, val, found);

        if (found) {
            cout << ">> Permit " << val << " expired and was successfully removed.\n";
            cout << "\nPermits level by level AFTER removal:";
            printLevelByLevel();
        } else {
            cout << ">> Permit " << val << " not found in the parking database.\n";
        }
    }
};

// ==================== MAIN MENU ====================
int main() {
    ParkingLotBST lot;
    int choice;

    do {
        cout << "\n===== PARKING LOT PERMIT BST MANAGEMENT =====\n";
        cout << "1. Issue/Insert Permits (Input one by one)\n";
        cout << "2. Print Permits Level by Level (Root Downwards)\n";
        cout << "3. Expire/Remove a Permit (Print Level by Level After)\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int n, val;
                cout << "How many permits to issue? ";
                cin >> n;
                cout << "Enter " << n << " permit numbers in order of arrival: ";
                for (int i = 0; i < n; i++) {
                    cin >> val;
                    lot.insert(val);
                }
                cout << ">> All permits recorded.\n";
                break;
            }
            case 2:
                lot.printLevelByLevel();
                break;

            case 3: {
                int val;
                cout << "Enter expired permit number to remove: ";
                cin >> val;
                lot.removePermit(val);
                break;
            }

            case 0:
                cout << "Closing parking management system.\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}