//
// Created by mayan on 23-Nov-22.
//

#ifndef MIVNY1_DOUBLYLINKEDLIST_H
#define MIVNY1_DOUBLYLINKEDLIST_H

#include <iostream>

template <class Data>
class DoublyLinkedList
{
private:
    struct node
    {
        Data data;
        node* prev;
        node* next;
    };
    node* head;
    node* tail;
public:
    DoublyLinkedList();

    ~DoublyLinkedList();

    /*
    template<int N>
    double_linked( T (&arr) [N]) : head( NULL ), tail ( NULL )
    {
        for( int i(0); i != N; ++i)
            push_back(arr[i]);
    }
     */

    bool isEmpty() const { return ( !head || !tail ); }
    // operator bool() const { return !empty(); }
    void addToEnd(Data data);
    void addToBeginning(Data data);
    void addAfter(Data data);
    Data* removeFromEnd();
    Data* removeFromBeginning();

    // class EMPTY_LIST : public std::exception {}; *****************
};

template <class Data>
DoublyLinkedList<Data>::DoublyLinkedList() : head(nullptr), tail (nullptr) {}

template <class Data>
DoublyLinkedList<Data>::~DoublyLinkedList()
{
    while (head)
    {
        node* temp(head);
        head=head->next;
        delete temp;
    }
}

template <class Data>
void DoublyLinkedList<Data>::addToEnd(Data data)
{
    tail = new node();
    tail->data = data;
    tail->prev = this->tail;
    tail->next = nullptr;
    this->tail = tail;
    if (tail->prev)
        tail->prev->next = tail;

    if (isEmpty())
        head = tail;
}

template <class Data>
void DoublyLinkedList<Data>::addToBeginning(Data data)
{
    head = new node();
    head->data = data;
    head->prev = nullptr;
    head->next = this->head;
    this->head = head;
    if (head->next)
        head->next->prev = head;

    if (isEmpty())
        tail = head;
}

template <class Data>
void DoublyLinkedList<Data>::addAfter(Data data)
{
    if (this == nullptr) {
        addToBegining(data);
        return;
    }
    if (this->next == nullptr) {
        addToEnd(data);
        return;
    }
    node* newNode = new node();
    newNode->data = data;
    newNode->prev = this;
    newNode->next = this->next;
    this->next = newNode;
    if (newNode->next) {
        (newNode->next)->prev = newNode;
    }
    this->head = head;
    if (head->next)
        head->next->prev = head;

    if (isEmpty())
        tail = head;
}

template <class Data>
Data* DoublyLinkedList<Data>::removeFromEnd()
{
    /*
    if (isEmpty())
        throw EMPTY_LIST();//
        */
    node* temp = this->tail;
    Data* data = tail->data;
    tail = tail->prev;

    if (tail) {
        tail->next = nullptr;
    }
    else {
        head = nullptr;
    }

    delete temp;
    return data;
}

template <class Data>
Data* DoublyLinkedList<Data>::removeFromBeginning()
{
    /*
    if (isEmpty()) {
        throw EMPTY_LIST;
    }
     */
    node* temp = this->head;
    Data* data = head->data;
    head = head->next;

    if (head) {
        head->prev = nullptr;
    }
    else
        tail = nullptr;

    delete temp;
    return data;
}


/*
//#include "PointerPlayer.h"

struct Node {
    PointerPlayer data;
    Node* next;
    Node* prev;
};

class DoublyLinkedList {
private:
    Node* head;
public:

    DoublyLinkedList();
    Node* getNext(struct Node* current) const;
    Node* getPrev(struct Node* current) const;
    Node* getHead() const;
    Node* addNext(struct Node* current, PointerPlayer newData);
    Node* addPrev(struct Node* current, PointerPlayer newData);
    void remove(struct Node* nodeToRemove);
};

*/

#endif //MIVNY1_DOUBLYLINKEDLIST_H