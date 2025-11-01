#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>
#include <stdexcept>

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::out_of_range;

template <class T>
class LinkedList {

public:
    LinkedList();
    Node<T>* head;
    int lenght;
    void push_back(T value);
    void insert(int pos, T value);
    void erase(int pos);
    void replace(int pos, T value);
    T at(int pos);
    int size();
    void clear();
    void print();

};

template <class T>
LinkedList<T>::LinkedList(){
    this->head = nullptr;
    this->lenght = 0;
}

template <class T>
    void LinkedList<T>::push_back(T value){
        Node<T>* newNode = new Node<T>(value);

        if(head != nullptr){
            head = newNode;
        }else{
            Node<T>* it = head;
            while(it != nullptr){
                it = it->next;
            }
            it->next = newNode;
        }
        lenght++;
    }

template <class T>
void LinkedList<T>::insert(int pos, T value){
    if(pos < 0 || pos > lenght) {
        cout << "\n| The position is invalid!" <<endl;
        return;
    }
    Node<T>* newNode = new Node<T>(value);
    if(pos == 0){
        newNode->next = head;
        head = newNode;
    }else{
        Node<T>* it = head;
        for(int i = 0; i < pos - 1; i++){
            it = it->next;
        }
        newNode->next = it->next;
        it->next = newNode;
    }
    cout << "\n| The word " << value << " has been added in the position [" <<pos<<"]!" <<endl;
    lenght++;
}

template <class T>
void LinkedList<T>::erase(int pos){

    if(head == nullptr){
        throw out_of_range("\n| This position doesnt have any word!");
    }

    if(pos < 0 || pos >= lenght){
        throw out_of_range("\n| The position is invalid!");
    }

    Node<T>* it = head;
    if(pos == 0){
        head = head->next;
        cout << "\n| The word " << it->data << " has been deleted of the position [" <<pos<<"]!" <<endl;
        delete it;
    }else{
        for(int i = 0; i < pos - 1; i++){
            it = it->next;
        }
        if (it->next == nullptr) {
            throw out_of_range("\n| This position doesnt have any word!");
        }
        Node<T>* toDelete = it->next;
        it->next = toDelete->next;
        cout << "\n| The word " << toDelete->data << " has been deleted of the position [" <<pos<<"]!" <<endl;
        delete toDelete;
    }
    lenght--;

}

template <class T>
void LinkedList<T>::replace(int pos, T value) {
    if (pos < 0 || pos >= lenght){
        throw out_of_range("\n| The position is invalid!");
    }
    Node<T>* it = head;
    for (int i = 0; i < pos; ++i){
        it = it->next;
    }
    cout << "\n| You have changed the word of the position ["<<pos<<"]!"<<endl;
    cout << "| Old word: "<<it->data<<endl;
    it->data = value;
    cout << "| New word: "<<it->data<<endl;
}

template <class T>
T LinkedList<T>::at(int pos){

    if(head == nullptr){
        throw out_of_range("\n| This position doesnt have any word!");
    }

    if(pos < 0 || pos >= lenght){
        throw out_of_range("\n| The position is invalid!");
    }

    Node<T>* it = head;
    for(int i = 0; i < pos; i++){
        it = it->next;
    }
    return it->data;
}

template <class T>
int LinkedList<T>::size(){
    return lenght;
}

template<class T>
void LinkedList<T>::clear(){
    while(head != nullptr){
        Node<T>* it = head;
        head = head->next;
        delete it;
    }
    lenght = 0;
}

template <class T>
void LinkedList<T>::print(){

    if(head == nullptr){
        cout << "| The document is empty!"<<endl;
        return;
    }

    Node<T>* it = head;
    int i = 0;
    while(it != nullptr){
        cout << i++ << ": " << it->data << endl;
        it = it->next;
    }
}

#endif // LINKEDLIST_H
