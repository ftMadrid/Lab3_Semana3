#ifndef NODE_H
#define NODE_H

template <class T>
struct Node {

    T data;
    Node<T>* next;

    Node<T>(T value){
        this->data = value;
        this->next = nullptr;
    }

};

#endif // NODE_H
