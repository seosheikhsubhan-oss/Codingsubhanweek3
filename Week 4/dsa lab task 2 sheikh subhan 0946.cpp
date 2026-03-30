#include <iostream>
#include <stack>

using namespace std;

// =========================================================
// Queue Implementation using Two Stacks
// =========================================================
template <class T>
class QueueUsingStacks {
private:
    stack<T> stack1; // Used for Enqueue operations (Inbox)
    stack<T> stack2; // Used for Dequeue and Front operations (Outbox)

    // Helper function to transfer elements from stack1 to stack2
    // This is only done when stack2 is empty
    void transferIfNeeded() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
    }

public:
    // 1. Enqueue: Insert an element at the end of the queue
    void enqueue(T value) {
        stack1.push(value);
        cout << value << " enqueued successfully.\n";
    }

    // 2. Dequeue: Remove and return the front element of the queue
    T dequeue() {
        transferIfNeeded(); // Ensure stack2 has the front elements

        if (stack2.empty()) {
            cout << "Queue Underflow! The queue is empty.\n";
            return T(); // Return default value
        }

        T frontValue = stack2.top();
        stack2.pop();
        return frontValue;
    }

    // 3. Front Element: Return the front element without removing it
    T front() {
        transferIfNeeded(); // Ensure stack2 has the front elements

        if (stack2.empty()) {
            cout << "The queue is empty. No front element.\n";
            return T(); // Return default value
        }

        return stack2.top();
    }

    // Utility function to check if the queue is empty
    bool isEmpty() const {
        return stack1.empty() && stack2.empty();
    }

    // 4. Display Elements: Print all elements in the queue (Front to Rear)
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }

        cout << "Queue Elements (Front to Rear): ";
        
        // Stack 2 contains the front-most elements (top is the absolute front)
        // We make a copy so we don't destroy the actual queue while printing
        stack<T> temp2 = stack2;
        while (!temp2.empty()) {
            cout << temp2.top() << " ";
            temp2.pop();
        }

        // Stack 1 contains the newer elements (bottom is the older, top is the absolute rear)
        // To print from bottom to top, we need to reverse it first using a temp stack
        stack<T> temp1 = stack1;
        stack<T> reverseStack1;
        while (!temp1.empty()) {
            reverseStack1.push(temp1.top());
            temp1.pop();
        }
        
        // Now print the reversed stack1
        while (!reverseStack1.empty()) {
            cout << reverseStack1.top() << " ";
            reverseStack1.pop();
        }
        
        cout << "\n-----------------------\n";
    }
};

// =========================================================
// Main Function (Interactive Menu)
// =========================================================
int main() {
    QueueUsingStacks<int> q;
    int choice;
    int value;

    cout << "--- Task 2: Queue Implementation using Two Stacks ---\n";

    do {
        cout << "\n========== QUEUE MENU ==========\n";
        cout << "1. Enqueue (Add element)\n";
        cout << "2. Dequeue (Remove element)\n";
        cout << "3. Front (View front element)\n";
        cout << "4. Display all elements\n";
        cout << "5. Exit\n";
        cout << "================================\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to enqueue: ";
                cin >> value;
                q.enqueue(value);
                break;
                
            case 2:
                if (!q.isEmpty()) {
                    cout << q.dequeue() << " dequeued successfully.\n";
                } else {
                    q.dequeue(); // Triggers the underflow message
                }
                break;
                
            case 3:
                if (!q.isEmpty()) {
                    cout << "Front element is: " << q.front() << "\n";
                } else {
                    q.front(); // Triggers the empty queue message
                }
                break;
                
            case 4:
                q.display();
                break;
                
            case 5:
                cout << "Exiting program. Goodbye!\n";
                break;
                
            default:
                cout << "Invalid choice! Please select a valid option from 1 to 5.\n";
        }
    } while (choice != 5);

    return 0;
}
