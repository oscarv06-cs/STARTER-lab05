// card.h
// Author: Oscar Valeriano
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H
#include <string>
#include <iostream>

class Card{
private:
    char suit;
    std::string value;
public:
    Card(char s, std::string v);
    std::string getValue() const;
    char getSuit() const;
    bool operator<(const Card& other) const;
    bool operator==(const Card& other) const;
    bool operator>(const Card& other) const; 
    std::string toString() const;


    friend std::ostream& operator<<(std::ostream& out, const Card& card);
    
};


#endif
