//
// Created by mayan on 23-Nov-22.
//

#include "DoublyLinkedList.h"

DoublyLinkedList::DoublyLinkedList() : head(nullptr) {}

Node* DoublyLinkedList::getNext(struct Node* current) const
{
    if (current == nullptr) {
        return nullptr;
    }
    return (current->next);
}

Node* DoublyLinkedList::getPrev(struct Node* current) const
{
    if (current == nullptr) {
        return nullptr;
    }
    return (current->prev);
}

Node* DoublyLinkedList::addNext(struct Node* current, PointerPlayer newData)
{
    if (current == nullptr) {
        if (current == head) {
            struct Node* newNode = new struct Node();
            newNode->data = newData;
            newNode->next = nullptr;
            newNode->prev = nullptr;
            head = newNode;
            return newNode;
        }
        return nullptr;
    }
    struct Node* newNode = new struct Node();
    newNode->data = newData;
    newNode->next = current->next;
    newNode->prev = current;
    current->next = newNode;
    return newNode;
}

Node* DoublyLinkedList::addPrev(struct Node* current, PointerPlayer newData)
{
    if (current == nullptr) {
        if (current == head) {
            struct Node* newNode = new struct Node();
            newNode->data = newData;
            newNode->next = nullptr;
            newNode->prev = nullptr;
            head = newNode;
            return newNode;
        }
    }
    struct Node* newNode = new struct Node();
    newNode->data = newData;
    newNode->prev = current->prev;
    newNode->next = current;
    current->prev = newNode;
    if (current == head) {
        head = current->prev;
    }
    return newNode;
}

void DoublyLinkedList::remove(struct Node *nodeToRemove) {
    if (nodeToRemove == nullptr) {
        return;
    }
    if ((nodeToRemove->prev) != nullptr) {
        (nodeToRemove->prev)->next = nodeToRemove->next;
    }
    else {
        head = nodeToRemove->next;
    }
    if ((nodeToRemove->next) != nullptr) {
        (nodeToRemove->next)->prev = nodeToRemove->prev;
    }
    delete(nodeToRemove);
}

Node* DoublyLinkedList::getHead() const{
    return head;
}
