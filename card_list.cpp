// card_list.cpp
// Author: Oscar Valeriano
// Implementation of the classes defined in card_list.h
#include "card_list.h"
#include "card.h"
#include <string>
#include <iostream>
using namespace std;
bst::bst(){
    root = nullptr;
}
bst::~bst(){
    clear(root);
}

void bst::clear(Node* n){
    if(!n){
        return;
    }else{
        clear(n->left);
        clear(n->right);
        delete n;
    }
}

bool bst::insert(const Card& card) {
    if(!root){
        root = new Node(card);
        return true;
    }
    return insert(root, card) != nullptr;
}

bst::Node* bst::insert(Node* n, const Card& card) {
    if(!n) {return new Node(card);}
    if(card < n->card){
        Node* temp = insert(n->left, card);
        n->left = temp;
        temp->parent = n;
    }
    else{
        Node* temp = insert(n->right, card);
        n->right = temp;
        temp->parent = n;
    }
    return n;
}

bool bst::find(const Card& card) const{
    return find(root, card) != nullptr;
}

bst::Node* bst::find(Node* n, const Card& card) const{
    if(!n) {return nullptr;}
    if(n->card == card){
        return n;
    }
    else if(card < n->card){
        return find(n->left, card);
    }
    else{
        return find(n->right, card);
    }
}

bool bst::remove(const Card& card){
    if(!root || !find(card)){
        return false;
    }
    root = removeNode(root, card);
    return true;
}

bst::Node* bst::removeNode(Node* n, const Card& card){
    if(!n) {return nullptr;}
    if(card < n->card){
        n->left = removeNode(n->left, card);
    }else if(card > n->card){
        n->right = removeNode(n->right, card);
    }else{
        if(!n->left){
            Node* temp = n->right;
            if(temp){
                temp->parent = n->parent;
            }
            delete n;
            return temp;
        }
        else if(!n->right){
            Node* temp = n->left;
            if(temp){
                temp->parent = n->parent;
            }
            delete n;
            return temp;
        }else{
            Node* temp = minValueNode(n->right);
            n->card = temp->card;
            n->right = removeNode(n->right, temp->card);
        }
    }
    return n;
}
const Card* bst::minValue() const{
    Node* n = minValueNode(root);
    if(n != nullptr){
        return &n->card;
    }
    else{
        return nullptr;
    }
}
bst::Node* bst::minValueNode(Node* n) const{
    while(n && n->left){
        n = n->left;
    }
    return n;
}
const Card* bst::maxValue() const{
    Node* n = maxValueNode(root);
    if(n != nullptr){
        return &n->card;
    }
    else{
        return nullptr;
    }
}
bst::Node* bst::maxValueNode(Node* n) const{
    while(n && n->right){
        n = n->right;
    }
    return n;
}
const Card* bst::successor(const Card& card) const {
    Node* n = find(root, card);
    if(!n) {return nullptr;}
    Node* temp = successorNode(n);
    if(temp != nullptr){
        return &temp->card;
    }else{
        return nullptr;
    }
}
bst::Node* bst::successorNode(Node* n) const {
    if(n->right){
        return minValueNode(n->right);
    }
    Node* temp = n->parent;
    while(temp && n == temp->right){
        n = temp;
        temp = temp->parent;
    }
    return temp;
}
const Card* bst::predecessor(const Card& card) const {
    Node* n = find(root, card);
    if(!n) {return nullptr;}
    Node* temp = predecessorNode(n);
    if(temp != nullptr){
        return &temp->card;
    }else{
        return nullptr;
    }
}
bst::Node* bst::predecessorNode(Node* n) const {
    if(n->left){
        return maxValueNode(n->left);
    }
    Node* temp = n->parent;
    while(temp && n == temp->left){
        n = temp;
        temp = temp->parent;
    }
    return temp;
}
void bst::printInOrder() const {
    printInOrder(root);
}
void bst::printInOrder(Node* n) const {
    if(n) {
        printInOrder(n->left);
        cout << n->card << endl;
        printInOrder(n->right);
    }
}