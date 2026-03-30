#include "myStack.h"

template <typename T>
myStack<T>::myStack(int size) {
    maxSize = size;
    arr = new T[maxSize];
    topIndex = -1;
}

template <typename T>
myStack<T>::~myStack() {
    delete[] arr;
}

template <typename T>
void myStack<T>::push(T value) {
    if (isFull()) {
        cout << "Stack Overflow!\n";
        return;
    }
    arr[++topIndex] = value;
}

template <typename T>
T myStack<T>::pop() {
    if (isEmpty()) {
        cout << "Stack Underflow!\n";
        return T();
    }
    return arr[topIndex--];
}

template <typename T>
T myStack<T>::top() const {
    if (isEmpty()) {
        cout << "Stack is empty!\n";
        return T();
    }
    return arr[topIndex];
}

template <typename T>
bool myStack<T>::isEmpty() const {
    return topIndex == -1;
}

template <typename T>
bool myStack<T>::isFull() const {
    return topIndex == maxSize - 1;
}

template <typename T>
void myStack<T>::display() const {
    if (isEmpty()) {
        cout << "Stack is empty!\n";
        return;
    }

    cout << "Stack (Top to Bottom):\n";
    for (int i = topIndex; i >= 0; i--) {
        cout << arr[i] << endl;
    }
}