#include <iostream>
using namespace std;


class TwoStacks {
private:
    int* arr;       
    int size;     
    int top1;       
    int top2;      

public:
    TwoStacks(int n);
    ~TwoStacks();
    void push1(int x);
    void push2(int x);
    int pop1();
    int pop2();
};

int main() {
    cout << "--- Testing Two Stacks in One Array ---\n\n";
    
    // Create a shared array of size 100 for the two stacks
    TwoStacks ts(100); 
    
    cout << "Input Sequence:\n";
    cout << "push1(2)\npush1(3)\npush2(4)\npop1()\npop2()\npop2()\n\n";

    ts.push1(2);
    ts.push1(3);
    ts.push2(4);

    cout << "Output:\n";
    
    cout << ts.pop1() << " ";
    cout << ts.pop2() << " ";
    cout << ts.pop2() << "\n";

    return 0;
}

/*
 * Task: Constructor to initialize a shared array for two stacks.
 * Input Parameters: 
 * - int n: Maximum capacity of the shared array.
 */
TwoStacks::TwoStacks(int n) {
    size = n;
    arr = new int[n];
    top1 = -1;       // Stack 1 starts out of bounds on the left
    top2 = size;     // Stack 2 starts out of bounds on the right
}

/*
 * Task: Destructor to free dynamically allocated memory.
 */
TwoStacks::~TwoStacks() {
    delete[] arr;
}

/*
 * Task: Pushes an element into Stack 1 (grows from left to right).
 * Input Parameters: 
 * - int x: The integer value to be pushed into Stack 1.
 */
void TwoStacks::push1(int x) {
    // Check if there is at least one empty space between the two tops
    if (top1 < top2 - 1) { 
        arr[++top1] = x;
    } else {
        cout << "Stack Overflow! Cannot push into Stack 1.\n";
    }
}

/*
 * Task: Pushes an element into Stack 2 (grows from right to left).
 * Input Parameters: 
 * - int x: The integer value to be pushed into Stack 2.
 */
void TwoStacks::push2(int x) {
    // Check if there is at least one empty space between the two tops
    if (top1 < top2 - 1) { 
        arr[--top2] = x;
    } else {
        cout << "Stack Overflow! Cannot push into Stack 2.\n";
    }
}

/*
 * Task: Pops and returns the top element from Stack 1.
 * Input Parameters: None.
 * Returns: The popped integer, or -1 if Stack 1 is empty.
 */
int TwoStacks::pop1() {
    // Check for Underflow (if top1 has elements)
    if (top1 >= 0) {
        return arr[top1--];
    }
    return -1; // Return -1 as requested if no element is present
}

/*
 * Task: Pops and returns the top element from Stack 2.
 * Input Parameters: None.
 * Returns: The popped integer, or -1 if Stack 2 is empty.
 */
int TwoStacks::pop2() {
    // Check for Underflow (if top2 is within array bounds)
    if (top2 < size) {
        return arr[top2++];
    }
    return -1; // Return -1 as requested if no element is present
}
