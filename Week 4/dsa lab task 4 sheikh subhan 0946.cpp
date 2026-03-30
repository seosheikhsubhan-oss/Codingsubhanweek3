#include <iostream>
#include <iomanip> // For formatting 4-digit IDs

using namespace std;

// =========================================================
// Customer Support Ticket Queue Implementation
// =========================================================
class TicketQueue {
private:
    int* queueArray;
    int capacity;
    int frontIndex;
    int rearIndex;
    int count;

public:
    // Constructor to initialize the queue
    TicketQueue(int size) {
        capacity = size;
        queueArray = new int[capacity];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    // Destructor to free memory
    ~TicketQueue() {
        delete[] queueArray;
    }

    // 1. Enqueue: Add a new support ticket to the queue
    void enqueue(int ticket_id) {
        if (count == capacity) {
            cout << "System Full! Cannot accept more tickets right now.\n";
            return;
        }
        
        // Circular increment
        rearIndex = (rearIndex + 1) % capacity;
        queueArray[rearIndex] = ticket_id;
        count++;
        
        cout << "Ticket ID [" << setfill('0') << setw(4) << ticket_id 
             << "] has been added to the support queue.\n";
    }

    // 2. Dequeue: Resolve and remove the ticket at the front
    void dequeue() {
        if (isEmpty()) {
            cout << "No pending tickets to resolve. Great job!\n";
            return;
        }
        
        int resolvedTicket = queueArray[frontIndex];
        frontIndex = (frontIndex + 1) % capacity;
        count--;
        
        cout << "Ticket ID [" << setfill('0') << setw(4) << resolvedTicket 
             << "] has been successfully resolved and removed from the queue.\n";
    }

    // 3. Front: Show the ticket at the front without removing it
    void front() const {
        if (isEmpty()) {
            cout << "The queue is currently empty. No next ticket.\n";
            return;
        }
        
        cout << "Next ticket to be resolved is ID: [" 
             << setfill('0') << setw(4) << queueArray[frontIndex] << "]\n";
    }

    // 4. Display: Show all pending tickets in the queue
    void display() const {
        if (isEmpty()) {
            cout << "There are currently NO pending tickets.\n";
            return;
        }

        cout << "--- Pending Customer Support Tickets ---\n";
        int idx = frontIndex;
        for (int i = 0; i < count; i++) {
            cout << i + 1 << ". Ticket ID: [" 
                 << setfill('0') << setw(4) << queueArray[idx] << "]\n";
            idx = (idx + 1) % capacity;
        }
        cout << "----------------------------------------\n";
    }

    // Helper method to check if the queue is empty
    bool isEmpty() const {
        return count == 0;
    }
};

// =========================================================
// Main Function (Customer Support Simulation)
// =========================================================
int main() {
    int maxTickets;
    cout << "--- Customer Support Ticket System ---\n";
    cout << "Enter the maximum number of tickets the system can handle at once: ";
    cin >> maxTickets;

    TicketQueue supportSystem(maxTickets);
    int choice;
    int ticketID;

    do {
        cout << "\n========== SUPPORT AGENT DASHBOARD ==========\n";
        cout << "1. Add new ticket (Enqueue)\n";
        cout << "2. Resolve next ticket (Dequeue)\n";
        cout << "3. View next ticket to resolve (Front)\n";
        cout << "4. Display all pending tickets (Display)\n";
        cout << "5. Exit System\n";
        cout << "=============================================\n";
        cout << "Select an action (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter a 4-digit Ticket ID: ";
                cin >> ticketID;
                // Basic validation for positive numbers
                if (ticketID < 0 || ticketID > 9999) {
                    cout << "Invalid ID. Please enter a valid 4-digit number (0000-9999).\n";
                } else {
                    supportSystem.enqueue(ticketID);
                }
                break;
                
            case 2:
                supportSystem.dequeue();
                break;
                
            case 3:
                supportSystem.front();
                break;
                
            case 4:
                supportSystem.display();
                break;
                
            case 5:
                cout << "Shutting down the Customer Support System. Goodbye!\n";
                break;
                
            default:
                cout << "Invalid selection! Please choose between 1 and 5.\n";
        }
    } while (choice != 5);

    return 0;
}
