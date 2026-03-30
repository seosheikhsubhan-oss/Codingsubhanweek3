#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// =========================================================
// Package Structure
// =========================================================
struct Package {
    int id;
    string address;
    int startTime; // 24-hour format, e.g., 900 for 9:00 AM
    int endTime;   // 24-hour format, e.g., 1700 for 5:00 PM
};

// =========================================================
// Real-Time Delivery Queue Implementation
// =========================================================
class DeliveryQueue {
private:
    Package* queueArray;
    int capacity;
    int frontIndex;
    int rearIndex;
    int count;

public:
    // Constructor
    DeliveryQueue(int size) {
        capacity = size;
        queueArray = new Package[capacity];
        frontIndex = 0;
        rearIndex = -1;
        count = 0;
    }

    // Destructor
    ~DeliveryQueue() {
        delete[] queueArray;
    }

    // 1. Enqueue: Add a new package with its details
    void enqueue(int id, string address, int start, int end) {
        if (isFull()) {
            cout << "[Error] Logistics Queue is Full! Cannot accept Package ID: " << id << "\n";
            return;
        }
        
        rearIndex = (rearIndex + 1) % capacity;
        queueArray[rearIndex].id = id;
        queueArray[rearIndex].address = address;
        queueArray[rearIndex].startTime = start;
        queueArray[rearIndex].endTime = end;
        count++;
        
        cout << "[Success] Package ID " << id << " added to the delivery queue.\n";
    }

    // 2. Dequeue: Process and remove the front package
    void dequeue() {
        if (isEmpty()) return;
        frontIndex = (frontIndex + 1) % capacity;
        count--;
    }

    // 3. Front: Inspect the front package without removing it
    void front() const {
        if (isEmpty()) {
            cout << "No packages in the queue.\n";
            return;
        }
        Package p = queueArray[frontIndex];
        cout << "Next Package -> ID: " << p.id 
             << " | Address: " << p.address 
             << " | Window: " << setfill('0') << setw(4) << p.startTime 
             << " to " << setfill('0') << setw(4) << p.endTime << "\n";
    }

    // 4. Display: View all packages currently in the queue
    void display() const {
        if (isEmpty()) {
            cout << "The delivery queue is currently empty.\n";
            return;
        }

        cout << "--- Current Delivery Queue ---\n";
        int idx = frontIndex;
        for (int i = 0; i < count; i++) {
            Package p = queueArray[idx];
            cout << i + 1 << ". [ID: " << p.id << "] " 
                 << "To: " << p.address 
                 << " (Window: " << setfill('0') << setw(4) << p.startTime 
                 << "-" << setfill('0') << setw(4) << p.endTime << ")\n";
            idx = (idx + 1) % capacity;
        }
        cout << "------------------------------\n";
    }

    // 5. TimeToDeliver: Check if the front package can be delivered
    void timeToDeliver(int currentTime) {
        if (isEmpty()) {
            cout << "No packages to process.\n";
            return;
        }

        // Keep checking packages until we find one we can deliver, or we hit one we must wait for
        while (!isEmpty()) {
            Package p = queueArray[frontIndex];

            if (currentTime > p.endTime) {
                // Time has passed the end window. It is expired.
                cout << "[EXPIRED] Package ID " << p.id << " missed its delivery window! Skipping to next.\n";
                dequeue(); // Remove from queue and continue the loop
            } 
            else if (currentTime < p.startTime) {
                // Time hasn't reached the start window yet. FIFO means we wait.
                cout << "[WAIT] Package ID " << p.id << " cannot be delivered yet. Window starts at " 
                     << setfill('0') << setw(4) << p.startTime << ". Driver is waiting.\n";
                break; // Stop processing, we must wait for time to pass
            } 
            else {
                // currentTime is within the delivery window!
                cout << "[DELIVERED] Package ID " << p.id << " successfully delivered to " << p.address << "!\n";
                dequeue(); // Remove from queue
                break; // Stop processing (driver has to drive to the next one, simulating one delivery at a time)
            }
        }
    }

    // Helpers
    bool isEmpty() const { return count == 0; }
    bool isFull() const { return count == capacity; }
};

// =========================================================
// Main Function (Logistics Simulation)
// =========================================================
int main() {
    int maxCapacity;
    cout << "--- Real-Time Package Delivery System ---\n";
    cout << "Enter max capacity of the delivery truck/queue: ";
    cin >> maxCapacity;

    DeliveryQueue logisticsSystem(maxCapacity);
    
    int currentTime = 800; // Start the day at 08:00 AM
    int choice;

    do {
        cout << "\n========== LOGISTICS DASHBOARD ==========\n";
        cout << "Current System Time: " << setfill('0') << setw(4) << currentTime << " Hours\n";
        cout << "1. Receive new package (Enqueue)\n";
        cout << "2. Attempt delivery (timeToDeliver)\n";
        cout << "3. View next package (Front)\n";
        cout << "4. View all scheduled packages (Display)\n";
        cout << "5. Fast-Forward Time (Simulate time passing)\n";
        cout << "6. End Shift (Exit)\n";
        cout << "=========================================\n";
        cout << "Action: ";
        cin >> choice;

        if (choice == 1) {
            int id, start, end;
            string addr;
            cout << "Enter Package ID: ";
            cin >> id;
            cin.ignore(); // Clear buffer
            cout << "Enter Delivery Address: ";
            getline(cin, addr);
            cout << "Enter Start Time (e.g. 0900): ";
            cin >> start;
            cout << "Enter End Time (e.g. 1700): ";
            cin >> end;
            logisticsSystem.enqueue(id, addr, start, end);
        } 
        else if (choice == 2) {
            logisticsSystem.timeToDeliver(currentTime);
        } 
        else if (choice == 3) {
            logisticsSystem.front();
        } 
        else if (choice == 4) {
            logisticsSystem.display();
        } 
        else if (choice == 5) {
            int mins;
            cout << "Enter hours/minutes to advance (e.g. 100 for 1 hour): ";
            cin >> mins;
            currentTime += mins;
            // Simple clock adjustment (e.g. 0860 becomes 0900)
            if (currentTime % 100 >= 60) {
                currentTime = currentTime + 40; 
            }
            cout << "Time updated to " << setfill('0') << setw(4) << currentTime << ".\n";
        } 
        else if (choice == 6) {
            cout << "Ending shift. Closing system...\n";
        } 
        else {
            cout << "Invalid input.\n";
        }
    } while (choice != 6);

    return 0;
}
