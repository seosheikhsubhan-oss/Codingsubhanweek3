#include <iostream>
using namespace std;

// =========================================================
// 1. Abstract Class (Generic Template Interface)
// =========================================================
template <class T>
class AbstractQueue {
public:
    virtual void enQueue(T value) = 0;
    virtual T deQueue() = 0;
    virtual T front() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual ~AbstractQueue() {}
};

// =========================================================
// 2. Child Class (Concrete Generic Template Implementation)
// =========================================================
template <class T>
class myQueue : public AbstractQueue<T> {
private:
    T* arr;         // Dynamically allocated array for queue storage
    int capacity;   // Maximum size of the queue
    int frontIndex; // Points to the front element
    int rearIndex;  // Points to the last inserted element
    int count;      // Tracks the current number of elements in the queue

public:
    // Constructor defining max size
    myQueue(int size) {
        capacity = size;
        arr = new T[capacity];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    // Destructor to free dynamically allocated memory
    ~myQueue() {
        delete[] arr;
    }

    // Adds an element to the end/rear of the Queue
    void enQueue(T value) override {
        if (isFull()) {
            cout << "Queue Overflow! Cannot enqueue " << value << ".\n";
            return;
        }
        // Circular increment to reuse empty spaces at the beginning of the array
        rearIndex = (rearIndex + 1) % capacity;
        arr[rearIndex] = value;
        count++;
        cout << value << " enqueued successfully.\n";
    }

    // Removes and returns the front element
    T deQueue() override {
        if (isEmpty()) {
            cout << "Queue Underflow! Queue is empty.\n";
            return T(); // Return default value of type T if empty
        }
        T item = arr[frontIndex];
        // Circular increment for the front index
        frontIndex = (frontIndex + 1) % capacity;
        count--;
        return item;
    }

    // Returns the front element without removing it
    T front() const override {
        if (isEmpty()) {
            cout << "Queue is empty. No front element.\n";
            return T(); // Return default value of type T
        }
        return arr[frontIndex];
    }

    // Returns true if the queue is empty
    bool isEmpty() const override {
        return count == 0;
    }

    // Returns true if the queue is full
    bool isFull() const override {
        return count == capacity;
    }

    // Prints all elements in the queue from top to bottom (front to rear)
    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return;
        }
        cout << "Queue Elements (Front to Rear): \n";
        int idx = frontIndex;
        for (int i = 0; i < count; i++) {
            cout << "-> " << arr[idx] << "\n";
            idx = (idx + 1) % capacity;
        }
        cout << "-----------------------\n";
    }
};

// =========================================================
// 3. Main Function (Interactive Menu)
// =========================================================
int main() {
    int size;
    cout << "Enter the maximum capacity for the queue: ";
    cin >> size;

    // Create an object of myQueue using integers for testing
    myQueue<int> queue(size);
    
    int choice;
    int value;

    do {
        cout << "\n========== QUEUE MENU ==========\n";
        cout << "1. Enqueue (Add element)\n";
        cout << "2. Dequeue (Remove element)\n";
        cout << "3. Front (View front element)\n";
        cout << "4. Check if Empty\n";
        cout << "5. Check if Full\n";
        cout << "6. Display all elements\n";
        cout << "7. Exit\n";
        cout << "================================\n";
        cout << "Enter your choice (1-7): ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to enqueue: ";
                cin >> value;
                queue.enQueue(value);
                break;
                
            case 2:
                if (!queue.isEmpty()) {
                    cout << queue.deQueue() << " dequeued successfully.\n";
                } else {
                    queue.deQueue(); // Triggers the underflow message
                }
                break;
                
            case 3:
                if (!queue.isEmpty()) {
                    cout << "Front element is: " << queue.front() << "\n";
                } else {
                    queue.front(); // Triggers the empty queue message
                }
                break;
                
            case 4:
                if (queue.isEmpty()) {
                    cout << "Yes, the queue is currently empty.\n";
                } else {
                    cout << "No, the queue is not empty.\n";
                }
                break;
                
            case 5:
                if (queue.isFull()) {
                    cout << "Yes, the queue is currently full.\n";
                } else {
                    cout << "No, the queue is not full.\n";
                }
                break;
                
            case 6:
                queue.display();
                break;
                
            case 7:
                cout << "Exiting program. Goodbye!\n";
                break;
                
            default:
                cout << "Invalid choice! Please select a valid option from 1 to 7.\n";
        }
    } while (choice != 7);

    return 0;
}
