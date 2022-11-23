//
// Created by mayan on 23-Nov-22.
//

#ifndef MIVNY1_DOUBLYLINKEDLIST_H
#define MIVNY1_DOUBLYLINKEDLIST_H

#include "PointerPlayer.h"

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

#endif //MIVNY1_DOUBLYLINKEDLIST_H