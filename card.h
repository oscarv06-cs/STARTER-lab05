// card.h
// Author: Oscar Valeriano
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

using namespace std;

enum Suit{clubs, diamonds, spades, hearts};

class Card {
 public:
    Card(Suit s, string v);
    bool operator==(const Card& o) const;
    bool operator<(const Card& o) const;
    bool operator>(const Card& o) const;

    Suit getSuit() const;
    string getValue() const;

 private:
    Suit suit;
    string value;
    int getNum() const;

};

std::ostream& operator<<(std::ostream& os, const Card& card);   

#endif
