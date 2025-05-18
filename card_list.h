#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"
#include <iostream>

class bst {
public:
    struct Node {
        Card card;
        Node* left;
        Node* right;
        Node* parent;
        Node(const Card& c, Node* p = nullptr)
          : card(c), left(nullptr), right(nullptr), parent(p) {}
          
        
    };
    // Iterator class declaration
    class Iterator {
        Node* current;
        const bst* tree;
    public:
        Iterator(Node* n = nullptr, const bst* t = nullptr);
        Iterator& operator++();
        Iterator& operator--();
        const Card& operator*() const;
        const Card* operator->() const;
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
    };
    bst();
    ~bst();
    bool insert(const Card& c);
    bool contains(const Card& c) const;
    bool remove(const Card& c);
    const Card* minValue() const;
    const Card* maxValue() const;
    const Card* successor(const Card& c) const;
    const Card* predecessor(const Card& c) const;
    bool find(const Card& c) const;
    void printInOrder() const;  
    

    // Iterator methods
    Iterator begin() const;
    Iterator end() const;
    Iterator rbegin() const;
    Iterator rend() const;
    void printDeck(std::ostream& out = std::cout) const;
private:
    Node* root;
};

#endif