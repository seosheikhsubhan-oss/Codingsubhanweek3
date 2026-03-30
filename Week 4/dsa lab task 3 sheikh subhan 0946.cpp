#include <iostream>
#include <stack>

using namespace std;

// =========================================================
// Custom Queue Implementation
// =========================================================
class Queue {
private:
    int* arr;
    int capacity;
    int frontIndex;
    int rearIndex;
    int count;

public:
    Queue(int size) {
        capacity = size;
        arr = new int[capacity];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    ~Queue() {
        delete[] arr;
    }

    void enqueue(int value) {
        if (count == capacity) {
            cout << "Queue is full!\n";
            return;
        }
        rearIndex = (rearIndex + 1) % capacity;
        arr[rearIndex] = value;
        count++;
    }

    int dequeue() {
        if (isEmpty()) {
            return -1; 
        }
        int item = arr[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        count--;
        return item;
    }

    int front() const {
        if (isEmpty()) {
            return -1;
        }
        return arr[frontIndex];
    }

    bool isEmpty() const {
        return count == 0;
    }

    int getSize() const {
        return count;
    }
    
    // Helper to print without modifying the queue
    void display() const {
        int idx = frontIndex;
        for (int i = 0; i < count; i++) {
            cout << arr[idx] << " ";
            idx = (idx + 1) % capacity;
        }
        cout << "\n";
    }
};

// =========================================================
// Algorithm: Reverse First K Elements
// =========================================================
void reverseFirstKElements(Queue& q, int k) {
    int n = q.getSize();

    // Handle edge cases as requested in the lab manual
    if (k <= 1 || q.isEmpty()) {
        return; // No reversal needed for K=0 or K=1
    }
    if (k > n) {
        k = n; // If K is greater than size, reverse the whole queue
    }

    stack<int> s;

    // Step 1: Dequeue first K elements and push them onto the stack
    for (int i = 0; i < k; i++) {
        s.push(q.dequeue());
    }

    // Step 2: Pop elements from the stack and enqueue them back
    // (This adds them to the rear in reversed order)
    while (!s.empty()) {
        q.enqueue(s.top());
        s.pop();
    }

    // Step 3: Dequeue the remaining (N - K) elements and enqueue them to the rear
    // (This pushes the original trailing elements behind the reversed segment)
    for (int i = 0; i < n - k; i++) {
        q.enqueue(q.dequeue());
    }
}

// =========================================================
// Main Function
// =========================================================
int main() {
    int n, k, value;

    cout << "--- Task 3: Reverse First K Elements of a Queue ---\n\n";

    cout << "Enter the total number of elements you want to add to the queue: ";
    cin >> n;

    if (n <= 0) {
        cout << "Queue size must be greater than 0.\n";
        return 0;
    }

    Queue q(n);

    cout << "Enter the " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> value;
        q.enqueue(value);
    }

    cout << "Enter the value of K (number of elements to reverse): ";
    cin >> k;

    cout << "\nOriginal Queue: ";
    q.display();

    // Apply the reversal logic
    reverseFirstKElements(q, k);

    cout << "Queue after reversing first " << k << " elements: ";
    q.display();

    return 0;
}
