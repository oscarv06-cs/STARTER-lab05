// card.cpp
// Author: Oscar Valeriano
// Implementation of the classes defined in card.h
#include "card.h"
#include <ostream>

char Card:: getSuit() const{
    return suit;
}

std::string Card:: getValue() const{
    return value;
}

Card::Card(char s, std::string v) {
    value = v;
    suit = s;
}

bool Card:: operator<(const Card& other) const{
    std::string suitOrder = "cdsh";
    int thisSuit = suitOrder.find(this->suit);
    int otherSuit = suitOrder.find(other.suit);

    if (thisSuit != otherSuit){
        return thisSuit < otherSuit;
    }
    std::string valOrder[] = {"a", "2", "3", "4", "5", "6", "7", "8", "9", "10", "j", "q", "k"};
    int thisVal = 0;
    int otherVal = 0;

    for (int i = 0; i < 13; i++){
        if (valOrder[i] == this->value){
            thisVal = i;
        }
        if (valOrder[i] == other.value){
            otherVal = i;
        }
    }
    return thisVal < otherVal;
}


std::ostream& operator<<(std::ostream& out, const Card& card){
    out << card.getSuit() << " " << card.getValue();
    return out;
}

bool Card::operator==(const Card& other) const {
    return this->suit == other.suit && this->value == other.value;
}

bool Card::operator>(const Card& other) const {
    return other < *this;
}

std::string Card::toString() const {
    return std::string(1, suit) + " " + value;
}
