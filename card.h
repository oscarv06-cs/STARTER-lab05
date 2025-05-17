// card.h
// Author: Oscar Valeriano
// All class declarations related to defining a single card go here
#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"

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

    //  helpers
    Node* insert(Node* n, const Card& card);
    Node* find(Node* n, const Card& card) const;
    Node* removeNode(Node* n, const Card& card);
    void clear(Node* n);
    Node* minValueNode(Node* n) const;
    Node* maxValueNode(Node* n) const;
    Node* successorNode(Node* n) const;
    Node* predecessorNode(Node* n) const;
    void printInOrder(Node* n) const;

public:
    CardList();
    ~CardList();

    bool insert(const Card& card);
    bool find(const Card& card) const;
    bool remove(const Card& card);

    const Card* minValue() const;
    const Card* maxValue() const;
    const Card* successor(const Card& card) const;
    const Card* predecessor(const Card& card) const;

    void printInOrder() const;
};

#endif // CARD_LIST_H
