// Oscar Valeriano
// Implements the game using std::set and Card class (no custom BST)
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

    // Reads Alice's hand
    while (getline(cardFile1, line) && (line.length() > 0)) {
        istringstream iss(line);
        char suit; // creates suit ase a char val
        string value;
        iss >> suit >> value;
        alice.insert(Card(suit, value));
    }
    cardFile1.close();

    // Reads Bob's hand
    while (getline(cardFile2, line) && (line.length() > 0)) {
        istringstream iss(line);
        char suit; // creates suit ase a char val
        string value;
        iss >> suit >> value;
        bob.insert(Card(suit, value));
    }
    cardFile2.close();

    bool match = true; 
    while (match) { //tries to find matches
        match = false;

        // Alice's turn (smallest up)
        for (auto it = alice.begin(); it != alice.end(); ) {
            if (bob.find(*it) != bob.end()) {
                cout << "Alice picked matching card " << *it << endl;
                bob.erase(*it);
                it = alice.erase(it);
                match = true;
                break;
            } else {
                ++it;
            }
        }

        // Bob's turn (largest down)
        for (auto it = bob.rbegin(); it != bob.rend(); ) {
            if (alice.find(*it) != alice.end()) {
                cout << "Bob picked matching card " << *it << endl;
                alice.erase(*it);
                bob.erase(next(it).base());
                match = true;
                break;
            } else {
                ++it;
            }
        }
    }
    // prints alice's cards
    cout << "\nAlice's cards:" << endl;
    for (const auto& elem : alice) {
        cout << elem << endl;
    }
    // prints bob's cards
    cout << "\nBob's cards:" << endl;
    for (const auto& elem : bob) {
        cout << elem << endl;
    }

    return 0;
}