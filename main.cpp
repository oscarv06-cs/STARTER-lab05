#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "card.h"
#include "card_list.h"
// Do not include set in this file

using namespace std;

int main(int argc, char* argv[]) {
  if(argc < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  ifstream cardFile1(argv[1]);
  ifstream cardFile2(argv[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail()) {
    cout << "Could not open file " << argv[2];
    return 1;
  }

  CardList alice;
  CardList bob;
  
  //Read each file
  while (getline(cardFile1, line) && (line.length() > 0)) {
    Suit suit;
    string value;

    istringstream iss(line);
    char temp;
    iss >> temp >> value;

    if(temp == 'c') {suit = Suit::clubs;}
    else if (temp == 'd') {suit = Suit::diamonds;}
    else if(temp == 's') {suit = Suit::spades;}
    else{suit = Suit::hearts;}

    alice.insert(Card(suit, value));
  }

  cardFile1.close();


  while (getline(cardFile2, line) && (line.length() > 0)) {
    Suit suit;
    string value;

    istringstream iss(line);
    char temp;
    iss >> temp >> value;

    if(temp == 'c') {suit = Suit::clubs;}
    else if (temp == 'd') {suit = Suit::diamonds;}
    else if(temp == 's') {suit = Suit::spades;}
    else{suit = Suit::hearts;}

    bob.insert(Card(suit, value));

  }

  cardFile2.close();

  bool match = true;
  while(match){
    match = false;

    const Card* a = alice.minValue();
    while(a){
      if(bob.find(*a)){
        cout << "Alice picked matching card " << *a << endl;
        bob.remove(*a);
        alice.remove(*a);

        match = true;
        break;
      }
      a = alice.successor(*a);
    }

    const Card* b = bob.maxValue();
    while(b){
      if(alice.find(*b)){
        cout << "Bob picked matching card " << *b << endl;
        alice.remove(*b);
        bob.remove(*b);

        match = true;
        break;
      }
      b = bob.predecessor(*b);
    }
  }

  cout << "\nAlice's cards: " << endl;
  alice.printInOrder();
  cout << endl;    
  
  cout << "Bob's cards: " << endl;
  bob.printInOrder();

  return 0; 
}
