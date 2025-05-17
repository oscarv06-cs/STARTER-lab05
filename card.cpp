// card.cpp
// Author: Oscar Valeriano
// Implementation of the classes defined in card.h
// card.cpp
#include "card.h"
#include <ostream>
#include <string>
#include <algorithm>

Card::Card(char s, const std::string& v)
  : suit(s), value(v) {}

char Card::getSuit() const {
    return suit;
}

std::string Card::getValue() const {
    return value;
}

// Comparison operators
bool Card::operator==(const Card& o) const {
    return suit == o.suit && value == o.value;
}

bool Card::operator<(const Card& o) const {
    static const std::string suitOrder = "cdsh";
    auto s1 = suitOrder.find(suit);
    auto s2 = suitOrder.find(o.suit);
    if (s1 != s2) return s1 < s2;

    static const std::string valOrder[] = {
      "a","2","3","4","5","6","7","8","9","10","j","q","k"
    };
    auto i1 = std::find(std::begin(valOrder), std::end(valOrder), value);
    auto i2 = std::find(std::begin(valOrder), std::end(valOrder), o.value);
    return i1 < i2;
}

bool Card::operator>(const Card& o) const {
    return o < *this;
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.getSuit() << " " << card.getValue();
    return os;
}
