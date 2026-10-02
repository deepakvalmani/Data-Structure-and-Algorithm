#include <iostream>
#include <vector>
#include "bst.hpp"

using std::cout, std::vector;

void print(const vector<int>& v) {
    for (int k : v) cout << k << " ";
    cout << "\n";
}

int main() {
    //                 50
    //          30            70
    //       20    40      60      80
    //     10    35  45  55  65       90
    //                              85
    vector<int> keys = {50, 30, 70, 20, 40, 60, 80, 10, 35, 45, 55, 65, 90, 85};
    Node* t = buildFromLevelOrder(keys);

    cout << "levelOrder          = "; print(levelOrder(t));
                                     // expected: 50 30 70 20 40 60 80 10 35 45 55 65 90 85
    cout << "size                = " << size(t) << "\n";                 // expected: 14
    cout << "height              = " << height(t) << "\n";               // expected: 4
    cout << "sizeOdd             = " << sizeOdd(t) << "\n";              // expected: 5
    cout << "isPerfectlyBalanced = " << isPerfectlyBalanced(t) << "\n";  // expected: 0
    cout << "isSemiBalanced      = " << isSemiBalanced(t) << "\n";       // expected: 0
    cout << "sizeAtDepth(3)      = " << sizeAtDepth(t, 3) << "\n";       // expected: 6
    cout << "sizeAboveDepth(2)   = " << sizeAboveDepth(t, 2) << "\n";    // expected: 3
    cout << "sizeBelowDepth(2)   = " << sizeBelowDepth(t, 2) << "\n";    // expected: 7
    destroy(t);

    //         4
    //      2     6
    //     1 3   5 7
    Node* p = buildFromLevelOrder({4, 2, 6, 1, 3, 5, 7});
    cout << "\nperfect tree:\n";
    cout << "levelOrder          = "; print(levelOrder(p));               // expected: 4 2 6 1 3 5 7
    cout << "height              = " << height(p) << "\n";               // expected: 2
    cout << "isPerfectlyBalanced = " << isPerfectlyBalanced(p) << "\n";  // expected: 1
    cout << "isSemiBalanced      = " << isSemiBalanced(p) << "\n";       // expected: 1
    destroy(p);

    //         4
    //      2     6
    //     1 3   5
    Node* s = buildFromLevelOrder({4, 2, 6, 1, 3, 5});
    cout << "\nsemi-balanced tree:\n";
    cout << "isPerfectlyBalanced = " << isPerfectlyBalanced(s) << "\n";  // expected: 0
    cout << "isSemiBalanced      = " << isSemiBalanced(s) << "\n";       // expected: 1
    destroy(s);

    // 1 -> 2 -> 3   (right links only)
    Node* c = buildFromLevelOrder({1, 2, 3});
    cout << "\nchain:\n";
    cout << "height              = " << height(c) << "\n";               // expected: 2
    cout << "isSemiBalanced      = " << isSemiBalanced(c) << "\n";       // expected: 0
    destroy(c);

    Node* e = buildFromLevelOrder({});
    cout << "\nempty tree:\n";
    cout << "height              = " << height(e) << "\n";               // expected: -1
    cout << "isPerfectlyBalanced = " << isPerfectlyBalanced(e) << "\n";  // expected: 1
    cout << "isSemiBalanced      = " << isSemiBalanced(e) << "\n";       // expected: 1
    cout << "sizeAtDepth(0)      = " << sizeAtDepth(e, 0) << "\n";       // expected: 0
}
