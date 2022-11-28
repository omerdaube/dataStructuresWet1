//
// Created by omerd on 23/11/2022.
//

#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <math.h>
#include <algorithm>
using std::max;

template<class Data, class Cond>
class AVL {

private:
    Data nodeData;
    int nodeHeight;
    AVL* left;
    AVL* right;
    AVL* father;
public:
    AVL() : nodeData(), nodeHeight(0), left(nullptr), right(nullptr), father(nullptr) {}
    AVL(Data d, AVL* f) : nodeData(d), nodeHeight(0), left(nullptr), right(nullptr), father(f) {}
    AVL(AVL* me) : nodeData(me->nodeData), nodeHeight(me->nodeHeight), left(me->left), right(me->right), father(me->father) {}

    ~AVL() = default; //V

    void deleteAll() {
        if(!this)
            return;
        if (left) {
            left->deleteAll();
            delete left;
        }
        if (right) {
            right->deleteAll();
            delete right;
        }
        //delete this;
    }

    AVL* getLeft(){
        return this->left;
    } //v

    AVL* getRight(){
        return this->right;
    } //v

    Data getData(){
        return this->nodeData;
    } //v

    void add(Data data) {
        if (this->nodeData == NULL){
            this->nodeData = data;
            return;
        }
        if (Cond(data, this->nodeData, 0)()) {
            return;
        }
//        if (Cond(Data(), this->nodeData, 0)()) {
//
//        }
        if (Cond(this->nodeData, data, 1)()) {
            if (!this->left) {
                this->left = new AVL(data, this);
            }
            else {
                this->nodeHeight = this->left->heightCalc() + 1;
                this->left->add(data);
            }
        }
        else {
            if (!this->right) {
                this->right = new AVL(data, this);
            } else {
                this->nodeHeight = this->right->heightCalc() + 1;
                this->right->add(data);
            }
        }
        this->rotate(); //for the whole path
    } //V

    int degree() {
        if ((this->left != nullptr) && (this->right != nullptr)) {
            return 2;
        }
        if ((this->left == nullptr) && (this->right == nullptr)) {
            return 0;
        }
        return 1;
    } //V

    int heightCalc() { //V
        if (degree() == -1)
            return -1;
        else if (degree() == 0)
            return 0;
        else if (degree() == 1) {
            if (this->left != nullptr) {
                return this->left->nodeHeight + 1;
            }
            return this->right->nodeHeight + 1;
        }
        return max(this->left->nodeHeight + 1, this->right->nodeHeight + 1);
    } //v

    void remove(Data data){
        if (Cond(data, this->nodeData, 0)()){
            if(degree() == 0) {
                if(this->father == nullptr){
                    this->nodeData = Data();
                    return;
                }
                if (this->father->left != nullptr && this->father->left == this) {
                    this->father->left = nullptr;
                }
                else {
                    this->father->right = nullptr;
                }
                this->father->nodeHeight = this->father->heightCalc();
                delete this;
                return;
            }
            else if(degree() == 1){
                if (this->right == nullptr) {
                    AVL *tempL = left->left, *tempR = left->right;
                    this->replaceData(this->left);
                    delete left;
                    left = tempL;
                    right = tempR;
                    this->nodeHeight = heightCalc();
                }
                else{
                    AVL *tempL = right->left, *tempR = right->right;
                    this->replaceData(this->right);
                    delete right;
                    left = tempL;
                    right = tempR;
                    this->nodeHeight = heightCalc();
                }
            }
            else { //2 sons
                AVL *next = getNextInorder();
                this->replaceData(next);
                this->right->remove(data); //pass new path
            }
        }
        else if (Cond(this->nodeData, data, 1)() && this->left != nullptr) {
            this->left->remove(data);
        }
        else if (Cond(data, this->nodeData, 1)() && this->right != nullptr){
            this->right->remove(data);
        }
        this->nodeHeight = heightCalc();
        this->rotate(); //for whole path
    } //v

//    void removeFromBinTree(Data data){
//        if(this->degree() == 0){
//            delete this;
//            return;
//        }
//        if(this->degree() == 1){
//            if(this->left != nullptr){
//                if(this->father->right == this){
//                    this->father->right = this->left;
//                    this->left->father = this->father;
//                    delete this;
//                    return;
//                }
//                else{
//                    this->father->left = this->left;
//                    this->left->father = this->father;
//                    delete this;
//                    return;
//                }
//            }
//            else{
//                if(this->father->right == this){
//                    this->father->right = this->right;
//                    this->right->father = this->father;
//                    delete this;
//                    return;
//                }
//                else{
//                    this->father->left = this->right;
//                    this->right->father = this->father;
//                    delete this;
//                    return;
//                }
//            }
//        }
//        AVL* a = this->getNextInorder();
//        replaceData(a);
//        removeFromBinTree(a->nodeData);
//    } //V

    AVL* getNextInorder(){
        AVL* curr = this;
        if(curr->right == nullptr){
            return nullptr;
        }
        curr = curr->right;
        while(curr->left != nullptr){
            curr = curr->left;
        }
        return curr;
    } //V

    int BF(){
        int n1, n2;
        if(this->left == nullptr){
            n1 = -1;
        }
        else{
            n1 = this->left->nodeHeight;
        }
        if(this->right == nullptr){
            n2 = -1;
        }
        else{
            n2 = this->right->nodeHeight;
        }
        return n1 - n2;
    } //V

    void rotate() {
        this->nodeHeight = heightCalc();
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
    } //V

    void replaceData(AVL *toReplace) {
        Data tempData = this->nodeData;
        this->nodeData = toReplace->nodeData;
        toReplace->nodeData = tempData;
    } //V

    void LL() {
        AVL *B = this, *A = B->left;
        if (B->father) {
            B->left = A->right;
            if (B->left) {
                B->left->father = B;
            }
            if (B->father->left && B->father->left == B) { //ch
                B->father->left = A;
            }
            else {
                B->father->right = A;
            }
            A->father = B->father;
            A->right = B;
            B->father = A;
            B->nodeHeight = B->heightCalc();
            A->nodeHeight = A->heightCalc();
        } else {
            B->left = A->left;
            A->left->father = B;
            A->left = A->right;
            A->right = B->right;
            if (B->right) {
                B->right->father = A;
            }
            B->right = A;
            A->replaceData(B);
            B->father = nullptr;
            A->father = B;
            A->nodeHeight = A->heightCalc();
            B->nodeHeight = B->heightCalc();
        }
    }

    void RR() {
        AVL *A = this, *B = this->right;
        if (A->father) {
            A->right = B->left;
            if (B->left)
                B->left->father = A;
            if (A->father->left && A->father->left == A) //
                A->father->left = B;
            else
                A->father->right = B;
            B->father = A->father;
            B->left = A;
            A->father = B;
            A->nodeHeight = A->heightCalc();
            B->nodeHeight = B->heightCalc();
        }
        else {
            A->right = B->right;
            if(B->right){
                B->right->father = A;
            }
            B->right = B->left;
            B->left = A->left;
            if (A->left)
                A->left->father = B;
            A->left = B;
            A->replaceData(B);
            A->father = nullptr;
            B->father = A;
            B->nodeHeight = B->heightCalc();
            A->nodeHeight = A->heightCalc();
        }

    }

    void LR() {
        this->left->RR();
        LL();
    } //V

    void RL() {
        this->right->LL();
        RR();
    } //V

    AVL* getClosestAndBigger(int i){
        AVL* a = search(i);
        if(a != nullptr) {
            return a;
        }
        a = this;
        while(true){
            if(a->nodeData < i){
                if(a->right == nullptr){
                    break;
                }
                a = a->right;
            }
            else{
                if(a->left == nullptr){
                    break;
                }
                a = a->left;
            }
        }
        int j;
        while(true){
            if(!a){
                return nullptr;
            }
            j = a->nodeData;
            if(j < i){
                a = a->father;
                i = a->father->nodeData;
            }
            return a;
        }
    } //need mayan help - c add 4 ->2

    AVL* search(int d)
    {
        struct AVL* current = this;
        while (current != nullptr){
            if(Cond(current->nodeData, d, 0)()) {
                return current;
            }
            else if (Cond(current->nodeData, d, 1)()) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }
        return nullptr;
    } //v

    AVL* getMostRight()
    {
        if (this == nullptr) {
            return nullptr;
        }
        if (this->right == nullptr) {
            return this;
        }
        return (this->right)->getMostRight();
    } //v

    AVL** avlToArr(){
        int n = getSize(this);
        int count = 0;
        int *counter = &count;
        AVL** arr = new AVL*[sizeof(this) * n];
        addToArr(arr, counter);
        return arr;
    }//v

    void addToArr(AVL** arr, int* counter){
        if(this == nullptr)
            return;
        this->left->addToArr(arr, counter);
        AVL* a = new AVL(this);
        arr[*counter] = a;
        *counter += 1;
        this->right->addToArr(arr, counter);
    }//v

    int getSize(AVL* a){
        if(a == nullptr || Cond(a->nodeData, Data(), 0)())
            return 0;
        return getSize(a->left) + getSize(a->right) + 1;
    }//v


    AVL* arrToAvl(AVL** arr,int size){
        this->nodeHeight = ceil(log(size + 1)) - 1;
        this->buildCompleteTree();
        int count = pow(2, nodeHeight + 1) - 1 - size;
        int *counter = &count;
        this->buildNonCompleteTree(counter);
        this->updateHeights();
        int count2 = 0;
        int *counter2 = &count2;
        this->addToTree(arr, counter2);
        return this;
    }
    void updateHeights(){
        if(!this)
            return;
        this->left->updateHeights();
        this->right->updateHeights();
        this->nodeHeight = this->heightCalc();
    }

    void addToTree(AVL** arr, int * counter){
        if(this == nullptr)
            return;
        this->left->addToTree(arr, counter);
        this->nodeData = static_cast<AVL>(*arr[*counter]).nodeData;
        *counter += 1;
        this->right->addToTree(arr, counter);
    }

    void buildNonCompleteTree(int* toRemove){
        if(!this){
            return;
        }
        if(0 < *toRemove && this->nodeHeight == 0){
            *toRemove -= 1;
            if(this->father->right == this)
                this->father->right = nullptr;
            else
                this->father->left = nullptr;
            delete this;
            return;
        }
        this->right->buildNonCompleteTree(toRemove);
        this->left->buildNonCompleteTree(toRemove);
    }

    void buildCompleteTree()
    {
        if (this->nodeHeight <= 0) {
            return;
        }
        this->left = new AVL(Data(), this);
        this->left->nodeHeight = this->nodeHeight - 1;
        this->right = new AVL(Data(), this);
        this->right->nodeHeight = this->nodeHeight - 1;
        this->left->buildCompleteTree();
        this->right->buildCompleteTree();
    }
    bool isEmpty() const{
        return (Cond(nodeData, Data(), 0)());
    }
};

#endif

