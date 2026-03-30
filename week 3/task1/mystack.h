#ifndef MYSTACK_H
#define MYSTACK_H

#include "AbstractStack.h"
#include <iostream>
using namespace std;

template <typename T>
class myStack : public AbstractStack<T> {
private:
    T* arr;
    int maxSize;
    int topIndex;

public:
    myStack(int size);
    ~myStack();

    void push(T value);
    T pop();
    T top() const;
    bool isEmpty() const;
    bool isFull() const;

    void display() const;
};

#endif
