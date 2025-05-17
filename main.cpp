#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "card.h"
#include "card_list.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1(argv[1]), cardFile2(argv[2]);
    if (!cardFile1 || !cardFile2) {
        cout << "Could not open file " << argv[2] << endl;
        return 1;
    }

    CardList alice, bob;
    string line;

    // Read Alice's hand
    while (getline(cardFile1, line) && !line.empty()) {
        stringstream ss(line);
        char suit;
        string value;
        ss >> suit >> value;
        alice.insert(Card(suit, value));
    }
    cardFile1.close();

    // Read Bob's hand
    while (getline(cardFile2, line) && !line.empty()) {
        stringstream ss(line);
        char suit;
        string value;
        ss >> suit >> value;
        bob.insert(Card(suit, value));
    }
    cardFile2.close();

    // Play
    bool anyMatch = true;
    while (anyMatch) {
        anyMatch = false;

        // Alice’s turn: scan from smallest up
        const Card* a = alice.minValue();
        while (a) {
            if (bob.find(*a)) {
                cout << "Alice picked matching card " << *a << endl;
                bob.remove(*a);
                alice.remove(*a);
                anyMatch = true;
                break;
            }
            a = alice.successor(*a);
        }

        // Bob’s turn: scan from largest down
        const Card* b = bob.maxValue();
        while (b) {
            if (alice.find(*b)) {
                cout << "Bob picked matching card " << *b << endl;
                alice.remove(*b);
                bob.remove(*b);
                anyMatch = true;
                break;
            }
            b = bob.predecessor(*b);
        }
    }

    // Print remaining
    cout << "\nAlice's cards:" << endl;
    alice.printInOrder();
    cout << "\nBob's cards:" << endl;
    bob.printInOrder();

    return 0;
}
