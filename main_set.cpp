// Feb 14: This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

int main(int argc, char* argv[]) {
  if(argc < 3) {
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


  set<Card> alice;
  set<Card> bob;

  //Read each file
  while (getline(cardFile1, line) && (line.length() > 0)) {
    Suit suit;
    string value;

    istringstream iss(line);
    char temp;
    iss >> temp >> value;

    if(temp == 'c') {suit = clubs;}
    else if (temp == 'd') {suit = diamonds;}
    else if(temp == 's') {suit = spades;}
    else{suit = hearts;}

    alice.insert(Card(suit, value));

  }

  cardFile1.close();

  while (getline(cardFile2, line) && (line.length() > 0)) {
    Suit suit;
    string value;

    istringstream iss(line);
    char temp;
    iss >> temp >> value;

    if(temp == 'c') {suit = clubs;}
    else if (temp == 'd') {suit = diamonds;}
    else if(temp == 's') {suit = spades;}
    else{suit = hearts;}

    bob.insert(Card(suit, value));
  }

  cardFile2.close();

  bool match = true;
  while(match){
    match = false;

    for(auto it = alice.begin(); it != alice.end();){

      if(bob.find(*it) != bob.end()){
        cout << "Alice picked matching card " << *it << endl;

        bob.erase(*it);
        it = alice.erase(it);

        match = true;
        break;
      }
      else{
        it++;
      }
      
    }

    for(auto it = bob.rbegin(); it != bob.rend();){

      if(alice.find(*it) != alice.end()){
        cout << "Bob picked matching card " << *it << endl;

        alice.erase(*it);
        bob.erase(next(it).base());

        match = true;
        break;
      }
      else{
        it++;
      }
      
    }
  }

  
  char type;

  cout << "\nAlice's cards: " << endl;
  for(auto elem : alice){
    if(elem.getSuit() == 0){
      type = 'c';
    }else if(elem.getSuit() == 1){
      type = 'd';
    }else if(elem.getSuit() == 2){
      type = 's';
    }else{
      type = 'h';
    }
    cout << type << " " << elem.getValue() << endl;
    
  }

  cout << "\nBob's cards: " << endl;
  for(auto elem : bob){
    if(elem.getSuit() == 0){
      type = 'c';
    }else if(elem.getSuit() == 1){
      type = 'd';
    }else if(elem.getSuit() == 2){
      type = 's';
    }else{
      type = 'h';
    }
    cout << type << " " << elem.getValue() << endl;
  }
  return 0;
}
