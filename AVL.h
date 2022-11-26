//
// Created by omerd on 23/11/2022.
//

#ifndef DATASTRUCT1_AVL_H
#define DATASTRUCT1_AVL_H

#include <stdio.h>
#include <algorithm>

template<class Data, class SortingCondition>
class AVL {
public:
    Data data; // Assuming that has: default c'tor.
    int height;
    AVL *left;
    AVL *right;
    AVL *parent;

    AVL();

    bool isEmpty() const;

    void add(Data data1);

    AVL* search(int i);

    int degree();

    AVL* getClosestAndBigger(int i);

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
        if (l)
            l->parent = this;
    }

    void set_right(AVL *r) {
        this->right = r;
        if (r)
            r->parent = this;
    }

    void remove(Data data){
        // in case it's the last one in the tree
        //if (data == this->data && this->parent == nullptr && !this->left && !this->right) {
        if (SortingCondition(data, this->data, SortingCondition::Condition::Equals) && this->parent == nullptr && !this->left &&
                !this->right) {
            this->data = Data();
            return;
        }
        // in case we found the node
        //if (data == this->data){
        if (SortingCondition(data, this->data, SortingCondition::Condition::Equals)()) {
            AVL *p = this->parent;

            if (this->is_leaf()) {
                //if (p->left && p->left->data == data) {
                if (p->left && SortingCondition(p->left->data, data, SortingCondition::Condition::Equals)) {
                    p->left = nullptr;
                } else {
                    p->right = nullptr;
                }
                delete this;
                p->height = p->heightCalc();
                return;
            }
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
                AVL *temp_p = temp->parent;
                //if (temp_p->left &&  == )
                if (temp_p->left &&  SortingCondition(temp_p->left->data, temp->data, SortingCondition::Condition::Equals)) {
                    temp_p->set_left(temp->right);
                }
                else {
                    temp_p->set_right(temp->right);
                }

                delete temp;
                temp_p->height = temp_p->heightCalc();
                temp_p->rotate_recursive();
            }
        }
        else {
            //if (data < this->data) {
            if (SortingCondition(this->data, data, SortingCondition::Condition::GreaterThan)) {
                if (this->left)
                    this->left->remove(data);
                else
                    throw std::exception();
            //} else if (data > this->data) {
            } else if (SortingCondition(data, this->data, SortingCondition::Condition::GreaterThan)) {
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

            //if (B->parent->left && B->parent->left->data == B->data)
            if (B->parent->left && SortingCondition(B->parent->left->data, B->data, SortingCondition::Condition::Equals))
            {
                B->parent->left = A;
            }
            else {
                B->parent->right = A;
            }
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
            if (B->right)
                B->right->parent = A;
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
            //if (A->parent->left && A->parent->left->data == A->data)
            if (A->parent->left && SortingCondition(A->parent->left->data, A->data, SortingCondition::Condition::Equals)) {
                A->parent->left = B;
            }
            else {
                A->parent->right = B;
            }
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
            return nullptr;
        }
        if (this->right == nullptr) {
            return this;
        }
        return (this->right)->getMostRight();
    }

    AVL* treeToArray(int elementsNum)
    {
        AVL* arr = malloc(sizeOf(*this)*elementsNum);
        int i = 0;
        AVL *currentP = this, *fatherP = this;
        while (i < elementsNum) {
            while (currentP != nullptr && currentP->left != nullptr) {
                fatherP = currentP;
                currentP = currentP->left;
            }
            arr[i] = currentP;
            i++;
            if (currentP == fatherP->left) {
                arr[i] = fatherP;
                i++;
                currentP = fatherP->right;
            }
            else {
                currentP = fatherP;
                fatherP = fatherP->father;
            }
        }
    }

    AVL* buildCompleteTree(AVL* tree, int height, AVL* parent)
    {
        if (height < 0) {
            return nullptr;
        }
        this = AVL();
        this->height = height;
        this->father = parent;
        this->left = buildCompleteTree(tree->left, height- 1);
        this->right = buildCompleteTree(tree->right, height- 1);
        return this;
    }

    AVL* arrayTotree(AVL* tree, AVL* arr, int elementsNum)
    {
        if (elementsNum == 0) {
            tree->data = Data();
            tree->left = nullptr;
            tree->right = nullptr;
            tree->father = nullptr;
            return this;
        }
        //finding the hight of the smallest complete tree that is bigger than the required tree.
        int height = 0, completeTreeElemNum = 1, elemToRemoveNum, i = 0, j = 0;
        AVL *currentP = this, *fatherP = nullptr;
        while (completeTreeElemNum < elementsNum){
            completeTreeElemNum += 2*completeTreeElemNum;
            height++;
        }
        tree = buildCompleteTree(tree, height, nullptr);
        elemToRemoveNum = completeTreeElemNum - elementsNum;
        while (i < elemToRemoveNum) {
            while (currentP != nullptr && currentP->right != nullptr) {
                fatherP = currentP;
                currentP = currentP->right;
            }
            fatherP->right = nullptr;
            i++;
            if (currentP == fatherP->right) {
                currentP = fatherP->left;
            }
            else {
                currentP = fatherP;
                fatherP = fatherP->father;
            }
        }
        while (j < elementsNum) {
            while (currentP != nullptr && currentP->left != nullptr) {
                fatherP = currentP;
                currentP = currentP->left;
            }
            this->data = arr[j]->data;
            j++;
            if (currentP == fatherP->left) {
                fatherP->data = arr[j]->data;
                j++;
                currentP = fatherP->right;
            }
            else {
                currentP = fatherP;
                fatherP = fatherP->father;
            }
        }
        delete(arr);
        return tree;
    }

    AVL* merge(AVL* a, int na, AVL* b, int nb) {
        AVL* c = malloc(sizeof(AVL)*(na+nb));
        int ia, ib, ic;
        for(ia = ib = ic = 0; (ia < na) && (ib < nb); ic++)
        {
            if(a[ia] < b[ib]) {
                c[ic] = a[ia];
                ia++;
            }
            else {
                c[ic] = b[ib];
                ib++;
            }
        }
        for(;ia < na; ia++, ic++) c[ic] = a[ia];
        for(;ib < nb; ib++, ic++) c[ic] = b[ib];
        return c;
    }

    AVL* uniteTrees(AVL* tree1, int elementsNum1, AVL* tree2, int elementsNum2)
    {
        AVL* arr1 = tree1->treeToArray(elementsNum1);
        AVL* arr2 = tree2->treeToArray(elementsNum2);
        AVL* mergedArr = merge(arr1, elementsNum1, arr2, elementsNum2);
        AVL* newTree = AVL();
        return arrayTotree(newTree, mergedArr, (elementsNum1 + elementsNum2));
    }

    template <class Func>
    void updateInorder(Func f, int elementsNum)
    {
        AVL* currentP = this, fatherP = nullptr;
        int j = 0;
        while (j < elementsNum) {
            while (currentP != nullptr && currentP->left != nullptr) {
                fatherP = currentP;
                currentP = currentP->left;
            }
            f(currentP);
            j++;
            if (currentP == fatherP->left) {
                f(fatherP);
                j++;
                currentP = fatherP->right;
            }
            else {
                currentP = fatherP;
                fatherP = fatherP->father;
            }
        }
    }
};

template<class Data, class SortingCondition>
AVL<Data, SortingCondition>::AVL() : data(), height(NULL), left(nullptr), right(nullptr), parent(nullptr) {}

template<class Data, class SortingCondition>
bool AVL<Data, SortingCondition>::isEmpty() const{
    return (SortingCondition(data, Data(), SortingCondition::Condition::Equals));
}

template<class Data, class SortingCondition>
void AVL<Data, SortingCondition>::add(Data data1) {
    if (SortingCondition(this->data, Data(),SortingCondition::Condition::Equals)) {
        this->data = data1;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        return;
    }
    if (Condition(data1, this->data, SortingCondition::Condition::Equals)) {
        return;
    }
    if (SortingCondition(this->data, data1, SortingCondition::Condition::GreaterThan)) {
        if (!this->left) {
            this->left = new AVL();
            this->left->data = data1;
            this->left->parent = this;
            this->left->height = 0;
        }
        else {
            this->height = this->left->heightCalc() + 1;
            this->left->add(data1);
        }
    } else {
        if (!this->right) {
            this->right = new AVL();
            this->right->data = data1;
            this->right->parent = this;
            this->right->height = 0;
        } else {
            this->height = this->right->heightCalc() + 1;
            this->right->add(data1);
        }
    }
    this->rotate();
}

template<class Data, class SortingCondition>
AVL<Data, SortingCondition>* AVL<Data, SortingCondition>::search(int i)
{
    struct AVL* current = this;
    while (current != nullptr){
        //if(current->data == i){
        if(SortingCondition(current->data, i,SortingCondition::Condition::Equals)) {
            return current;
        }
            //else if (current->data > i) {
        else if (SortingCondition(current->data, i, SortingCondition::Condition::GreaterThan)) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return nullptr;
}

template<class Data, class SortingCondition>
int AVL<Data, SortingCondition>::degree() {
    if ((this->left != nullptr) && (this->right != nullptr)) {
        return 2;
    }
    if ((this->left == nullptr) && (this->right == nullptr)) {
        return 0;
    }
    return 1;
}

template<class Data, class SortingCondition>
AVL<Data, SortingCondition>* AVL<Data, SortingCondition>::getClosestAndBigger(int i){
    AVL* a = search(i);
    if(a != nullptr) {
        return a;
    }
    Data d = Data(i);
    add(d);
    a = search(i);
    AVL* current = a;
    while(true){
        if(!current->parent){
            remove(d);
            return nullptr;
        }
        if(current == current->parent->right){
            current = current->parent;
        }
        remove(d);
        return current->parent;
    }
}






#endif //DATASTRUCT1_AVL_H