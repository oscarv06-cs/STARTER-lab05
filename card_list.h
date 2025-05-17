// card_list.h
// card_list.h
#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"
#include <iostream>

class CardList {
private:
    struct Node {
        Card card;
        Node* left;
        Node* right;
        Node* parent;
        Node(const Card& c, Node* p = nullptr)
          : card(c), left(nullptr), right(nullptr), parent(p) {}
    };
    Node* root;

    // … all your private helpers here …

public:
    CardList();
    ~CardList();

    bool insert(const Card& c);
    bool find(const Card& c) const;
    bool remove(const Card& c);

    const Card* minValue() const;
    const Card* maxValue() const;
    const Card* successor(const Card& c) const;
    const Card* predecessor(const Card& c) const;

    void printInOrder() const;
};

#endif // CARD_LIST_H
