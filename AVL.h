//
// Created by omerd on 23/11/2022.
//

#ifndef DATASTRUCT1_AVL_H
#define DATASTRUCT1_AVL_H

#include <stdio.h>
#include <algorithm>

template<class Data>
class AVL {
public:
    Data data;
    int height;
    AVL* left;
    AVL* right;
    AVL* parent;

    AVL() : data(), height(0), left(nullptr), right(nullptr), parent(nullptr) {}

    bool isEmpty() const{
        return data == Data();
    }


    void add(Data data) {
        if (this->data == Data()) {
            this->data = data;
            this->parent = nullptr;
            this->left = nullptr;//
            this->right = nullptr;//
            return;
        }
        if (data == this->data)
            return;
        if (data < this->data) {
            if (!this->left) {
                this->left = new AVL();
                this->left->data = data;
                this->left->parent = this;
                this->left->height = 0;
            }
            else {
                this->height = this->left->heightCalc() + 1;
                this->left->add(data);
            }
        } else {
            if (!this->right) {
                this->right = new AVL();
                this->right->data = data;
                this->right->parent = this; //
                this->right->height = 0;
            } else {
                this->height = this->right->heightCalc() + 1;
                this->right->add(data);
            }
        }
        this->rotate();
    }

    AVL* search(int i)
    {
        struct AVL* current = this;
        while (current != nullptr){
            if(current->data == i){
                return current;
            }
            else if (current->data > i) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return nullptr;
    }
    int degree() {
        if ((this->left != nullptr) && (this->right != nullptr)) {
            return 2;
        }
        if ((this->left == nullptr) && (this->right == nullptr)) {
            return 0;
        }
        return 1;
    }

    int heightCalc() {
        if (degree() == -1)
            return -1;
        else if (degree() == 0)
            return 0;
        else if (degree() == 1) {
            if (this->left != nullptr) {
                return this->left->height + 1;
            }
            return this->right->height + 1;
        }
        return std::max(this->left->height + 1, this->right->height + 1);
    }



    void set_left(AVL *l) {
        this->left = l;
        if (l) l->parent = this;
    }

    void set_right(AVL *l) {
        this->right = l;
        if (l) l->parent = this;
    }

    void remove(Data data){
        // in case it's the last one in the tree
        if (data == this->data && this->parent == nullptr && !this->left && !this->right) {
            this->data = Data();
            return;
        }
        // in case we found the node
        if (data == this->data){
            AVL *p = this->parent;

            if (this->is_leaf()) {
                if (p->left && p->left->data == data) {
                    p->left = nullptr;
                } else {
                    p->right = nullptr;
                }
                delete this;
                p->height = p->heightCalc();
                return;
            }

            // if node has only left son swap him and delete the left son
            if (!this->right) {
                this->swapData(this->left);
                delete this->left;
                this->left = nullptr;
                this->height = heightCalc();
            }
            else {
                AVL *temp = this->right;
                while (temp->left) temp = temp->left;
                this->swapData(temp);

                // remove parent pointer to temp
                AVL *temp_p = temp->parent;
                if (temp_p->left && temp_p->left->data == temp->data)
                    temp_p->set_left(temp->right);
                else
                    temp_p->set_right(temp->right);

                delete temp;
                temp_p->height = temp_p->heightCalc();
                temp_p->rotate_recursive();
            }
        }
        else {
            if (data < this->data) {
                if (this->left)
                    this->left->remove(data);
                else
                    throw std::exception();
            } else if (data > this->data) {
                if (this->right)
                    this->right->remove(data);
                else
                    throw std::exception();
            }
            this->rotate();
        }

    }




    bool is_leaf() {
        return !left && !right;
    }

    void free_tree() {
        if (left) left->free_tree();
        if (right) right->free_tree();
        delete this;
    }

    void delete_tree() {
        if (left) left->delete_tree();
        if (right) right->delete_tree();
        delete this;
    }

    int BF(){
        int n1, n2;
        if(this->left == nullptr){
            n1 = -1;
        }
        else{
            n1 = this->left->height;
        }
        if(this->right == nullptr){
            n2 = -1;
        }
        else{
            n2 = this->right->height;
        }
        return n1 - n2;
    }

    void rotate() {
        this->height = heightCalc();
        if (abs(this->BF()) <= 1) return;

        if (this->BF() == 2) {
            if (this->left->BF() >= 0)
                LL();
            else
                LR();
        } else {
            if (this->right->BF() <= 0)
                RR();
            else
                RL();
        }
    }

    void rotate_recursive() {
        this->rotate();
        if (this->parent)
            this->parent->rotate_recursive();
    }

    void swapData(AVL *B) {
        Data temp = this->data;
        this->data = B->data;
        B->data = temp;
    }

    void LL() {
        AVL *B = this, *A = B->left;
        if (B->parent) {
            B->left = A->right;
            if (B->left)
                B->left->parent = B;

            if (B->parent->left && B->parent->left->data == B->data)
                B->parent->left = A;
            else
                B->parent->right = A;
            A->parent = B->parent;

            A->right = B;
            B->parent = A;

            B->heightCalc();
            A->heightCalc();

        } else {
            B->left = A->left;
            A->left->parent = B;

            A->left = A->right;


            A->right = B->right;
            if (B->right) B->right->parent = A;


            B->right = A;

            A->swapData(B);
            B->parent = nullptr;
            A->parent = B;

            A->heightCalc();
            B->heightCalc();
        }


    }



    void RR() {
        AVL *A = this, *B = A->right;
        if (A->parent) {
            A->right = B->left;
            if (B->left)
                B->left->parent = A;
            if (A->parent->left && A->parent->left->data == A->data)
                A->parent->left = B;
            else
                A->parent->right = B;
            B->parent = A->parent;
            B->left = A;
            A->parent = B;
            A->heightCalc();
            B->heightCalc();
        }
        else {
            A->set_right(B->right);
            B->right = B->left;
            B->left = A->left;
            if (A->left)
                A->left->parent = B;
            A->left = B;
            A->swapData(B);
            A->parent = nullptr;
            B->parent = A;
            B->heightCalc();
            A->heightCalc();
        }

    }

    void LR() {
        this->left->RR();
        LL();
    }

    void RL() {
        this->right->LL();
        RR();
    }

    AVL* getMostRight() const
    {
        if (this == nullptr) {
            return nulptr;
        }
        if (this->right == nullptr) {
            return this;
        }
        return (this->right)->getMostRight();
    }
};

#endif //DATASTRUCT1_AVL_H

