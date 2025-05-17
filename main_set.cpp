// Feb 14: This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"
#include <sstream>

/*Std::Set is a container which stroes elements in a sroted order and does not allow duplicates. It automatically keeps data sorted using comparisons like <. This is important
 for the game we're coding. The operations are also fast, insert, delete, and search all have O(logn) time*/
using namespace std;

std::set<Card> alice;
std::set<Card> bob;

int main(int argc, char** argv){
  if(argc < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argv[1]);
  ifstream cardFile2 (argv[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argv[2];
    return 1;
  }

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    stringstream ss(line);
    string suit, value;
    ss >> suit >> value;
    Card card(suit[0], value);
    alice.insert(card);

  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    stringstream ss(line);
    string suit, value;
    ss >> suit >> value;
    Card card(suit[0], value);
    bob.insert(card);

  }
  cardFile2.close();
  bool match_found = true;
  while (match_found != false){ //Check if no matches have been found
    match_found = false;
    //Alice
    for (auto it = alice.begin(); it != alice.end(); ++it) // Iterator to iterate through alice's cards
      if (bob.find(*it) != bob.end()){
        Card match = *it;
        alice.erase(match);
        bob.erase(match);
        match_found = true;
        cout << "\nAlice picked matching card " << match << endl;
        break; //Ends the turn
      }

    for (auto it = bob.rbegin(); it != bob.rend(); ++it) // Iterator to iterate through bob's cards
      if (alice.find(*it) != alice.end()){
      Card match = *it;
      alice.erase(match);
      bob.erase(match);
      match_found = true;
      cout << "\nBob picked matching card " << match << endl;
      break; //Ends the turn
    }
  }
  //Iterates through Alice's set and outputs her remaining cards
  cout << "Alice's cards" << endl;
  for (auto it = alice.begin(); it != alice.end(); ++it){
    cout << *it << endl;
  }
 // Iterates through Bob's set and outputs his remaining cards
  cout << "Bob's cards" << endl;
  for (auto it = bob.rbegin(); it != bob.rend(); ++it){
    cout << *it << endl;
  }
  return 0;
}
