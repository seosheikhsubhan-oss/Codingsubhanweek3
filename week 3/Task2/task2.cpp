#include <iostream>
#include "myStack.h"
using namespace std;

int main() {
    myStack<int> s(10);
    int choice, value;

    do {
        cout << "\n1. Push\n2. Pop\n3. Top\n4. isEmpty\n5. isFull\n6. Display\n7. Get Min\n8. Exit\n";
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
        case 7:
            cout << "Minimum: " << s.getMin() << endl;
            break;
        }
    } while (choice != 8);

    return 0;
}
