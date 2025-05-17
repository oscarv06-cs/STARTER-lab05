// card_list.cpp
// Author: Oscar Valeriano
// Implementation of the classes defined in card_list.h
#include "card_list.h"
#include "card.h"
#include <iostream>
using namespace std;
bst::bst() : root(nullptr) {}

bst::~bst() {
    deleteTree(root);
}

void bst::deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

void bst::insert(const Card& card) {
    insertHelper(root, card, nullptr);
}

void bst::insertHelper(Node*& curr, const Card& card, Node* parent) {
    if (!curr) {
        curr = new Node(card, parent);
        return;
    }
    if (card < curr->card) insertHelper(curr->left, card, curr);
    else if (card > curr->card) insertHelper(curr->right, card, curr);
    // duplicates are ignored
}

bool bst::contains(const Card& card) const {
    return findNode(root, card) != nullptr;
}

bst::Node* bst::findNode(Node* curr, const Card& card) const {
    if (!curr) return nullptr;
    if (card == curr->card) return curr;
    if (card < curr->card) return findNode(curr->left, card);
    else return findNode(curr->right, card);
}

void bst::remove(const Card& card) {
    removeNode(root, card);
}

void bst::removeNode(Node*& curr, const Card& card) {
    if (!curr) return;
    if (card < curr->card) removeNode(curr->left, card);
    else if (card > curr->card) removeNode(curr->right, card);
    else {
        if (!curr->left && !curr->right) {
            delete curr;
            curr = nullptr;
        } else if (!curr->left || !curr->right) {
            Node* temp = curr->left ? curr->left : curr->right;
            temp->parent = curr->parent;
            delete curr;
            curr = temp;
        } else {
            Node* succ = getMin(curr->right);
            curr->card = succ->card;
            removeNode(curr->right, succ->card);
        }
    }
}

void bst::printDeck() const {
    printInOrder(root);
    cout << endl;
}

void bst::printInOrder(Node* node) const {
    if (!node) return;
    printInOrder(node->left);
    cout << node->card.toString() << endl;
    printInOrder(node->right);
}

bst::Node* bst::getMin(Node* node) const {
    while (node && node->left) node = node->left;
    return node;
}

bst::Node* bst::getMax(Node* node) const {
    while (node && node->right) node = node->right;
    return node;
}

bst::Node* bst::getSuccessor(Node* node) const {
    if (node->right) return getMin(node->right);
    Node* p = node->parent;
    while (p && node == p->right) {
        node = p;
        p = p->parent;
    }
    return p;
}

bst::Node* bst::getPredecessor(Node* node) const {
    if (node->left) return getMax(node->left);
    Node* p = node->parent;
    while (p && node == p->left) {
        node = p;
        p = p->parent;
    }
    return p;
}

bst::Iterator bst::begin() const {
    return Iterator(getMin(root), this);
}

bst::Iterator bst::end() const {
    return Iterator(nullptr, this);
}

bst::Iterator bst::rbegin() const {
    return Iterator(getMax(root), this);
}

bst::Iterator bst::rend() const {
    return Iterator(nullptr, this);
}


bst::Iterator& bst::Iterator::operator++() {
    curr = tree->getSuccessor(curr);
    return *this;
}

bst::Iterator& bst::Iterator::operator--() {
    curr = tree->getPredecessor(curr);
    return *this;
}

void playGame(bst& alice, bst& bob) {
    bool matchFound = true;
    
    while (matchFound) {
        matchFound = false;
        for (auto it = alice.begin(); it != alice.end(); ++it) {
            if (bob.contains(*it)) {
                cout << "Alice picked matching card " << *it << endl;
                alice.remove(*it);
                bob.remove(*it);
                matchFound = true;
                break;
            }
        }
        for (auto it = bob.rbegin(); it != bob.rend(); --it) {
            if (alice.contains(*it)) {
                cout << "Bob picked matching card " << *it << endl;
                alice.remove(*it);
                bob.remove(*it);
                matchFound = true;
                break; 
            }
        }
    }
    cout << "Alice's cards:" << endl;
    alice.printDeck();
    cout << "Bob's cards:" << endl;
    bob.printDeck();
}

