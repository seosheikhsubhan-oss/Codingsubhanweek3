#include <iostream>
#include <string>

using namespace std;

// =========================================================
// Document Print Queue Implementation
// =========================================================
class PrintQueue {
private:
    string* queueArray;
    int capacity;
    int frontIndex;
    int rearIndex;
    int count;

public:
    // Constructor to initialize the print queue
    PrintQueue(int size) {
        capacity = size;
        queueArray = new string[capacity];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    // Destructor to free dynamically allocated memory
    ~PrintQueue() {
        delete[] queueArray;
    }

    // 1. Enqueue: Add a new document to the print queue
    void enqueue(string document_name) {
        if (isFull()) {
            cout << "Printer memory is full! Cannot add '" << document_name << "' right now.\n";
            return;
        }
        
        // Circular increment for the rear index
        rearIndex = (rearIndex + 1) % capacity;
        queueArray[rearIndex] = document_name;
        count++;
        
        cout << "Document '" << document_name << "' added to the print queue.\n";
    }

    // 2. Dequeue: Print the document at the front of the queue
    void dequeue() {
        if (isEmpty()) {
            cout << "Printer is idle. No documents in the queue to print.\n";
            return;
        }
        
        string printedDoc = queueArray[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        count--;
        
        cout << ">>> PRINTING: '" << printedDoc << "' ... Done!\n";
    }

    // 3. Front: Check the document at the front without removing it
    void front() const {
        if (isEmpty()) {
            cout << "The print queue is currently empty.\n";
            return;
        }
        
        cout << "Next document to be printed is: '" << queueArray[frontIndex] << "'\n";
    }

    // 4. Display: Show all the documents in the queue
    void display() const {
        if (isEmpty()) {
            cout << "There are no pending print jobs.\n";
            return;
        }

        cout << "--- Current Print Jobs ---\n";
        int idx = frontIndex;
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ". " << queueArray[idx] << "\n";
            idx = (idx + 1) % capacity;
        }
        cout << "--------------------------\n";
    }

    // Helper methods to check queue status
    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == capacity;
    }
};

// =========================================================
// Main Function (Printer Simulation)
// =========================================================
int main() {
    int maxJobs;
    cout << "--- Office Printer System ---\n";
    cout << "Enter the maximum number of print jobs the printer can queue: ";
    cin >> maxJobs;

    // Clear the input buffer before reading strings with getline
    cin.ignore(); 

    PrintQueue printer(maxJobs);
    int choice;
    string docName;

    do {
        cout << "\n========== PRINTER MENU ==========\n";
        cout << "1. Send document to printer (Enqueue)\n";
        cout << "2. Print next document (Dequeue)\n";
        cout << "3. View next document in line (Front)\n";
        cout << "4. Display all pending jobs (Display)\n";
        cout << "5. Power off printer (Exit)\n";
        cout << "==================================\n";
        cout << "Select an action (1-5): ";
        cin >> choice;
        cin.ignore(); // Clear the newline character left by cin

        switch (choice) {
            case 1:
                cout << "Enter the name of the document: ";
                getline(cin, docName); // Use getline to allow spaces in document names
                printer.enqueue(docName);
                break;
                
            case 2:
                printer.dequeue();
                break;
                
            case 3:
                printer.front();
                break;
                
            case 4:
                printer.display();
                break;
                
            case 5:
                cout << "Powering off the printer. Goodbye!\n";
                break;
                
            default:
                cout << "Invalid selection! Please choose between 1 and 5.\n";
        }
    } while (choice != 5);

    return 0;
}
