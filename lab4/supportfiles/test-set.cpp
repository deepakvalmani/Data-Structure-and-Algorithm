#include <iostream>
#include "set.hpp"

using std::cout;

int main() {
    Set<char> s;

    // Insert keys out of order; 'C' is inserted twice to test uniqueness.
    for (char k : {'E', 'A', 'S', 'D', 'C', 'H', 'P', 'M', 'C'})
        s.add(k);
    // s should now hold, in sorted order: A C D E H M P S

    cout << "size()      = " << s.size() << "\n";        // expected: 8

    cout << "contains(H) = " << s.contains('H') << "\n";  // expected: 1
    cout << "contains(X) = " << s.contains('X') << "\n";  // expected: 0

    cout << "min()       = " << s.min() << "\n";          // expected: A

    cout << "ceiling(A)  = " << s.ceiling('A') << "\n";   // expected: A
    cout << "ceiling(F)  = " << s.ceiling('F') << "\n";   // expected: H

    cout << "rank(A)     = " << s.rank('A') << "\n";      // expected: 0
    cout << "rank(H)     = " << s.rank('H') << "\n";      // expected: 4
    cout << "rank(Z)     = " << s.rank('Z') << "\n";      // expected: 8

    // select(i): i-th largest key in the set (see lab handout).
    cout << "select(0)   = " << s.select(0) << "\n";      // expected: S
    cout << "select(7)   = " << s.select(7) << "\n";      // expected: A

    s.remove('H');
    cout << "after remove(H):\n";
    cout << "size()      = " << s.size() << "\n";         // expected: 7
    cout << "contains(H) = " << s.contains('H') << "\n";  // expected: 0
}
