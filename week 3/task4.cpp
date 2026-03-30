#include <iostream>
#include <stack>
using namespace std;

class TextEditor {
private:
    string text;
    stack<string> undoStack;
    stack<string> redoStack;

public:
    void type(string word) {
        undoStack.push(text);
        text += word;
        while (!redoStack.empty()) redoStack.pop();
    }

    void del(int count) {
        undoStack.push(text);
        text.erase(text.size() - count, count);
        while (!redoStack.empty()) redoStack.pop();
    }

    void undo() {
        if (undoStack.empty()) {
            cout << "Nothing to undo\n";
            return;
        }
        redoStack.push(text);
        text = undoStack.top();
        undoStack.pop();
    }

    void redo() {
        if (redoStack.empty()) {
            cout << "Nothing to redo\n";
            return;
        }
        undoStack.push(text);
        text = redoStack.top();
        redoStack.pop();
    }

    void display() {
        cout << "Current Text: " << text << endl;
    }
};

int main() {
    TextEditor editor;
    int choice;
    string input;
    int num;

    do {
        cout << "\n1. Type\n2. Delete\n3. Undo\n4. Redo\n5. Display\n6. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter text: ";
            cin >> input;
            editor.type(input);
            break;
        case 2:
            cout << "Enter number of characters to delete: ";
            cin >> num;
            editor.del(num);
            break;
        case 3:
            editor.undo();
            break;
        case 4:
            editor.redo();
            break;
        case 5:
            editor.display();
            break;
        }
    } while (choice != 6);

    return 0;
}
