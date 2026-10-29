INFIX 
#include <iostream>
#include <string>

using namespace std;

// 1. Character Stack
class Node {
public:
    char data;
    Node* next;
    Node(char c) { 
        data = c; 
        next = NULL; 
    }
};

class Stack {
private:
    Node* top;

public:
    Stack() { 
        top = NULL; 
    }

    void push(char c) {
        Node* n = new Node(c);
        n->next = top;
        top = n;
    }

    char pop() {
        if (!top) return '\0';
        Node* t = top;
        char c = t->data;
        top = top->next;
        delete t;
        return c;
    }

    char peek() { 
        return top ? top->data : '\0'; 
    }

    bool isEmpty() { 
        return top == NULL; 
    }
};

// 2. Integer Stack
class IntNode {
public:
    int data;
    IntNode* next;
    IntNode(int d) { 
        data = d; 
        next = NULL; 
    }
};

class IntStack {
private:
    IntNode* top;

public:
    IntStack() { 
        top = NULL; 
    }

    void push(int x) {
        IntNode* n = new IntNode(x);
        n->next = top;
        top = n;
    }

    int pop() {
        if (!top) return 0;
        IntNode* t = top;
        int val = t->data;
        top = top->next;
        delete t;
        return val;
    }

    bool isEmpty() { 
        return top == NULL; 
    }
};

// 3. Operation Class
class Operation {
public:
    int prec(char c) {
        if (c == '^') return 3;
        if (c == '*' || c == '/') return 2;
        if (c == '+' || c == '-') return 1;
        return -1;
    }

    int power(int base, int exp) {
        int res = 1;
        for (int i = 0; i < exp; i++) res *= base;
        return res;
    }

    string in_to_post(string s) {
        Stack st;
        string result = "";
        for (int i = 0; i < (int)s.length(); i++) {
            char c = s[i];
            if (c == ' ') continue;

            // Direct inline alphanumeric check
            if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                result += c;
            } else if (c == '(') {
                st.push(c);
            } else if (c == ')') {
                while (!st.isEmpty() && st.peek() != '(')
                 result += st.pop();
                st.pop();     // remove '('
            } else {
                while (!st.isEmpty() &&   ((prec(st.peek()) > prec(c)) || (prec(st.peek()) == prec(c) && c != '^'))) 
{
  result += st.pop();
                }
                st.push(c);
            }
        }
        while (!st.isEmpty()) result += st.pop();
        return result;
    }

    int evaluatePostfix(string post) {
        IntStack st;
        for (int i = 0; i < (int)post.length(); i++) {
            char c = post[i];

            // Direct inline digit check
            if (c >= '0' && c <= '9') {
                st.push(c - '0');
            } else {
                int val2 = st.pop();
                int val1 = st.pop();
                switch (c) {
                    case '+': st.push(val1 + val2); break;
                    case '-': st.push(val1 - val2); break;
                    case '*': st.push(val1 * val2); break;
                    case '/': st.push(val2 != 0 ? val1 / val2 : 0); break;
                    case '^': st.push(power(val1, val2)); break;
                }
            }
        }
        return st.pop();
    }

    string in_to_pre(string s) {
        string rev = "";
        for (int i = (int)s.length() - 1; i >= 0; i--) {
            if (s[i] == '(') rev += ')';
            else if (s[i] == ')') rev += '(';
            else rev += s[i];
        }

        Stack st;
        string post = "";
        for (int i = 0; i < (int)rev.length(); i++) {
            char c = rev[i];
            if (c == ' ') continue;

            // Direct inline alphanumeric check
            if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                post += c;
            } else if (c == '(') {
                st.push(c);
            } else if (c == ')') {
                while (!st.isEmpty() && st.peek() != '(') post += st.pop();
                st.pop();
            } else {
                while (!st.isEmpty() && 
                      ((prec(st.peek()) > prec(c)) || 
                       (prec(st.peek()) == prec(c) && c == '^'))) {
                    post += st.pop();
                }
                st.push(c);
            }
        }
        while (!st.isEmpty()) post += st.pop();

        string prefix = "";
        for (int i = (int)post.length() - 1; i >= 0; i--) prefix += post[i];
        return prefix;
    }
};

int main() {
    Operation op;
    string expr;

    cout << "Enter Infix Expression: ";
    cin >> expr;

    string post = op.in_to_post(expr);
    string pre = op.in_to_pre(expr);

    cout << "\nPostfix Expression: " << post << endl;
    cout << "Prefix Expression:  " << pre << endl;
    cout << "Evaluation Result:  " << op.evaluatePostfix(post) << endl;

    return 0;
}
