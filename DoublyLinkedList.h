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
    node* current;
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
    Data removeFromEnd();
    Data removeFromBeginning();

    // class EMPTY_LIST : public std::exception {}; *****************
};

template <class Data>
DoublyLinkedList<Data>::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

template <class Data>
DoublyLinkedList<Data>::~DoublyLinkedList()
{
    node* currentNode = this->head->current, temp;
    while (currentNode)
    {
        temp = currentNode;
        currentNode = currentNode->next;
        delete temp;
    }
}

template <class Data>
void DoublyLinkedList<Data>::addToEnd(Data data)
{
    node *newNode = new node();
    this->current = newNode; //////////////////////////
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = this->tail;
    if (this->tail) {
        //this->tail->next = new node();
        //this->tail->next->data = data;
        this->tail->next = newNode;
        //(this->tail->next)->prev = this->tail;
        //(this->tail->next)->next = nullptr;
        this->tail = this->tail->next;
        //////(this->tail->prev)->next = this->tail;
    }
    else {
        this->head = newNode;
        this->tail = this->head;
    }
}

template <class Data>
void DoublyLinkedList<Data>::addToBeginning(Data data)
{
    node* newNode = new node();
    newNode->data = data;
    newNode->prev = nullptr;
    newNode->next = this->head;
    this->current = newNode; //////////////////////////
    //this->head = head;
    if (this->head) {
        this->head->prev = newNode;
        this->head = newNode;
    }
    else {
        this->head = newNode;
        this->tail = this->head;
    }
}

template <class Data>
void DoublyLinkedList<Data>::addAfter(Data data)
{
    if (!(this->current)) {
        addToBeginning(data);
        return;
    }
    if (!(this->current->next)) {
        addToEnd(data);
        return;
    }
    node* newNode = new node();
    newNode->data = data;
    newNode->prev = this->current;
    newNode->next = this->current->next;
    this->current->next = newNode;
    if (newNode->next) {
        (newNode->next)->prev = newNode;
    }
    this->current = newNode;
    /*
    this->head = head;
    if (head->next)
        head->next->prev = head;

    if (isEmpty())
        tail = head;
    */
}

template <class Data>
Data DoublyLinkedList<Data>::removeFromEnd()
{
    /*
    if (isEmpty())
        throw EMPTY_LIST();//
    */
    Data data = NULL;
    node* temp = this->tail;
    if (temp) {
        data = this->tail->data;
        this->tail = this->tail->prev;
        delete temp;
    }

    if (this->tail) {
        this->tail->next = nullptr;
    }
    else {
        this->head = nullptr;
    }
    this->current = this->tail;
    return data;
}

template <class Data>
Data DoublyLinkedList<Data>::removeFromBeginning()
{
    /*
    if (isEmpty()) {
        throw EMPTY_LIST;
    }
     */
    node *temp = this->head;
    Data data = NULL;
    if (temp) {
        data = temp->data;
        this->head = this->head->next;
        delete temp;
    }
    if (this->head) {
        this->head->prev = nullptr;
    }
    else {
        this->tail = nullptr;
    }
    this->current = this->head;
    return data;
}
















//
//template <class Data>
//class DoublyLinkedList
//{
//private:
//    struct node
//    {
//        Data* data;
//        node* prev;
//        node* next;
//    };
//    //node* current;
//    node* head;
//    node* tail;
//public:
//    DoublyLinkedList();
//
//    ~DoublyLinkedList();
//
//    /*
//    template<int N>
//    double_linked( T (&arr) [N]) : head( NULL ), tail ( NULL )
//    {
//        for( int i(0); i != N; ++i)
//            push_back(arr[i]);
//    }
//     */
//
//    bool isEmpty() const { return ( !head || !tail ); }
//    // operator bool() const { return !empty(); }
//    void addToEnd(Data* data);
//    void addToBeginning(Data* data);
//    void addAfter(Data* data);
//    Data* removeFromEnd();
//    Data* removeFromBeginning();
//
//    // class EMPTY_LIST : public std::exception {}; *****************
//};
//
//template <class Data>
//DoublyLinkedList<Data>::DoublyLinkedList() : head(nullptr), tail (nullptr) {}
//
//template <class Data>
//DoublyLinkedList<Data>::~DoublyLinkedList()
//{
//    node* currentNode = this->head, temp;
//    while (currentNode)
//    {
//        temp = currentNode;
//        currentNode = currentNode->next;
//        delete temp;
//    }
//}
//
//template <class Data>
//void DoublyLinkedList<Data>::addToEnd(Data* data)
//{
//    node *newNode = new node();
//    newNode->data = data;
//    newNode->next = nullptr;
//    newNode->prev = this->tail;
//    if (this->tail) {
//        //this->tail->next = new node();
//        //this->tail->next->data = data;
//        this->tail->next = newNode;
//        //(this->tail->next)->prev = this->tail;
//        //(this->tail->next)->next = nullptr;
//        this->tail = this->tail->next;
//        //////(this->tail->prev)->next = this->tail;
//    }
//    else {
//        this->head = newNode;
//        this->tail = this->head;
//    }
//}
//
//template <class Data>
//void DoublyLinkedList<Data>::addToBeginning(Data* data)
//{
//    node* newNode = new node();
//    newNode->data = data;
//    newNode->prev = nullptr;
//    newNode->next = this->head;
//    //this->head = head;
//    if (this->head) {
//        this->head->prev = newNode;
//        this->head = newNode;
//    }
//    else {
//        this->head = newNode;
//        this->tail = this->head;
//    }
//}
//
//template <class Data>
//void DoublyLinkedList<Data>::addAfter(Data* data)
//{
//    if (!this) {
//        addToBeginning(data);
//        return;
//    }
//    if (!(this->node->next)) {
//        addToEnd(data);
//        return;
//    }
//    node* newNode = new node();
//    newNode->data = data;
//    newNode->prev = this;
//    newNode->next = this->next;
//    this->next = newNode;
//    if (newNode->next) {
//        (newNode->next)->prev = newNode;
//    }
//    /*
//    this->head = head;
//    if (head->next)
//        head->next->prev = head;
//
//    if (isEmpty())
//        tail = head;
//    */
//}
//
//template <class Data>
//Data* DoublyLinkedList<Data>::removeFromEnd()
//{
//    /*
//    if (isEmpty())
//        throw EMPTY_LIST();//********************************************************************************
//    */
//    Data *data = nullptr;
//    node* temp = this->tail;
//    if (temp) {
//        data = this->tail->data;
//        this->tail = this->tail->prev;
//        delete temp;
//    }
//
//    if (this->tail) {
//        this->tail->next = nullptr;
//    }
//    else {
//        this->head = nullptr;
//    }
//    return data;
//}
//
//template <class Data>
//Data* DoublyLinkedList<Data>::removeFromBeginning()
//{
//    /*
//    if (isEmpty()) {
//        throw EMPTY_LIST;
//    }
//     */
//    node *temp = this->head;
//    Data *data = nullptr;
//    if (temp) {
//        data = temp->data;
//        delete temp;
//        this->head = this->head->next;
//    }
//    if (this->head) {
//        this->head->prev = nullptr;
//    }
//    else {
//        this->tail = nullptr;
//    }
//    return data;
//}


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