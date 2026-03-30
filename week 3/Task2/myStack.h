#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>
#include "AbstractStack.h"
using namespace std;

template <typename T>
class myStack : public AbstractStack<T> {
private:
    T* arr;
    T* minArr;   // additional stack for minimum tracking
    int topIndex;
    int minTop;
    int capacity;

public:
    myStack(int size) {
        capacity = size;
        arr = new T[capacity];
        minArr = new T[capacity];
        topIndex = -1;
        minTop = -1;
    }

    void push(T value) {
        if (isFull()) {
            cout << "Stack Overflow!\n";
            return;
        }

        arr[++topIndex] = value;

        // Maintain min stack
        if (minTop == -1 || value <= minArr[minTop]) {
            minArr[++minTop] = value;
        }
    }

    T pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!\n";
            return -1;
        }

        T removed = arr[topIndex--];

        if (removed == minArr[minTop]) {
            minTop--;
        }

        return removed;
    }

    T top() const {
        if (isEmpty()) {
            cout << "Stack Empty!\n";
            return -1;
        }
        return arr[topIndex];
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex == capacity - 1;
    }

    T getMin() const {
        if (minTop == -1) {
            cout << "Stack Empty!\n";
            return -1;
        }
        return minArr[minTop];
    }

    void display() const {
        if (isEmpty()) {
            cout << "Stack Empty!\n";
            return;
        }

        cout << "Stack (Top ? Bottom): ";
        for (int i = topIndex; i >= 0; i--) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    ~myStack() {
        delete[] arr;
        delete[] minArr;
    }
};

#endif
