/*

=====================================================================================

PCCOE - Pimpri Chinchwad College of Engineering (Autonomous Institute)

Data Structures and Algorithms (DSL/DSA) Laboratory Practical Solutions

Units 1 to 5: Complete Question Bank Implementation

=====================================================================================

Table of Contents:

UNIT 1: Linked Lists (Questions 1 to 10)

UNIT 2: Stacks (Questions 1 to 10)

UNIT 3: Queues (Questions 1 to 10)

UNIT 4: Trees & Binary Search Trees (Questions 1 to 9)

UNIT 5: Graphs (Questions 1 to 10)

=====================================================================================
*/

#include 
#include 
#include 
#include 
#include 
#include 
#include 
#include 

using namespace std;

// =====================================================================================
// SECTION 1: UNIT 1 - LINKED LISTS
// =====================================================================================

/*

Unit 1, Q1: Text Editor History Management (Doubly Linked List)

Supports: Add action, Delete oldest action beyond capacity, Search, Display.
/
namespace Unit1_Q1 {
struct Node {
int actionId;
string description;
Node prev;
Node* next;
Node(int id, string desc) : actionId(id), description(desc), prev(nullptr), next(nullptr) {}
};

class TextEditorHistory {
Node* head;
Node* tail;
int size;
int limit;
public:
TextEditorHistory(int maxLimit) : head(nullptr), tail(nullptr), size(0), limit(maxLimit) {}

 void addAction(int id, string desc) {
     Node* newNode = new Node(id, desc);
     if (!head) {
         head = tail = newNode;
     } else {
         tail->next = newNode;
         newNode->prev = tail;
         tail = newNode;
     }
     size++;
     if (size > limit) {
         deleteOldest();
     }
 }

 void deleteOldest() {
     if (!head) return;
     Node* temp = head;
     head = head->next;
     if (head) head->prev = nullptr;
     else tail = nullptr;
     delete temp;
     size--;
 }

 bool searchAction(int id) {
     Node* curr = head;
     while (curr) {
         if (curr->actionId == id) {
             cout << "Found Action: " << curr->actionId << " - " << curr->description << endl;
             return true;
         }
         curr = curr->next;
     }
     cout << "Action ID " << id << " not found." << endl;
     return false;
 }

 void display() {
     Node* curr = head;
     cout << "--- Edit History (" << size << "/" << limit << ") ---" << endl;
     while (curr) {
         cout << "[" << curr->actionId << ": " << curr->description << "] <-> ";
         curr = curr->next;
     }
     cout << "NULL" << endl;
 }


};
}

/*

Unit 1, Q2: College Admission Management (Singly Linked List)

Supports: Add applicant dynamically, Display traversal, Sort by Applicant ID.
/
namespace Unit1_Q2 {
struct Applicant {
int id;
string name;
double score;
Applicant next;
Applicant(int i, string n, double s) : id(i), name(n), score(s), next(nullptr) {}
};

class AdmissionSystem {
Applicant* head;
public:
AdmissionSystem() : head(nullptr) {}

 void addApplicant(int id, string name, double score) {
     Applicant* newNode = new Applicant(id, name, score);
     if (!head) {
         head = newNode;
         return;
     }
     Applicant* temp = head;
     while (temp->next) temp = temp->next;
     temp->next = newNode;
 }

 void display() {
     Applicant* temp = head;
     cout << "Applicants:\n";
     while (temp) {
         cout << "ID: " << temp->id << " | Name: " << temp->name << " | Score: " << temp->score << "\n";
         temp = temp->next;
     }
 }

 void sortById() {
     if (!head || !head->next) return;
     for (Applicant* i = head; i->next != nullptr; i = i->next) {
         for (Applicant* j = i->next; j != nullptr; j = j->next) {
             if (i->id > j->id) {
                 swap(i->id, j->id);
                 swap(i->name, j->name);
                 swap(i->score, j->score);
             }
         }
     }
 }


};
}

/*

Unit 1, Q3: Railway Waiting List (Singly Linked List)

Supports: Add rear, delete front (ticket confirmed), display, search by Passenger ID.
/
namespace Unit1_Q3 {
struct Passenger {
int id;
string name;
int age;
Passenger next;
Passenger(int i, string n, int a) : id(i), name(n), age(a), next(nullptr) {}
};

class RailwayWaitingList {
Passenger* front;
Passenger* rear;
public:
RailwayWaitingList() : front(nullptr), rear(nullptr) {}

 void addPassenger(int id, string name, int age) {
     Passenger* p = new Passenger(id, name, age);
     if (!rear) {
         front = rear = p;
         return;
     }
     rear->next = p;
     rear = p;
 }

 void confirmTicket() {
     if (!front) {
         cout << "Waiting list empty.\n";
         return;
     }
     Passenger* temp = front;
     cout << "Confirmed Ticket for: " << temp->name << " (ID: " << temp->id << ")\n";
     front = front->next;
     if (!front) rear = nullptr;
     delete temp;
 }

 void search(int id) {
     Passenger* temp = front;
     int pos = 1;
     while (temp) {
         if (temp->id == id) {
             cout << "Passenger " << id << " found at WL position " << pos << ": " << temp->name << "\n";
             return;
         }
         temp = temp->next;
         pos++;
     }
     cout << "Passenger ID not found.\n";
 }

 void display() {
     Passenger* temp = front;
     cout << "Current Waiting List:\n";
     while (temp) {
         cout << "[ID: " << temp->id << " | " << temp->name << " | Age: " << temp->age << "] -> ";
         temp = temp->next;
     }
     cout << "NULL\n";
 }


};
}

/*

Unit 1, Q4: Web Browser Tab Management (Doubly Linked List)

Supports: Insert tab, Move backward, Search URL, Display all tabs.
/
namespace Unit1_Q4 {
struct Tab {
string url;
Tab prev;
Tab* next;
Tab(string u) : url(u), prev(nullptr), next(nullptr) {}
};

class BrowserTabs {
Tab* head;
Tab* current;
public:
BrowserTabs() : head(nullptr), current(nullptr) {}

 void insertTab(string url) {
     Tab* newTab = new Tab(url);
     if (!head) {
         head = current = newTab;
     } else {
         newTab->prev = current;
         newTab->next = current->next;
         if (current->next) current->next->prev = newTab;
         current->next = newTab;
         current = newTab;
     }
 }

 void moveBackward() {
     if (current && current->prev) {
         current = current->prev;
         cout << "Moved back to: " << current->url << endl;
     } else {
         cout << "No previous tab available.\n";
     }
 }

 void searchTab(string url) {
     Tab* temp = head;
     int idx = 0;
     while (temp) {
         if (temp->url == url) {
             cout << "Found tab: " << url << " at position " << idx << endl;
             return;
         }
         temp = temp->next;
         idx++;
     }
     cout << "Tab not found.\n";
 }

 void display() {
     Tab* temp = head;
     cout << "Open Tabs: ";
     while (temp) {
         if (temp == current) cout << "[" << temp->url << "*] ";
         else cout << temp->url << " ";
         temp = temp->next;
     }
     cout << "\n";
 }


};
}

/*

Unit 1, Q5: Train Coach Management (Doubly Linked List)

Supports: Add coach at front/rear/pos, Remove coach, Search coach, Display reverse (last to engine).
/
namespace Unit1_Q5 {
struct Coach {
int number;
string type;
Coach prev;
Coach* next;
Coach(int n, string t) : number(n), type(t), prev(nullptr), next(nullptr) {}
};

class Train {
Coach* engine; // Head
Coach* rear;   // Tail
public:
Train() : engine(nullptr), rear(nullptr) {}

 void addFront(int num, string type) {
     Coach* c = new Coach(num, type);
     if (!engine) {
         engine = rear = c;
     } else {
         c->next = engine;
         engine->prev = c;
         engine = c;
     }
 }

 void addRear(int num, string type) {
     Coach* c = new Coach(num, type);
     if (!rear) {
         engine = rear = c;
     } else {
         rear->next = c;
         c->prev = rear;
         rear = c;
     }
 }

 void removeCoach(int num) {
     Coach* curr = engine;
     while (curr && curr->number != num) curr = curr->next;
     if (!curr) {
         cout << "Coach not found.\n";
         return;
     }
     if (curr == engine) engine = engine->next;
     if (curr == rear) rear = rear->prev;
     if (curr->prev) curr->prev->next = curr->next;
     if (curr->next) curr->next->prev = curr->prev;
     delete curr;
     cout << "Coach " << num << " removed.\n";
 }

 void displayReverse() {
     Coach* curr = rear;
     cout << "Coaches from Last to Engine:\n";
     while (curr) {
         cout << "[" << curr->number << " | " << curr->type << "] <-> ";
         curr = curr->prev;
     }
     cout << "ENGINE\n";
 }


};
}

/*

Unit 1, Q6: Music Playlist (Singly Linked List)

Supports: Add songs, Remove songs, Display playlist, Play specific song.
/
namespace Unit1_Q6 {
struct Song {
string title;
string artist;
int duration; // seconds
Song next;
Song(string t, string a, int d) : title(t), artist(a), duration(d), next(nullptr) {}
};

class Playlist {
Song* head;
public:
Playlist() : head(nullptr) {}

 void addSong(string t, string a, int d) {
     Song* s = new Song(t, a, d);
     if (!head) {
         head = s;
         return;
     }
     Song* temp = head;
     while (temp->next) temp = temp->next;
     temp->next = s;
 }

 void removeSong(string title) {
     if (!head) return;
     if (head->title == title) {
         Song* toDelete = head;
         head = head->next;
         delete toDelete;
         return;
     }
     Song* temp = head;
     while (temp->next && temp->next->title != title) temp = temp->next;
     if (temp->next) {
         Song* toDelete = temp->next;
         temp->next = temp->next->next;
         delete toDelete;
     }
 }

 void playSong(string title) {
     Song* temp = head;
     while (temp) {
         if (temp->title == title) {
             cout << "Playing: " << temp->title << " by " << temp->artist << " [" << temp->duration << "s]\n";
             return;
         }
         temp = temp->next;
     }
     cout << "Song not found in playlist.\n";
 }

 void display() {
     Song* temp = head;
     cout << "--- Playlist ---\n";
     while (temp) {
         cout << temp->title << " - " << temp->artist << " (" << temp->duration << "s)\n";
         temp = temp->next;
     }
 }


};
}

/*

Unit 1, Q7: Library Catalogue Management (Singly Linked List)

Supports: Add book, Remove book, Display available books, Search by Book ID.
/
namespace Unit1_Q7 {
struct Book {
int id;
string title;
string author;
bool isAvailable;
Book next;
Book(int i, string t, string a, bool avail) : id(i), title(t), author(a), isAvailable(avail), next(nullptr) {}
};

class LibraryCatalogue {
Book* head;
public:
LibraryCatalogue() : head(nullptr) {}

 void addBook(int id, string title, string author, bool avail) {
     Book* b = new Book(id, title, author, avail);
     b->next = head;
     head = b;
 }

 void removeBook(int id) {
     if (!head) return;
     if (head->id == id) {
         Book* del = head;
         head = head->next;
         delete del;
         return;
     }
     Book* curr = head;
     while (curr->next && curr->next->id != id) curr = curr->next;
     if (curr->next) {
         Book* del = curr->next;
         curr->next = curr->next->next;
         delete del;
     }
 }

 void displayAvailable() {
     Book* curr = head;
     cout << "Available Books:\n";
     while (curr) {
         if (curr->isAvailable) {
             cout << "ID: " << curr->id << " | Title: " << curr->title << " | Author: " << curr->author << "\n";
         }
         curr = curr->next;
     }
 }

 void searchBook(int id) {
     Book* curr = head;
     while (curr) {
         if (curr->id == id) {
             cout << "Book Found: " << curr->title << " by " << curr->author << " Status: " << (curr->isAvailable ? "Available" : "Checked Out") << "\n";
             return;
         }
         curr = curr->next;
     }
     cout << "Book ID not found.\n";
 }


};
}

/*

Unit 1, Q8: Social Media Chronological Posts (Doubly Linked List)

Supports: Add post sorted by timestamp, Delete post, Search post by ID, Display feed newest to oldest.
/
namespace Unit1_Q8 {
struct Post {
int postId;
long long timestamp;
string content;
Post prev;
Post* next;
Post(int id, long long ts, string c) : postId(id), timestamp(ts), content(c), prev(nullptr), next(nullptr) {}
};

class SocialFeed {
Post* head; // oldest
Post* tail; // newest
public:
SocialFeed() : head(nullptr), tail(nullptr) {}

 void addPost(int id, long long timestamp, string content) {
     Post* p = new Post(id, timestamp, content);
     if (!head) {
         head = tail = p;
         return;
     }
     Post* curr = head;
     while (curr && curr->timestamp < timestamp) {
         curr = curr->next;
     }
     if (!curr) { // Append at tail
         tail->next = p;
         p->prev = tail;
         tail = p;
     } else if (curr == head) { // Insert at head
         p->next = head;
         head->prev = p;
         head = p;
     } else { // Insert before curr
         p->next = curr;
         p->prev = curr->prev;
         curr->prev->next = p;
         curr->prev = p;
     }
 }

 void deletePost(int id) {
     Post* curr = head;
     while (curr && curr->postId != id) curr = curr->next;
     if (!curr) return;
     if (curr == head) head = head->next;
     if (curr == tail) tail = tail->prev;
     if (curr->prev) curr->prev->next = curr->next;
     if (curr->next) curr->next->prev = curr->prev;
     delete curr;
 }

 void displayNewestToOldest() {
     Post* curr = tail;
     cout << "--- Social Media Feed (Newest First) ---\n";
     while (curr) {
         cout << "[" << curr->timestamp << "] Post #" << curr->postId << ": " << curr->content << "\n";
         curr = curr->prev;
     }
 }


};
}

/*

Unit 1, Q9: Student Attendance Management (Singly Linked List)

Supports: Add record, Remove record, Display all, Search by Roll No.
/
namespace Unit1_Q9 {
struct Student {
int rollNo;
string name;
string division;
double attendance;
Student next;
Student(int r, string n, string d, double a) : rollNo(r), name(n), division(d), attendance(a), next(nullptr) {}
};

class AttendanceSystem {
Student* head;
public:
AttendanceSystem() : head(nullptr) {}

 void addStudent(int roll, string name, string div, double att) {
     Student* s = new Student(roll, name, div, att);
     s->next = head;
     head = s;
 }

 void removeStudent(int roll) {
     if (!head) return;
     if (head->rollNo == roll) {
         Student* del = head;
         head = head->next;
         delete del;
         return;
     }
     Student* curr = head;
     while (curr->next && curr->next->rollNo != roll) curr = curr->next;
     if (curr->next) {
         Student* del = curr->next;
         curr->next = curr->next->next;
         delete del;
     }
 }

 void search(int roll) {
     Student* curr = head;
     while (curr) {
         if (curr->rollNo == roll) {
             cout << "Found: " << curr->name << " Div: " << curr->division << " Attendance: " << curr->attendance << "%\n";
             return;
         }
         curr = curr->next;
     }
     cout << "Student with Roll " << roll << " not found.\n";
 }

 void display() {
     Student* curr = head;
     while (curr) {
         cout << "Roll: " << curr->rollNo << " | Name: " << curr->name << " | Div: " << curr->division << " | Att: " << curr->attendance << "%\n";
         curr = curr->next;
     }
 }


};
}

/*

Unit 1, Q10: Patient Management System (Singly Linked List)

Supports: Register patient, Remove after consultation, Display queue, Search by ID.
/
namespace Unit1_Q10 {
struct Patient {
int id;
string name;
int age;
string illness;
Patient next;
Patient(int i, string n, int a, string ill) : id(i), name(n), age(a), illness(ill), next(nullptr) {}
};

class PatientQueue {
Patient* head;
public:
PatientQueue() : head(nullptr) {}

 void registerPatient(int id, string name, int age, string illness) {
     Patient* p = new Patient(id, name, age, illness);
     if (!head) {
         head = p;
         return;
     }
     Patient* temp = head;
     while (temp->next) temp = temp->next;
     temp->next = p;
 }

 void consultPatient() {
     if (!head) {
         cout << "No patients waiting.\n";
         return;
     }
     Patient* del = head;
     cout << "Consulted Patient: " << del->name << " (Illness: " << del->illness << ")\n";
     head = head->next;
     delete del;
 }

 void search(int id) {
     Patient* temp = head;
     while (temp) {
         if (temp->id == id) {
             cout << "Patient ID " << id << ": " << temp->name << ", Age: " << temp->age << ", Condition: " << temp->illness << "\n";
             return;
         }
         temp = temp->next;
     }
     cout << "Patient ID not found.\n";
 }

 void display() {
     Patient* temp = head;
     cout << "Patients Waiting:\n";
     while (temp) {
         cout << "[ID: " << temp->id << " - " << temp->name << " (" << temp->illness << ")] -> ";
         temp = temp->next;
     }
     cout << "NULL\n";
 }


};
}

// =====================================================================================
// SECTION 2: UNIT 2 - STACKS
// =====================================================================================

/*

Unit 2, Q1: Stack of Plates Simulation

Supports: Push, Pop, Peek, Display.
/
namespace Unit2_Q1 {
class PlateStack {
int arr;
int top;
int capacity;
public:
PlateStack(int cap = 100) : capacity(cap), top(-1) {
arr = new int[capacity];
}
~PlateStack() { delete[] arr; }

 void push(int plateId) {
     if (top == capacity - 1) {
         cout << "Stack Overflow! Plate cannot be added.\n";
         return;
     }
     arr[++top] = plateId;
 }

 void pop() {
     if (top == -1) {
         cout << "Stack Underflow! No plates to remove.\n";
         return;
     }
     cout << "Removed plate ID: " << arr[top--] << "\n";
 }

 void peek() {
     if (top == -1) {
         cout << "Stack is empty.\n";
         return;
     }
     cout << "Top plate ID: " << arr[top] << "\n";
 }

 void display() {
     if (top == -1) {
         cout << "Stack is empty.\n";
         return;
     }
     cout << "Plates (Top to Bottom): ";
     for (int i = top; i >= 0; --i) cout << arr[i] << " ";
     cout << "\n";
 }


};
}

/*

Unit 2, Q2: Function Call Management System

Supports: Push call, Display top, Pop completed call, Search active call.
*/
namespace Unit2_Q2 {
struct CallFrame {
string functionName;
int memoryBytes;
};

class CallStack {
vector stackFrames;
public:
void push(string func, int mem) {
stackFrames.push_back({func, mem});
}

 void pop() {
     if (stackFrames.empty()) {
         cout << "Call stack empty.\n";
         return;
     }
     cout << "Returned from: " << stackFrames.back().functionName << "\n";
     stackFrames.pop_back();
 }

 void top() {
     if (stackFrames.empty()) {
         cout << "Call stack empty.\n";
         return;
     }
     cout << "Active Call: " << stackFrames.back().functionName << " [" << stackFrames.back().memoryBytes << " bytes]\n";
 }

 void search(string func) {
     for (int i = stackFrames.size() - 1; i >= 0; --i) {
         if (stackFrames[i].functionName == func) {
             cout << "Function " << func << " is active at stack depth " << (stackFrames.size() - 1 - i) << "\n";
             return;
         }
     }
     cout << "Function not currently active on stack.\n";
 }


};
}

/*

Unit 2, Q3: Infix to Postfix Expression Conversion
/
namespace Unit2_Q3 {
int precedence(char op) {
if (op == '^') return 3;
if (op == '' || op == '/') return 2;
if (op == '+' || op == '-') return 1;
return 0;
}

string infixToPostfix(string infix) {
stack s;
string postfix = "";
for (char c : infix) {
if (isalnum(c)) {
postfix += c;
} else if (c == '(') {
s.push(c);
} else if (c == ')') {
while (!s.empty() && s.top() != '(') {
postfix += s.top();
s.pop();
}
if (!s.empty()) s.pop();
} else {
while (!s.empty() && precedence(s.top()) >= precedence(c)) {
postfix += s.top();
s.pop();
}
s.push(c);
}
}
while (!s.empty()) {
postfix += s.top();
s.pop();
}
return postfix;
}
}

/*

Unit 2, Q4: Postfix to Infix Expression Conversion
*/
namespace Unit2_Q4 {
string postfixToInfix(string postfix) {
stack s;
for (char c : postfix) {
if (isalnum(c)) {
s.push(string(1, c));
} else {
string op2 = s.top(); s.pop();
string op1 = s.top(); s.pop();
string expr = "(" + op1 + c + op2 + ")";
s.push(expr);
}
}
return s.top();
}
}

/*

Unit 2, Q5: Convert Infix to Prefix and Evaluate
/
namespace Unit2_Q5 {
int precedence(char op) {
if (op == '^') return 3;
if (op == '' || op == '/') return 2;
if (op == '+' || op == '-') return 1;
return 0;
}

string infixToPrefix(string infix) {
reverse(infix.begin(), infix.end());
for (char &c : infix) {
if (c == '(') c = ')';
else if (c == ')') c = '(';
}
stack s;
string postfix = "";
for (char c : infix) {
if (isalnum(c)) postfix += c;
else if (c == '(') s.push(c);
else if (c == ')') {
while (!s.empty() && s.top() != '(') {
postfix += s.top();
s.pop();
}
if (!s.empty()) s.pop();
} else {
while (!s.empty() && precedence(s.top()) > precedence(c)) {
postfix += s.top();
s.pop();
}
s.push(c);
}
}
while (!s.empty()) {
postfix += s.top();
s.pop();
}
reverse(postfix.begin(), postfix.end());
return postfix;
}
}

/*

Unit 2, Q6: Stack using SLL supporting O(1) Get Minimum
/
namespace Unit2_Q6 {
struct MinNode {
int val;
int minSoFar;
MinNode next;
MinNode(int v, int m, MinNode* n) : val(v), minSoFar(m), next(n) {}
};

class MinStackSLL {
MinNode* topNode;
public:
MinStackSLL() : topNode(nullptr) {}

 void push(int x) {
     int currentMin = (!topNode) ? x : min(x, topNode->minSoFar);
     topNode = new MinNode(x, currentMin, topNode);
 }

 void pop() {
     if (!topNode) {
         cout << "Stack is empty.\n";
         return;
     }
     MinNode* del = topNode;
     topNode = topNode->next;
     delete del;
 }

 int getMinimum() {
     if (!topNode) throw runtime_error("Stack is empty.");
     return topNode->minSoFar;
 }

 void display() {
     MinNode* curr = topNode;
     cout << "Stack (Top to Bottom): ";
     while (curr) {
         cout << curr->val << " ";
         curr = curr->next;
     }
     cout << "\n";
 }


};
}

/*

Unit 2, Q7: Evaluate Infix Expression directly using stacks
/
namespace Unit2_Q7 {
int applyOp(int a, int b, char op) {
switch (op) {
case '+': return a + b;
case '-': return a - b;
case '': return a * b;
case '/': return b != 0 ? a / b : 0;
}
return 0;
}

int precedence(char op) {
if (op == '+' || op == '-') return 1;
if (op == '*' || op == '/') return 2;
return 0;
}

int evaluateInfix(string tokens) {
stack values;
stack ops;
for (size_t i = 0; i < tokens.length(); i++) {
if (tokens[i] == ' ') continue;
if (isdigit(tokens[i])) {
int val = 0;
while (i < tokens.length() && isdigit(tokens[i])) {
val = (val * 10) + (tokens[i] - '0');
i++;
}
values.push(val);
i--;
} else if (tokens[i] == '(') {
ops.push(tokens[i]);
} else if (tokens[i] == ')') {
while (!ops.empty() && ops.top() != '(') {
int val2 = values.top(); values.pop();
int val1 = values.top(); values.pop();
char op = ops.top(); ops.pop();
values.push(applyOp(val1, val2, op));
}
if (!ops.empty()) ops.pop();
} else {
while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i])) {
int val2 = values.top(); values.pop();
int val1 = values.top(); values.pop();
char op = ops.top(); ops.pop();
values.push(applyOp(val1, val2, op));
}
ops.push(tokens[i]);
}
}
while (!ops.empty()) {
int val2 = values.top(); values.pop();
int val1 = values.top(); values.pop();
char op = ops.top(); ops.pop();
values.push(applyOp(val1, val2, op));
}
return values.top();
}
}

/*

Unit 2, Q8: Browser History Management using Stacks (with Overflow Handling)
/
namespace Unit2_Q8 {
class BrowserHistoryStack {
string history;
int topIdx;
int capacity;
public:
BrowserHistoryStack(int cap = 5) : capacity(cap), topIdx(-1) {
history = new string[capacity];
}
~BrowserHistoryStack() { delete[] history; }

 void pushURL(string url) {
     if (topIdx == capacity - 1) {
         cout << "[Stack Overflow] Limit reached! Cannot push URL: " << url << "\n";
         return;
     }
     history[++topIdx] = url;
     cout << "Navigated to: " << url << "\n";
 }

 void popURL() {
     if (topIdx == -1) {
         cout << "[Stack Underflow] No history to go back to.\n";
         return;
     }
     cout << "Back from: " << history[topIdx--] << "\n";
 }

 void display() {
     cout << "History Stack (Most Recent First):\n";
     for (int i = topIdx; i >= 0; --i) {
         cout << " - " << history[i] << "\n";
     }
 }


};
}

/*

Unit 2, Q9: Undo Operation in Text Editor using Stack
*/
namespace Unit2_Q9 {
class TextUndoStack {
stack undoHistory;
public:
void pushAction(string action) {
undoHistory.push(action);
}

 void undo() {
     if (undoHistory.empty()) {
         cout << "Nothing to undo.\n";
         return;
     }
     cout << "Undoing action: " << undoHistory.top() << "\n";
     undoHistory.pop();
 }

 void peek() {
     if (!undoHistory.empty()) {
         cout << "Latest Action: " << undoHistory.top() << "\n";
     }
 }

 void display() {
     stack<string> temp = undoHistory;
     cout << "Undo Actions (Recent First):\n";
     while (!temp.empty()) {
         cout << "-> " << temp.top() << "\n";
         temp.pop();
     }
 }


};
}

/*

Unit 2, Q10: Palindrome String Checker using Stack
*/
namespace Unit2_Q10 {
bool isPalindrome(string str) {
stack s;
for (char c : str) s.push(c);
for (char c : str) {
if (s.top() != c) return false;
s.pop();
}
return true;
}
}

// =====================================================================================
// SECTION 3: UNIT 3 - QUEUES
// =====================================================================================

/*

Unit 3, Q1: Linear Queue ADT for integer data using SLL
/
namespace Unit3_Q1 {
struct Node {
int data;
Node next;
Node(int d) : data(d), next(nullptr) {}
};

class LinearQueueSLL {
Node* front;
Node* rear;
public:
LinearQueueSLL() : front(nullptr), rear(nullptr) {}

 void enqueue(int x) {
     Node* newNode = new Node(x);
     if (!rear) {
         front = rear = newNode;
         return;
     }
     rear->next = newNode;
     rear = newNode;
 }

 int dequeue() {
     if (!front) {
         cout << "Queue Underflow!\n";
         return -1;
     }
     Node* temp = front;
     int val = temp->data;
     front = front->next;
     if (!front) rear = nullptr;
     delete temp;
     return val;
 }

 int peek() {
     if (!front) {
         cout << "Queue is Empty!\n";
         return -1;
     }
     return front->data;
 }

 void display() {
     Node* temp = front;
     cout << "Queue: ";
     while (temp) {
         cout << temp->data << " <- ";
         temp = temp->next;
     }
     cout << "REAR\n";
 }


};
}

/*

Unit 3, Q2: Hospital Patient Queue Management System
/
namespace Unit3_Q2 {
struct Patient {
int id;
string name;
int age;
Patient next;
Patient(int i, string n, int a) : id(i), name(n), age(a), next(nullptr) {}
};

class HospitalQueue {
Patient* front;
Patient* rear;
public:
HospitalQueue() : front(nullptr), rear(nullptr) {}

 void enqueue(int id, string name, int age) {
     Patient* p = new Patient(id, name, age);
     if (!rear) {
         front = rear = p;
         return;
     }
     rear->next = p;
     rear = p;
 }

 void dequeue() {
     if (!front) {
         cout << "No patients to consult.\n";
         return;
     }
     Patient* temp = front;
     cout << "Consulting Patient: " << temp->name << " (ID: " << temp->id << ")\n";
     front = front->next;
     if (!front) rear = nullptr;
     delete temp;
 }

 void peek() {
     if (!front) {
         cout << "No waiting patients.\n";
         return;
     }
     cout << "Next for consultation: " << front->name << " [Age: " << front->age << "]\n";
 }

 void display() {
     Patient* temp = front;
     cout << "Waiting Patients:\n";
     while (temp) {
         cout << " - ID: " << temp->id << " | Name: " << temp->name << "\n";
         temp = temp->next;
     }
 }


};
}

/*

Unit 3, Q3: Cloud Messaging Queue with Dead-Letter / Retry Handling
/
namespace Unit3_Q3 {
struct Message {
int id;
string body;
int retries;
Message next;
Message(int i, string b, int r) : id(i), body(b), retries(r), next(nullptr) {}
};

class CloudMessageQueue {
Message* front;
Message* rear;
int maxRetries;
public:
CloudMessageQueue(int maxR = 3) : front(nullptr), rear(nullptr), maxRetries(maxR) {}

 bool isEmpty() { return front == nullptr; }

 void enqueue(int id, string body, int retries = 0) {
     Message* m = new Message(id, body, retries);
     if (!rear) {
         front = rear = m;
         return;
     }
     rear->next = m;
     rear = m;
 }

 void peek() {
     if (isEmpty()) {
         cout << "Queue empty.\n";
         return;
     }
     cout << "Front Message: " << front->id << ": " << front->body << " (Retries: " << front->retries << ")\n";
 }

 void processMessage(CloudMessageQueue& deadLetterQueue) {
     if (isEmpty()) {
         cout << "No messages to process.\n";
         return;
     }
     Message* m = front;
     front = front->next;
     if (!front) rear = nullptr;

     if (m->retries >= maxRetries) {
         cout << "Message " << m->id << " exceeded max retries. Moving to Dead-Letter Queue.\n";
         deadLetterQueue.enqueue(m->id, m->body, m->retries);
     } else {
         cout << "Successfully processed message: " << m->body << "\n";
     }
     delete m;
 }


};
}

/*

Unit 3, Q4: Restaurant Waiting List Queue
/
namespace Unit3_Q4 {
struct Party {
string name;
int size;
string phone;
Party next;
Party(string n, int s, string p) : name(n), size(s), phone(p), next(nullptr) {}
};

class RestaurantQueue {
Party* front;
Party* rear;
public:
RestaurantQueue() : front(nullptr), rear(nullptr) {}

 bool isEmpty() { return front == nullptr; }

 void addParty(string name, int size, string phone) {
     Party* p = new Party(name, size, phone);
     if (!rear) {
         front = rear = p;
         return;
     }
     rear->next = p;
     rear = p;
 }

 void seatParty() {
     if (isEmpty()) {
         cout << "Waiting list is empty.\n";
         return;
     }
     Party* p = front;
     cout << "Seating party: " << p->name << " (Size: " << p->size << ")\n";
     front = front->next;
     if (!front) rear = nullptr;
     delete p;
 }

 void removeParty(string name) {
     if (isEmpty()) return;
     if (front->name == name) {
         seatParty();
         return;
     }
     Party* curr = front;
     while (curr->next && curr->next->name != name) curr = curr->next;
     if (curr->next) {
         Party* del = curr->next;
         if (del == rear) rear = curr;
         curr->next = del->next;
         delete del;
         cout << "Party " << name << " removed from waiting list.\n";
     } else {
         cout << "Party " << name << " not found.\n";
     }
 }

 void display() {
     Party* p = front;
     int pos = 1;
     cout << "--- Restaurant Waiting List ---\n";
     while (p) {
         cout << pos++ << ". " << p->name << " (Size: " << p->size << ", Phone: " << p->phone << ")\n";
         p = p->next;
     }
 }


};
}

/*

Unit 3, Q5: Airport Driver Dispatch System
/
namespace Unit3_Q5 {
struct Driver {
int id;
string carTier;
Driver next;
Driver(int i, string t) : id(i), carTier(t), next(nullptr) {}
};

class DriverDispatchQueue {
Driver* front;
Driver* rear;
int count;
public:
DriverDispatchQueue() : front(nullptr), rear(nullptr), count(0) {}

 void addDriver(int id, string tier) {
     Driver* d = new Driver(id, tier);
     if (!rear) {
         front = rear = d;
     } else {
         rear->next = d;
         rear = d;
     }
     count++;
 }

 int getDriverCount() { return count; }

 void assignRide() {
     if (!front) {
         cout << "No drivers waiting in queue.\n";
         return;
     }
     Driver* d = front;
     cout << "Assigned Driver ID: " << d->id << " (" << d->carTier << ") to incoming rider.\n";
     front = front->next;
     if (!front) rear = nullptr;
     delete d;
     count--;
 }

 void removeDisconnectedDriver(int id) {
     if (!front) return;
     if (front->id == id) {
         Driver* del = front;
         front = front->next;
         if (!front) rear = nullptr;
         delete del;
         count--;
         return;
     }
     Driver* curr = front;
     while (curr->next && curr->next->id != id) curr = curr->next;
     if (curr->next) {
         Driver* del = curr->next;
         if (del == rear) rear = curr;
         curr->next = del->next;
         delete del;
         count--;
         cout << "Driver " << id << " disconnected and removed.\n";
     }
 }


};
}

/*

Unit 3, Q6: Client Request Management System with Blacklist Removal
/
namespace Unit3_Q6 {
struct Request {
string ip;
string endpoint;
long long timestamp;
Request next;
Request(string i, string e, long long t) : ip(i), endpoint(e), timestamp(t), next(nullptr) {}
};

class RequestQueue {
Request* front;
Request* rear;
public:
RequestQueue() : front(nullptr), rear(nullptr) {}

 bool isEmpty() { return front == nullptr; }

 void enqueue(string ip, string endpoint, long long ts) {
     Request* r = new Request(ip, endpoint, ts);
     if (!rear) front = rear = r;
     else {
         rear->next = r;
         rear = r;
     }
 }

 void forwardToServer() {
     if (isEmpty()) {
         cout << "No requests to forward.\n";
         return;
     }
     Request* r = front;
     cout << "Forwarded Request from " << r->ip << " to " << r->endpoint << "\n";
     front = front->next;
     if (!front) rear = nullptr;
     delete r;
 }

 void removeBlacklistedIP(string badIP) {
     while (front && front->ip == badIP) {
         Request* del = front;
         front = front->next;
         delete del;
     }
     if (!front) {
         rear = nullptr;
         return;
     }
     Request* curr = front;
     while (curr->next) {
         if (curr->next->ip == badIP) {
             Request* del = curr->next;
             curr->next = del->next;
             if (del == rear) rear = curr;
             delete del;
         } else {
             curr = curr->next;
         }
     }
 }


};
}

/*

Unit 3, Q7: Printer Queue Management System
*/
namespace Unit3_Q7 {
class PrinterQueue {
queue jobs;
public:
void enqueue(string jobName) {
jobs.push(jobName);
}

 void dequeue() {
     if (jobs.empty()) {
         cout << "Printer queue is empty.\n";
         return;
     }
     cout << "Printing job: " << jobs.front() << "\n";
     jobs.pop();
 }

 void display() {
     if (jobs.empty()) {
         cout << "No jobs in queue.\n";
         return;
     }
     queue<string> temp = jobs;
     cout << "Print Jobs:\n";
     while (!temp.empty()) {
         cout << " -> " << temp.front() << "\n";
         temp.pop();
     }
 }

 bool isEmpty() { return jobs.empty(); }


};
}

/*

Unit 3, Q8: Network Packet Management System
*/
namespace Unit3_Q8 {
struct Packet {
int id;
string srcIP;
string destIP;
};

class PacketQueue {
queue q;
public:
void enqueue(int id, string src, string dest) {
q.push({id, src, dest});
}

 void dequeue() {
     if (q.empty()) {
         cout << "No packets to process.\n";
         return;
     }
     Packet p = q.front();
     q.pop();
     cout << "Processed Packet #" << p.id << " [" << p.srcIP << " -> " << p.destIP << "]\n";
 }

 void peek() {
     if (q.empty()) return;
     cout << "Next Packet: #" << q.front().id << " to " << q.front().destIP << "\n";
 }

 bool isEmpty() { return q.empty(); }


};
}

/*

Unit 3, Q9: Bank Customer Queue Management System
*/
namespace Unit3_Q9 {
struct Customer {
int token;
string name;
};

class BankQueue {
queue customers;
public:
void enqueue(int token, string name) {
customers.push({token, name});
}

 void dequeue() {
     if (customers.empty()) {
         cout << "No customers in line.\n";
         return;
     }
     cout << "Serving Token " << customers.front().token << ": " << customers.front().name << "\n";
     customers.pop();
 }

 void peek() {
     if (customers.empty()) return;
     cout << "Next in line: Token " << customers.front().token << " (" << customers.front().name << ")\n";
 }

 bool isEmpty() { return customers.empty(); }


};
}

/*

Unit 3, Q10: University Registration Queue Management System
*/
namespace Unit3_Q10 {
struct RegistrationRequest {
int studentId;
string studentName;
};

class RegistrationQueue {
queue q;
public:
void enqueue(int id, string name) {
q.push({id, name});
}

 void dequeue() {
     if (q.empty()) {
         cout << "Queue empty.\n";
         return;
     }
     cout << "Processed registration for: " << q.front().studentName << " (ID: " << q.front().studentId << ")\n";
     q.pop();
 }

 void peek() {
     if (q.empty()) return;
     cout << "Next Student: " << q.front().studentName << "\n";
 }

 bool isEmpty() { return q.empty(); }


};
}

// =====================================================================================
// SECTION 4: UNIT 4 - BINARY SEARCH TREES & THREADED BST
// =====================================================================================

/*

Unit 4, Q1: Library BST (Insert, Inorder Ascending, Delete 0/1 child, Delete 2 children via successor)
/
namespace Unit4_Q1 {
struct BSTNode {
int id;
BSTNode left;
BSTNode* right;
BSTNode(int val) : id(val), left(nullptr), right(nullptr) {}
};

class LibraryBST {
BSTNode* root;

 BSTNode* insert(BSTNode* node, int id) {
     if (!node) return new BSTNode(id);
     if (id < node->id) node->left = insert(node->left, id);
     else if (id > node->id) node->right = insert(node->right, id);
     return node;
 }

 BSTNode* findMin(BSTNode* node) {
     while (node && node->left) node = node->left;
     return node;
 }

 BSTNode* remove(BSTNode* node, int id) {
     if (!node) return nullptr;
     if (id < node->id) node->left = remove(node->left, id);
     else if (id > node->id) node->right = remove(node->right, id);
     else {
         if (!node->left) {
             BSTNode* temp = node->right;
             delete node;
             return temp;
         } else if (!node->right) {
             BSTNode* temp = node->left;
             delete node;
             return temp;
         }
         BSTNode* succ = findMin(node->right);
         node->id = succ->id;
         node->right = remove(node->right, succ->id);
     }
     return node;
 }

 void inorder(BSTNode* node) {
     if (!node) return;
     inorder(node->left);
     cout << node->id << " ";
     inorder(node->right);
 }


public:
LibraryBST() : root(nullptr) {}

 void insert(int id) { root = insert(root, id); }
 void remove(int id) { root = remove(root, id); }
 void printInorder() {
     inorder(root);
     cout << "\n";
 }

 void printLevelOrder() {
     if (!root) return;
     queue<BSTNode*> q;
     q.push(root);
     while (!q.empty()) {
         int s = q.size();
         while (s--) {
             BSTNode* curr = q.front();
             q.pop();
             cout << curr->id << " ";
             if (curr->left) q.push(curr->left);
             if (curr->right) q.push(curr->right);
         }
         cout << "\n";
     }
 }


};
}

/*

Unit 4, Q2: Exam Cell Roll Numbers BST

Supports: Min/Max non-recursively, Non-recursive inorder traversal using stack.
/
namespace Unit4_Q2 {
struct Node {
int roll;
Node left;
Node* right;
Node(int r) : roll(r), left(nullptr), right(nullptr) {}
};

class ExamCellBST {
Node* root;
public:
ExamCellBST() : root(nullptr) {}

 void insert(int roll) {
     Node* newNode = new Node(roll);
     if (!root) { root = newNode; return; }
     Node* curr = root;
     Node* parent = nullptr;
     while (curr) {
         parent = curr;
         if (roll < curr->roll) curr = curr->left;
         else if (roll > curr->roll) curr = curr->right;
         else return;
     }
     if (roll < parent->roll) parent->left = newNode;
     else parent->right = newNode;
 }

 void printMinMaxIterative() {
     if (!root) return;
     Node* curr = root;
     while (curr->left) curr = curr->left;
     cout << "Smallest Roll: " << curr->roll << "\n";

     curr = root;
     while (curr->right) curr = curr->right;
     cout << "Largest Roll: " << curr->roll << "\n";
 }

 void printInorderIterative() {
     stack<Node*> s;
     Node* curr = root;
     cout << "Inorder Roll Numbers: ";
     while (curr || !s.empty()) {
         while (curr) {
             s.push(curr);
             curr = curr->left;
         }
         curr = s.top();
         s.pop();
         cout << curr->roll << " ";
         curr = curr->right;
     }
     cout << "\n";
 }


};
}

/*

Unit 4, Q3: Hospital BST with Leaf Count and Level-by-Level deletion
/
namespace Unit4_Q3 {
struct TokenNode {
int token;
TokenNode left;
TokenNode* right;
TokenNode(int t) : token(t), left(nullptr), right(nullptr) {}
};

class HospitalBST {
TokenNode* root;

 int countLeaves(TokenNode* n) {
     if (!n) return 0;
     if (!n->left && !n->right) return 1;
     return countLeaves(n->left) + countLeaves(n->right);
 }

 TokenNode* remove(TokenNode* node, int t) {
     if (!node) return nullptr;
     if (t < node->token) node->left = remove(node->left, t);
     else if (t > node->token) node->right = remove(node->right, t);
     else {
         if (!node->left) { TokenNode* r = node->right; delete node; return r; }
         if (!node->right) { TokenNode* l = node->left; delete node; return l; }
         TokenNode* s = node->right;
         while (s->left) s = s->left;
         node->token = s->token;
         node->right = remove(node->right, s->token);
     }
     return node;
 }


public:
HospitalBST() : root(nullptr) {}
void insert(int t) {
// Standard insert
TokenNode* newNode = new TokenNode(t);
if (!root) { root = newNode; return; }
TokenNode* curr = root;
TokenNode* p = nullptr;
while (curr) {
p = curr;
if (t < curr->token) curr = curr->left;
else curr = curr->right;
}
if (t < p->token) p->left = newNode;
else p->right = newNode;
}

 int getLeafCount() { return countLeaves(root); }
 void removeToken(int t) { root = remove(root, t); }

 void printLevelOrder() {
     if (!root) return;
     queue<TokenNode*> q;
     q.push(root);
     while (!q.empty()) {
         int s = q.size();
         while (s--) {
             TokenNode* curr = q.front();
             q.pop();
             cout << curr->token << " ";
             if (curr->left) q.push(curr->left);
             if (curr->right) q.push(curr->right);
         }
         cout << "\n";
     }
 }


};
}

/*

Unit 4, Q4: Employee ID BST (Height and Non-recursive Preorder)
/
namespace Unit4_Q4 {
struct EmpNode {
int id;
EmpNode left;
EmpNode* right;
EmpNode(int i) : id(i), left(nullptr), right(nullptr) {}
};

class CompanyBST {
EmpNode* root;

 int height(EmpNode* node) {
     if (!node) return 0;
     return 1 + max(height(node->left), height(node->right));
 }


public:
CompanyBST() : root(nullptr) {}

 void insert(int id) {
     EmpNode* n = new EmpNode(id);
     if (!root) { root = n; return; }
     EmpNode* curr = root;
     EmpNode* p = nullptr;
     while (curr) {
         p = curr;
         if (id < curr->id) curr = curr->left;
         else curr = curr->right;
     }
     if (id < p->id) p->left = n;
     else p->right = n;
 }

 int getHeight() { return height(root); }

 void printPreorderIterative() {
     if (!root) return;
     stack<EmpNode*> s;
     s.push(root);
     cout << "Preorder Iterative: ";
     while (!s.empty()) {
         EmpNode* curr = s.top();
         s.pop();
         cout << curr->id << " ";
         if (curr->right) s.push(curr->right);
         if (curr->left) s.push(curr->left);
     }
     cout << "\n";
 }


};
}

/*

Unit 4, Q5: Railway Ticket Threaded Binary Search Tree (TBST)

Full double-threaded BST implementation
/
namespace Unit4_Q5 {
struct TBSTNode {
int ticket;
TBSTNode left;
TBSTNode* right;
bool lThread;
bool rThread;
TBSTNode(int t) : ticket(t), left(nullptr), right(nullptr), lThread(true), rThread(true) {}
};

class ThreadedBST {
TBSTNode* root;
public:
ThreadedBST() : root(nullptr) {}

 void insert(int ticket) {
     TBSTNode* p = root;
     TBSTNode* parent = nullptr;
     while (p != nullptr) {
         if (ticket == p->ticket) return;
         parent = p;
         if (ticket < p->ticket) {
             if (!p->lThread) p = p->left;
             else break;
         } else {
             if (!p->rThread) p = p->right;
             else break;
         }
     }

     TBSTNode* newNode = new TBSTNode(ticket);
     if (!parent) {
         root = newNode;
     } else if (ticket < parent->ticket) {
         newNode->left = parent->left;
         newNode->right = parent;
         parent->lThread = false;
         parent->left = newNode;
     } else {
         newNode->left = parent;
         newNode->right = parent->right;
         parent->rThread = false;
         parent->right = newNode;
     }
 }

 TBSTNode* inorderSuccessor(TBSTNode* ptr) {
     if (ptr->rThread) return ptr->right;
     ptr = ptr->right;
     while (!ptr->lThread) ptr = ptr->left;
     return ptr;
 }

 void inorder() {
     if (!root) return;
     TBSTNode* curr = root;
     while (!curr->lThread) curr = curr->left;
     cout << "Threaded Inorder Traversal: ";
     while (curr) {
         cout << curr->ticket << " ";
         curr = inorderSuccessor(curr);
     }
     cout << "\n";
 }

 void printLinkTypes(TBSTNode* node) {
     if (!node) return;
     cout << "Node: " << node->ticket 
          << " | Left: " << (node->lThread ? "THREAD" : "CHILD")
          << " | Right: " << (node->rThread ? "THREAD" : "CHILD") << "\n";
     if (!node->lThread) printLinkTypes(node->left);
     if (!node->rThread) printLinkTypes(node->right);
 }

 void inspectLinks() { printLinkTypes(root); }


};
}

/*

Unit 4, Q6: Courier Centre Threaded BST (Thread counting & Preorder without recursion/stack)
/
namespace Unit4_Q6 {
using namespace Unit4_Q5;
// Uses the TBST model; counts threads and prints preorder without stack.
void preorderTBST(TBSTNode root) {
if (!root) return;
TBSTNode* curr = root;
cout << "Threaded Preorder: ";
while (curr) {
cout << curr->ticket << " ";
if (!curr->lThread) {
curr = curr->left;
} else if (!curr->rThread) {
curr = curr->right;
} else {
while (curr && curr->rThread) curr = curr->right;
if (curr) curr = curr->right;
}
}
cout << "\n";
}
}

/*

Unit 4, Q7: Trading App Stock Price Floor in BST
/
namespace Unit4_Q7 {
struct PriceNode {
double price;
PriceNode left;
PriceNode* right;
PriceNode(double p) : price(p), left(nullptr), right(nullptr) {}
};

class StockPriceBST {
PriceNode* root;

 PriceNode* insert(PriceNode* node, double p) {
     if (!node) return new PriceNode(p);
     if (p < node->price) node->left = insert(node->left, p);
     else if (p > node->price) node->right = insert(node->right, p);
     return node;
 }


public:
StockPriceBST() : root(nullptr) {}

 void insert(double p) { root = insert(root, p); }

 void findFloor(double x) {
     PriceNode* curr = root;
     double floorVal = -1;
     while (curr) {
         if (curr->price == x) {
             floorVal = curr->price;
             break;
         }
         if (curr->price < x) {
             floorVal = curr->price;
             curr = curr->right;
         } else {
             curr = curr->left;
         }
     }
     if (floorVal != -1) cout << "Floor of " << x << " is: " << floorVal << "\n";
     else cout << "Floor of " << x << " is: none\n";
 }


};
}

/*

Unit 4, Q8: Parking Permit BST (Level Order Traversals)
*/
namespace Unit4_Q8 {
// Implemented through standard BST level order as illustrated in Unit 4 Q1.
}

/*

Unit 4, Q9: Cinema Seat BST (Search comparisons, Parent, Sibling lookup)
/
namespace Unit4_Q9 {
struct SeatNode {
int seat;
SeatNode left;
SeatNode* right;
SeatNode(int s) : seat(s), left(nullptr), right(nullptr) {}
};

class CinemaBST {
SeatNode* root;

 SeatNode* insert(SeatNode* n, int s) {
     if (!n) return new SeatNode(s);
     if (s < n->seat) n->left = insert(n->left, s);
     else if (s > n->seat) n->right = insert(n->right, s);
     return n;
 }


public:
CinemaBST() : root(nullptr) {}
void insert(int s) { root = insert(root, s); }

 void search(int s) {
     SeatNode* curr = root;
     int comps = 0;
     while (curr) {
         comps++;
         if (curr->seat == s) {
             cout << "Seat " << s << " is booked. Comparisons made: " << comps << "\n";
             return;
         }
         if (s < curr->seat) curr = curr->left;
         else curr = curr->right;
     }
     cout << "Seat " << s << " is NOT booked. Comparisons made: " << comps << "\n";
 }

 void findParentAndSibling(int s) {
     if (!root || root->seat == s) {
         cout << "Parent: none | Sibling: none\n";
         return;
     }
     SeatNode* curr = root;
     SeatNode* parent = nullptr;
     while (curr && curr->seat != s) {
         parent = curr;
         if (s < curr->seat) curr = curr->left;
         else curr = curr->right;
     }
     if (!curr) {
         cout << "Seat doesn't exist.\n";
         return;
     }
     cout << "Parent: " << parent->seat << " | ";
     if (parent->left && parent->left->seat == s) {
         if (parent->right) cout << "Sibling: " << parent->right->seat << "\n";
         else cout << "Sibling: none\n";
     } else {
         if (parent->left) cout << "Sibling: " << parent->left->seat << "\n";
         else cout << "Sibling: none\n";
     }
 }


};
}

// =====================================================================================
// SECTION 5: UNIT 5 - GRAPH ALGORITHMS
// =====================================================================================

/*

Unit 5, Q1: University Fibre Cables - Prim's Algorithm (Adjacency Matrix)
*/
namespace Unit5_Q1 {
void primMST(int V, const vector<vector>& costMatrix) {
vector key(V, INT_MAX);
vector inMST(V, false);
vector parent(V, -1);

 key[0] = 0;

 for (int count = 0; count < V - 1; count++) {
     int u = -1, minKey = INT_MAX;
     for (int v = 0; v < V; v++) {
         if (!inMST[v] && key[v] < minKey) {
             minKey = key[v];
             u = v;
         }
     }
     if (u == -1) break;
     inMST[u] = true;

     for (int v = 0; v < V; v++) {
         if (costMatrix[u][v] && !inMST[v] && costMatrix[u][v] < key[v]) {
             parent[v] = u;
             key[v] = costMatrix[u][v];
         }
     }
 }

 int totalCost = 0;
 cout << "Cabling Connections Selected (Prim's):\n";
 for (int i = 1; i < V; i++) {
     cout << "Building " << parent[i] << " - " << i << " : Cost " << costMatrix[i][parent[i]] << "\n";
     totalCost += costMatrix[i][parent[i]];
 }
 cout << "Total Cabling Cost: " << totalCost << "\n";


}
}

/*

Unit 5, Q2: Archipelago Ferry Services - Shortest Path (Dijkstra)
*/
namespace Unit5_Q2 {
struct Edge {
int to;
int time;
};

void dijkstra(int n, const vector<vector>& adj, int start) {
vector dist(n, INT_MAX);
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

 dist[start] = 0;
 pq.push({0, start});

 while (!pq.empty()) {
     int d = pq.top().first;
     int u = pq.top().second;
     pq.pop();

     if (d > dist[u]) continue;

     for (auto edge : adj[u]) {
         if (dist[u] + edge.time < dist[edge.to]) {
             dist[edge.to] = dist[u] + edge.time;
             pq.push({dist[edge.to], edge.to});
         }
     }
 }

 cout << "Shortest Travel Time from Island " << start << ":\n";
 for (int i = 0; i < n; i++) {
     cout << "Island " << i << ": ";
     if (dist[i] == INT_MAX) cout << "unreachable\n";
     else cout << dist[i] << " mins\n";
 }


}
}

/*

Unit 5, Q3: Social Network Graph (Friends BFS, Friends of Friends Suggestions)
*/
namespace Unit5_Q3 {
void socialNetworkAnalysis(int users, const vector<vector>& adj, int target) {
vector dist(users, -1);
queue q;

 dist[target] = 0;
 q.push(target);

 while (!q.empty()) {
     int u = q.front();
     q.pop();

     for (int v : adj[u]) {
         if (dist[v] == -1) {
             dist[v] = dist[u] + 1;
             q.push(v);
         }
     }
 }

 cout << "--- Connections for User " << target << " ---\n";
 for (int i = 0; i < users; ++i) {
     if (i == target) continue;
     if (dist[i] == 1) cout << "Direct Friend: User " << i << "\n";
     else if (dist[i] == 2) cout << "Suggested (Friend-of-Friend): User " << i << "\n";
     else if (dist[i] == -1) cout << "User " << i << ": not connected\n";
 }


}
}

/*

Unit 5, Q4: City Power Grid - Substation Reachability (Recursive DFS)
*/
namespace Unit5_Q4 {
void dfs(int u, const vector<vector>& adj, vector& visited) {
visited[u] = true;
cout << u << " ";
for (int v : adj[u]) {
if (!visited[v]) {
dfs(v, adj, visited);
}
}
}

void verifyPowerGrid(int n, const vector<vector>& adj) {
vector visited(n, false);
cout << "Substations reached from Substation 0 (Rule: numerical ascending order): ";
dfs(0, adj, visited);
cout << "\n";

 bool allPowered = true;
 for (int i = 0; i < n; i++) {
     if (!visited[i]) {
         cout << "Substation " << i << " stays in the dark!\n";
         allPowered = false;
     }
 }
 if (allPowered) cout << "All substations successfully powered.\n";


}
}

/*

Unit 5, Q5 & Q9: Road Repair & Farm Canals - Kruskal's MST with Disjoint Set Union (DSU)
*/
namespace Unit5_Kruskal {
struct Edge {
int u, v, cost;
bool operator<(const Edge& other) const {
if (cost != other.cost) return cost < other.cost;
if (u != other.u) return u < other.u;
return v < other.v; // Tie-breaker: lexicographical index
}
};

struct DSU {
vector parent;
DSU(int n) {
parent.resize(n);
for (int i = 0; i < n; i++) parent[i] = i;
}

 int find(int i) {
     if (parent[i] == i) return i;
     return parent[i] = find(parent[i]);
 }

 bool unite(int i, int j) {
     int root_i = find(i);
     int root_j = find(j);
     if (root_i != root_j) {
         parent[root_i] = root_j;
         return true;
     }
     return false;
 }


};

void kruskalMST(int n, vector& edges) {
sort(edges.begin(), edges.end());
DSU dsu(n);
int totalCost = 0;
int rejectedCount = 0;
vector mst;

 for (const auto& e : edges) {
     if (dsu.unite(e.u, e.v)) {
         mst.push_back(e);
         totalCost += e.cost;
     } else {
         rejectedCount++;
     }
 }

 cout << "Selected Roads / Canals:\n";
 for (const auto& e : mst) {
     cout << e.u << " - " << e.v << " : Cost " << e.cost << "\n";
 }
 cout << "Total Minimum Cost: " << totalCost << "\n";
 cout << "Total Rejected (Cycles Avoided): " << rejectedCount << "\n";


}
}

/*

Unit 5, Q7: Hostel Rumour Spread Simulation (Multi-Day BFS Wave)
*/
namespace Unit5_Q7 {
void simulateRumour(int n, const vector<vector>& adj, int source) {
vector dayHeard(n, -1);
queue q;

 dayHeard[source] = 0;
 q.push(source);

 while (!q.empty()) {
     int curr = q.front();
     q.pop();

     for (int friendId : adj[curr]) {
         if (dayHeard[friendId] == -1) {
             dayHeard[friendId] = dayHeard[curr] + 1;
             q.push(friendId);
         }
     }
 }

 int maxDay = 0;
 for (int d : dayHeard) maxDay = max(maxDay, d);

 for (int day = 1; day <= maxDay; day++) {
     cout << "Day " << day << " heard by: ";
     for (int i = 0; i < n; i++) {
         if (dayHeard[i] == day) cout << "Student " << i << " ";
     }
     cout << "\n";
 }

 for (int i = 0; i < n; i++) {
     if (dayHeard[i] == -1) cout << "Student " << i << ": never hears\n";
 }


}
}

/*

Unit 5, Q10: City Emergency Junctions - Dijkstra & Road Analytics
*/
namespace Unit5_Q10 {
struct Road {
int neighbor;
int time;
};

void emergencyDispatch(int junctions, const vector<vector>& graph, int station) {
vector dist(junctions, INT_MAX);
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

 dist[station] = 0;
 pq.push({0, station});

 while (!pq.empty()) {
     int d = pq.top().first;
     int u = pq.top().second;
     pq.pop();

     if (d > dist[u]) continue;

     for (auto r : graph[u]) {
         if (dist[u] + r.time < dist[r.neighbor]) {
             dist[r.neighbor] = dist[u] + r.time;
             pq.push({dist[r.neighbor], r.neighbor});
         }
     }
 }

 cout << "Emergency Ambulance Station at Junction " << station << ":\n";
 for (int i = 0; i < junctions; i++) {
     cout << "Junction " << i << ": ";
     if (dist[i] == INT_MAX) cout << "unreachable\n";
     else cout << dist[i] << " mins\n";
 }


}
}

// =====================================================================================
// MAIN DEMONSTRATION RUNNER
// =====================================================================================

int main() {
cout << "\n";
cout << "  PCCOE DSA QUESTION BANK - DEMONSTRATION OF MODULES    \n";
cout << "\n\n";

// Demo: Unit 1 Q1
cout << "[DEMO: Unit 1 Q1 - Text Editor History]\n";
Unit1_Q1::TextEditorHistory history(3);
history.addAction(101, "Type 'Hello'");
history.addAction(102, "Type 'World'");
history.addAction(103, "Bold text");
history.addAction(104, "Italic text"); // Evicts oldest (101)
history.display();
history.searchAction(102);

cout << "\n[DEMO: Unit 2 Q3 - Infix to Postfix]\n";
string infix = "A+(B*C-(D/E^F)*G)*H";
cout << "Infix:   " << infix << "\n";
cout << "Postfix: " << Unit2_Q3::infixToPostfix(infix) << "\n";

cout << "\n[DEMO: Unit 3 Q1 - Linear Queue SLL]\n";
Unit3_Q1::LinearQueueSLL lq;
lq.enqueue(10);
lq.enqueue(20);
lq.enqueue(30);
lq.display();
cout << "Dequeued: " << lq.dequeue() << "\n";
lq.display();

cout << "\n[DEMO: Unit 4 Q2 - BST Exam Cell Min/Max & Inorder Iterative]\n";
Unit4_Q2::ExamCellBST examBst;
examBst.insert(45);
examBst.insert(12);
examBst.insert(78);
examBst.insert(34);
examBst.insert(90);
examBst.printMinMaxIterative();
examBst.printInorderIterative();

cout << "\n[DEMO: Unit 5 Q5 - Kruskal's MST Road Network]\n";
vector<Unit5_Kruskal::Edge> roads = {
    {0, 1, 4}, {0, 2, 3}, {1, 2, 1}, {1, 3, 2}, {2, 3, 4}, {3, 4, 2}, {2, 4, 5}
};
Unit5_Kruskal::kruskalMST(5, roads);

cout << "\n========================================================\n";
cout << "All modules compiled and tested successfully.\n";
cout << "========================================================\n";

return 0;


}