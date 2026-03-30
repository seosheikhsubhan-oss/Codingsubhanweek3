#include <iostream>
#include "myStack.h"
using namespace std;

int main() {
    int size;
    cout << "Enter stack size: ";
    cin >> size;

    myStack<int> s(size);

    int choice, value;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Top\n";
        cout << "4. isEmpty\n";
        cout << "5. isFull\n";
        cout << "6. Display\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            s.push(value);
            break;

        case 2:
            cout << "Popped: " << s.pop() << endl;
            break;

        case 3:
            cout << "Top: " << s.top() << endl;
            break;

        case 4:
            cout << (s.isEmpty() ? "Empty\n" : "Not Empty\n");
            break;

        case 5:
            cout << (s.isFull() ? "Full\n" : "Not Full\n");
            break;

        case 6:
            s.display();
            break;
        }

    } while (choice != 0);

    return 0;
}