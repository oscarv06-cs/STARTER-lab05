// These files should contain test code for all the classes and methods you used in your game with 
// the custom BST (main.cpp). We recommend at least 5 test cases for each public member function.

#include <cassert>
#include <sstream>
#include <vector>
#include <iostream>
#include "card.h"
#include "card_list.h"

// This is the helper to collect std::ostream output
std::string printDeckToString(const bst& tree) {
    std::ostringstream oss;
    tree.printDeck(oss);
    return oss.str();
}

void testCardClass() {
    // Test constructor & getters
    Card ca('c', "a");
    assert(ca.getSuit() == 'c');
    assert(ca.getValue() == "a");

    // Test equality
    Card ca2('c', "a");
    assert(ca == ca2);
    Card cb('c', "b");
    assert(!(ca == cb));

    // Test ordering
    Card da('d', "a");
    assert(ca < da);
    assert(da > ca);

    Card c2('c', "2");
    Card c3('c', "3");
    assert(c2 < c3);
    assert(!(c3 < c2));
    assert(!(c2 > c3));

    // Test ostream output
    std::ostringstream oss;
    oss << ca;
    assert(oss.str() == "c a");
}

void testBSTInsertContains() {
    bst tree;
    Card c1('c', "a"), c2('d', "10"), c3('h', "k"), c4('s', "2"), c5('c', "a");

    // Tje tree should start empty
    assert(!tree.contains(c1));
    assert(!tree.contains(c2));

    // This will insert returns true for new element
    assert(tree.insert(c1));
    // Insert returns false for duplicate
    assert(!tree.insert(c1));
    assert(tree.contains(c1));

    // Insert multiple distinct elements
    assert(tree.insert(c2));
    assert(tree.insert(c3));
    assert(tree.insert(c4));
    assert(tree.contains(c2));
    assert(tree.contains(c3));
    assert(tree.contains(c4));

    // This will insert duplicate
    assert(!tree.insert(c5));

    // This tree should contain only 4 distinct cards
    std::vector<Card> cards;
    for (auto it = tree.begin(); it != tree.end(); ++it) cards.push_back(*it);
    assert(cards.size() == 4);
}

void testBSTRemove() {
    bst tree;
    Card c1('c', "a"), c2('d', "10"), c3('h', "k"), c4('s', "2");

    // Remove from empty
    assert(!tree.remove(c1));

    tree.insert(c1); tree.insert(c2); tree.insert(c3); tree.insert(c4);

    assert(tree.remove(c3));
    assert(!tree.contains(c3));
    assert(!tree.remove(c3));

    //This will Remove leaf
    assert(tree.remove(c4));
    assert(!tree.contains(c4));

    // This Remove root (c1)
    assert(tree.remove(c1));
    assert(!tree.contains(c1));

    //This Remove last element
    assert(tree.remove(c2));
    assert(!tree.contains(c2));

    // The Tree should now be empty
    assert(tree.begin() == tree.end());
}

void testBSTMinMax() {
    bst tree;
    Card c1('d', "4"), c2('c', "2"), c3('s', "k"), c4('h', "10");
    tree.insert(c1); tree.insert(c2); tree.insert(c3); tree.insert(c4);

    assert(tree.minValue() && *tree.minValue() == c2);
    assert(tree.maxValue() && *tree.maxValue() == c3);

    // Remove min, check new min
    tree.remove(c2);
    assert(tree.minValue() && *tree.minValue() == c1);

    // Remove max, check new max
    tree.remove(c3);
    assert(tree.maxValue() && *tree.maxValue() == c4);

    // Empty tree
    tree.remove(c1); tree.remove(c4);
    assert(tree.minValue() == nullptr);
    assert(tree.maxValue() == nullptr);
}

void testBSTSuccessorPredecessor() {
    bst tree;
    Card c1('c', "2"), c2('c', "4"), c3('d', "3"), c4('h', "10");
    tree.insert(c1); tree.insert(c2); tree.insert(c3); tree.insert(c4);

    // In-order: c2, d3, c4, h10
    assert(tree.successor(c1) && *tree.successor(c1) == c3);
    assert(tree.successor(c3) && *tree.successor(c3) == c2);
    assert(tree.successor(c2) && *tree.successor(c2) == c4);
    assert(tree.successor(c4) == nullptr);

    assert(tree.predecessor(c1) == nullptr);
    assert(tree.predecessor(c3) && *tree.predecessor(c3) == c1);
    assert(tree.predecessor(c2) && *tree.predecessor(c2) == c3);
    assert(tree.predecessor(c4) && *tree.predecessor(c4) == c2);
}

void testBSTIterators() {
    bst tree;
    Card c1('c', "2"), c2('c', "4"), c3('d', "3");
    tree.insert(c1); tree.insert(c2); tree.insert(c3);

    // Forward iteration
    std::vector<Card> in;
    for (auto it = tree.begin(); it != tree.end(); ++it) in.push_back(*it);
    assert(in.size() == 3);

    // Reverse iteration
    std::vector<Card> rev;
    for (auto it = tree.rbegin(); it != tree.rend(); --it) rev.push_back(*it);
    assert(rev.size() == in.size());
    for (size_t i = 0; i < in.size(); ++i) assert(rev[i] == in[in.size() - 1 - i]);

    // Empty tree iterators
    bst emptyTree;
    assert(emptyTree.begin() == emptyTree.end());
    assert(emptyTree.rbegin() == emptyTree.rend());

    // Single-element tree
    bst oneTree;
    oneTree.insert(c1);
    auto b = oneTree.begin(), e = oneTree.end();
    assert(b != e); ++b; assert(b == e);
    auto rb = oneTree.rbegin(), re = oneTree.rend();
    assert(rb != re); --rb;
}

void testBSTPrintDeck() {
    bst tree;
    Card c1('d', "4"), c2('c', "2"), c3('s', "k");
    tree.insert(c1); tree.insert(c2); tree.insert(c3);

    std::string output = printDeckToString(tree);
    // Should print in order: c 2\nd 4\ns k\n
    std::istringstream iss(output);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(iss, line)) lines.push_back(line);
    assert(lines.size() == 3);
    assert(lines[0] == "c 2");
    assert(lines[1] == "d 4");
    assert(lines[2] == "s k");
}

int main() {
    testCardClass();
    testBSTInsertContains();
    testBSTRemove();
    testBSTMinMax();
    testBSTSuccessorPredecessor();
    testBSTIterators();
    testBSTPrintDeck();
    std::cout << "All tests passed" << std::endl;
    return 0;
}