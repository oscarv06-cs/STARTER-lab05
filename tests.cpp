// These files should contain test code for all the classes and methods you used in your game with 
// the custom BST (main.cpp). We recommend at least 5 test cases for each public member function. 
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>
#include "card.h"
#include "card_list.h"

int main() {
    Card ca('c', "a");
    Card da('d', "10");
    Card ca_dup('c', "a");
    assert(ca.getSuit() == 'c');
    assert(ca.getValue() == "a");
    assert(ca == ca_dup);
    assert(!(ca == da));
    assert(ca < da);
    assert(da > ca);

    Card dq('d', "q");
    Card hk('h', "k");
    Card s2('s', "2");
    Card sj('s', "j");
    assert(dq < hk);
    assert(s2 < sj);
    assert(!(sj < s2));
    assert(hk > dq);

    std::ostringstream oss;
    oss << ca;
    assert(oss.str() == "c a");

    bst tree;
    // empty tree
    assert(!tree.contains(ca));

    // insertion
    tree.insert(ca);
    assert(tree.contains(ca));
    tree.insert(da);
    assert(tree.contains(da));

    tree.insert(ca_dup);
    assert(tree.contains(ca_dup));

    // removal
    tree.remove(da);
    assert(!tree.contains(da));
    // remove non-existent
    tree.remove(da);
    assert(!tree.contains(da));

    // add more elements
    tree.insert(da);
    tree.insert(hk);
    tree.insert(s2);

    std::vector<Card> in;
    for (auto it = tree.begin(); it != tree.end(); ++it) {
        in.push_back(*it);
    }
    assert(in.size() == 4);
    assert(in[0] == ca);
    assert(in[1] == da);
    assert(in[2] == s2);
    assert(in[3] == hk);

    // reverse iteration
    std::vector<Card> rev;
    for (auto it = tree.rbegin(); it != tree.rend(); --it) {
        rev.push_back(*it);
    }
    assert(rev.size() == in.size());
    for (size_t i = 0; i < in.size(); ++i) {
        assert(rev[i] == in[in.size() - 1 - i]);
    }

    std::cout << "All tests passed\n";
    return 0;
}
