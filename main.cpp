#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "card.h"
#include "card_list.h"

using namespace std;

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1(argv[1]);
    ifstream cardFile2(argv[2]);
    if (cardFile1.fail() || cardFile2.fail()) {
        cout << "Could not open file " << argv[2] << endl;
        return 1;
    }

    bst alice;
    bst bob;
    string line;

    while (getline(cardFile1, line) && !line.empty()) {
        stringstream ss(line);
        string suit, value;
        ss >> suit >> value;
        Card card(suit[0], value);
        alice.insert(card);
    }
    cardFile1.close();

    while (getline(cardFile2, line) && !line.empty()) {
        stringstream ss(line);
        string suit, value;
        ss >> suit >> value;
        Card card(suit[0], value);
        bob.insert(card);
    }
    cardFile2.close();

    bool match_found = true;
    while (true) {
      bool found = false;
        for (auto it = alice.begin(); it != alice.end(); ++it) {
          if (bob.contains(*it)) {
              Card match = *it;
              alice.remove(match);
              bob.remove(match);
              cout << "Alice picked matching card " << match << endl;
              found = true;
              break;
          }
      }
  
      if (found) continue;
        for (auto it = bob.rbegin(); it != bob.rend(); ++it) {
          if (alice.contains(*it)) {
              Card match = *it;
              alice.remove(match);
              bob.remove(match);
              cout << "Bob picked matching card " << match << endl;
              found = true;
              break;
          }
      }
  
      if (!found) break;
  }
  
cout << endl << "Alice's cards:" << endl;
for (auto it = alice.begin(); it != alice.end(); ++it) {
    cout << *it << endl;
}


cout << endl <<"Bob's cards:" << endl;
for (auto it = bob.rbegin(); it != bob.rend(); ++it) {
    cout << *it << endl;
}


    return 0;
}
