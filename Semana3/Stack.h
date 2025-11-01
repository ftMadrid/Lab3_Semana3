#ifndef STACK_H
#define STACK_H

#include "Node.h"

template <class T>
class Stack {

public:

    Stack();

    Node<T>* topNode;
    int count;

    void push(T value);
    void pop();
    T top();
    bool empty();
    int size();
    void clear();

};

template <class T>
Stack<T>::Stack(){
    this->topNode = nullptr;
    this->count = 0;
}

template<class T>
void Stack<T>::push(T value) {
    Node<T>* newNode = new Node<T>(value);
    newNode->next = topNode;
    topNode = newNode;
    count++;
}

template<class T>
void Stack<T>::pop() {
    if (empty()){
        return;
    }
    Node<T>* it = topNode;
    topNode = topNode->next;
    delete it;
    count--;
}

template<class T>
T Stack<T>::top() {
    if (empty()) {
        throw out_of_range("\n| The stack is empty!");
    }
    return topNode->data;
}

template<class T>
bool Stack<T>::empty() {
    return topNode == nullptr;
}

template<class T>
int Stack<T>::size(){
    return count;
}

template<class T>
void Stack<T>::clear() {
    while (!empty()){
        pop();
    }
}

#endif // STACK_H
