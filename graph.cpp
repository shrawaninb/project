#include <iostream>
using namespace std;

// 1. Neighbor Node for Adjacency List (Pure SLL, No STL)
class FriendNode {
public:
    int userId;
    FriendNode* next;

    FriendNode(int id) {
        userId = id;
        next = NULL;
    }
};

// 2. Custom Queue for BFS Level-by-Level Traversal (No STL)
class QueueNode {
public:
    int data;
    QueueNode* next;

    QueueNode(int val) {
        data = val;
        next = NULL;
    }
};

class SimpleQueue {
private:
    QueueNode* front;
    QueueNode* rear;

public:
    SimpleQueue() {
        front = rear = NULL;
    }

    bool isEmpty() {
        return front == NULL;
    }

    void enqueue(int val) {
        QueueNode* nn = new QueueNode(val);
        if (isEmpty()) {
            front = rear = nn;
        } else {
            rear->next = nn;
            rear = nn;
        }
    }

    int dequeue() {
        if (isEmpty()) return -1;
        QueueNode* temp = front;
        int val = temp->data;
        front = front->next;
        if (front == NULL) rear = NULL;
        delete temp;
        return val;
    }
};

// Structure used to sort "People You May Know" suggestions
class Suggestion {
public:
    int userId;
    int mutualCount;
};

// 3. Social Network Graph Class
class SocialNetwork {
private:
    int numUsers;
    FriendNode** head; // Array of Adjacency List pointers

public:
    // 1. Data Structure Representation: Adjacency List using an array of SLLs
    SocialNetwork(int n) {
        numUsers = n;
        head = new FriendNode*[numUsers];
        for (int i = 0; i < numUsers; i++) {
            head[i] = NULL;
        }
    }

    ~SocialNetwork() {
        for (int i = 0; i < numUsers; i++) {
            FriendNode* curr = head[i];
            while (curr != NULL) {
                FriendNode* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] head;
    }

    // Friendship is mutual (Undirected Edge)
    void addFriendship(int u, int v) {
        // Add v to u's friend list
        FriendNode* nn1 = new FriendNode(v);
        nn1->next = head[u];
        head[u] = nn1;

        // Add u to v's friend list
        FriendNode* nn2 = new FriendNode(u);
        nn2->next = head[v];
        head[v] = nn2;
    }

    // 2. Print friend list of a given user, and the user with the most friends
    void printFriendList(int u) {
        if (u < 0 || u >= numUsers) {
            cout << ">> Invalid user ID!\n";
            return;
        }

        cout << "\nDirect friends of User " << u << ": ";
        FriendNode* curr = head[u];
        if (curr == NULL) {
            cout << "None (No friends)";
        } else {
            while (curr != NULL) {
                cout << curr->userId << " ";
                curr = curr->next;
            }
        }
        cout << "\n";
    }

    void printUserWithMostFriends() {
        int maxFriends = -1;
        int popularUser = -1;

        for (int i = 0; i < numUsers; i++) {
            int count = 0;
            FriendNode* curr = head[i];
            while (curr != NULL) {
                count++;
                curr = curr->next;
            }

            if (count > maxFriends) {
                maxFriends = count;
                popularUser = i;
            }
        }

        cout << ">> User with the MOST friends: User " << popularUser 
             << " (" << maxFriends << " friends)\n";
    }

    // 3. Level-by-level print (Direct friends, Friends-of-friends, etc.)
    void printLevels(int startUser) {
        if (startUser < 0 || startUser >= numUsers) {
            cout << ">> Invalid user ID!\n";
            return;
        }

        int* level = new int[numUsers];
        for (int i = 0; i < numUsers; i++) {
            level[i] = -1; // -1 means unreached / not connected
        }

        SimpleQueue q;
        q.enqueue(startUser);
        level[startUser] = 0;

        while (!q.isEmpty()) {
            int u = q.dequeue();
            FriendNode* curr = head[u];
            while (curr != NULL) {
                int v = curr->userId;
                if (level[v] == -1) {
                    level[v] = level[u] + 1;
                    q.enqueue(v);
                }
                curr = curr->next;
            }
        }

        // Find the maximum distance/depth reached
        int maxLevel = 0;
        for (int i = 0; i < numUsers; i++) {
            if (level[i] > maxLevel) maxLevel = level[i];
        }

        cout << "\n--- Connection Levels from User " << startUser << " ---\n";
        for (int l = 1; l <= maxLevel; l++) {
            if (l == 1) cout << "Level 1 (Direct Friends): ";
            else if (l == 2) cout << "Level 2 (Friends-of-Friends): ";
            else cout << "Level " << l << ": ";

            for (int i = 0; i < numUsers; i++) {
                if (level[i] == l) cout << i << " ";
            }
            cout << "\n";
        }

        // Identify users who cannot be reached
        cout << "Not Connected: ";
        bool foundUnreachable = false;
        for (int i = 0; i < numUsers; i++) {
            if (level[i] == -1) {
                cout << i << " ";
                foundUnreachable = true;
            }
        }
        if (!foundUnreachable) cout << "None (All users in network are connected)";
        cout << "\n-------------------------------------------\n";

        delete[] level;
    }

    // 4. Suggest "People You May Know" (exact friends-of-friends with mutual friend counts)
    void suggestPeopleYouMayKnow(int targetUser) {
        if (targetUser < 0 || targetUser >= numUsers) {
            cout << ">> Invalid user ID!\n";
            return;
        }

        bool* isDirectFriend = new bool[numUsers];
        int* mutualFriends = new int[numUsers];

        for (int i = 0; i < numUsers; i++) {
            isDirectFriend[i] = false;
            mutualFriends[i] = 0;
        }

        // Mark direct friends
        FriendNode* curr = head[targetUser];
        while (curr != NULL) {
            isDirectFriend[curr->userId] = true;
            curr = curr->next;
        }

        // Traverse friends-of-friends and count mutual connections
        curr = head[targetUser];
        while (curr != NULL) {
            int friendId = curr->userId;
            FriendNode* fof = head[friendId];

            while (fof != NULL) {
                int cand = fof->userId;
                // A candidate must not be the user themselves and not an existing direct friend
                if (cand != targetUser && !isDirectFriend[cand]) {
                    mutualFriends[cand]++;
                }
                fof = fof->next;
            }
            curr = curr->next;
        }

        // Collect all suggestions into an array for sorting
        int candidateCount = 0;
        for (int i = 0; i < numUsers; i++) {
            if (mutualFriends[i] > 0) {
                candidateCount++;
            }
        }

        if (candidateCount == 0) {
            cout << ">> No \"People You May Know\" suggestions available for User " << targetUser << ".\n";
            delete[] isDirectFriend;
            delete[] mutualFriends;
            return;
        }

        Suggestion* list = new Suggestion[candidateCount];
        int idx = 0;
        for (int i = 0; i < numUsers; i++) {
            if (mutualFriends[i] > 0) {
                list[idx].userId = i;
                list[idx].mutualCount = mutualFriends[i];
                idx++;
            }
        }

        // Sort descending by mutual friends count (Bubble sort without STL)
        for (int i = 0; i < candidateCount - 1; i++) {
            for (int j = 0; j < candidateCount - i - 1; j++) {
                if (list[j].mutualCount < list[j + 1].mutualCount) {
                    Suggestion temp = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = temp;
                }
            }
        }

        cout << "\n--- People You May Know for User " << targetUser << " (Highest mutual first) ---\n";
        for (int i = 0; i < candidateCount; i++) {
            cout << ">> User " << list[i].userId 
                 << " (" << list[i].mutualCount << " mutual friend(s))\n";
        }
        cout << "----------------------------------------------------------------------\n";

        delete[] list;
        delete[] isDirectFriend;
        delete[] mutualFriends;
    }
};

// ==================== MAIN MENU ====================
int main() {
    int n, m;
    cout << "Enter total number of users (0 to N-1): ";
    if (!(cin >> n)) return 0;

    SocialNetwork app(n);

    cout << "Enter number of friendship pairs: ";
    cin >> m;

    cout << "Enter " << m << " pairs (user1 user2):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        app.addFriendship(u, v);
    }

    int choice;
    do {
        cout << "\n=========== SOCIAL APP FRIEND MANAGEMENT ===========\n";
        cout << "1. Print Friend List of a User & User with Most Friends\n";
        cout << "2. Print Connections Level-by-Level (Direct -> FoF -> etc.)\n";
        cout << "3. Suggest \"People You May Know\" (Ranked by Mutual Friends)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int u;
                cout << "Enter User ID: ";
                cin >> u;
                app.printFriendList(u);
                app.printUserWithMostFriends();
                break;
            }
            case 2: {
                int u;
                cout << "Enter User ID to start level search: ";
                cin >> u;
                app.printLevels(u);
                break;
            }
            case 3: {
                int u;
                cout << "Enter User ID for friend suggestions: ";
                cin >> u;
                app.suggestPeopleYouMayKnow(u);
                break;
            }
            case 0:
                cout << "Exiting Social App.\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 0);

    return 0;
}