#include <iostream>
using namespace std;


// Custom Character Stack to avoid using the built-in <stack> library
class CharStack {
private:
    int top;
    int capacity;
    char* arr;

public:
    CharStack(int cap);
    ~CharStack();
    void push(char c);
    char pop();
    char peek();
    bool isEmpty();
};

int getPrecedence(char op);
char* infixToPostfix(const char* exp);

int main() {
    cout << "--- Testing Task 3: Infix to Postfix ---\n\n";
    
    // The test case provided in the assignment
    const char* infix = "a+b*(c^d-e)^(f+g*h)-i";
    
    char* postfix = infixToPostfix(infix);
    
    cout << "Input Infix:   " << infix << "\n";
    cout << "Output Postfix: " << postfix << "\n";
    
    delete[] postfix; 

    return 0;
}

=

// --- CharStack Method Implementations ---

CharStack::CharStack(int cap) {
    capacity = cap;
    arr = new char[cap];
    top = -1;
}

CharStack::~CharStack() {
    delete[] arr;
}

void CharStack::push(char c) {
    if (top < capacity - 1) {
        arr[++top] = c;
    }
}

char CharStack::pop() {
    if (top == -1) return '\0';
    return arr[top--];
}

char CharStack::peek() {
    if (top == -1) return '\0';
    return arr[top];
}

bool CharStack::isEmpty() {
    return top == -1;
}


/*
 * Task: Helper function to determine the precedence level of mathematical operators.
 * Input Parameters: 
 * - char op: The operator character (+, -, *, /, ^).
 * Returns: An integer representing precedence priority. Higher number = higher priority.
 */
int getPrecedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return -1;
}

/*
 * Task: Converts an Infix expression string into a Postfix expression string using a stack.
 * Input Parameters: 
 * - const char* exp: A constant character array representing the Infix expression.
 * Returns: A dynamically allocated char array containing the Postfix expression.
 */
char* infixToPostfix(const char* exp) {
    // 1. Calculate Length to avoid using strlen() from <cstring>
    int len = 0;
    while (exp[len] != '\0') {
        len++;
    }

    // 2. Allocate output buffer (Max size would be the same as input length)
    char* result = new char[len + 1];
    int resIndex = 0;

    // 3. Initialize Stack for operators
    CharStack st(len);

    for (int i = 0; i < len; i++) {
        char c = exp[i];

        // Step A: If the character is an operand (letter or digit), append to output string
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            result[resIndex++] = c;
        }
        // Step B: If the character is '(', push it to stack
        else if (c == '(') {
            st.push(c);
        }
        // Step C: If the character is ')', pop and add to output string until '(' is found
        else if (c == ')') {
            while (!st.isEmpty() && st.peek() != '(') {
                result[resIndex++] = st.pop();
            }
            if (!st.isEmpty() && st.peek() == '(') {
                st.pop(); // Remove the '(' from stack
            }
        }
        // Step D: If an operator is encountered
        else {
            while (!st.isEmpty() && getPrecedence(exp[i]) <= getPrecedence(st.peek())) {
                // Handling Right-to-Left Associativity for the exponent operator (^)
                if (c == '^' && st.peek() == '^') {
                    break;
                }
                else {
                    result[resIndex++] = st.pop();
                }
            }
            st.push(c);
        }
    }

    // Step E: Pop all the remaining elements from the stack
    while (!st.isEmpty()) {
        result[resIndex++] = st.pop();
    }

    result[resIndex] = '\0'; 
    return result;
}
