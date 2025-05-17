// card.h
// Author: Oscar Valeriano
// All class declarations related to defining a single card go here
// card.h
#ifndef CARD_H
#define CARD_H

#include <string>
#include <ostream>

class Card {
private:
    char suit;
    std::string value;
public:
    Card(char s, const std::string& v);
    char getSuit() const;
    std::string getValue() const;
    bool operator<(const Card& other) const;
    bool operator==(const Card& other) const;
    bool operator>(const Card& other) const;
    std::string toString() const;
    friend std::ostream& operator<<(std::ostream& out, const Card& c);
};

#endif // CARD_H
