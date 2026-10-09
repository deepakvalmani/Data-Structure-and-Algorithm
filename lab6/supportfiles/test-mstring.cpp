#include "Mstring.h"
int main() {
    Mstring s;
    // Insert characters to form "abcd"
    s.insert(0, 'a');  s.insert(1, 'b');  s.insert(2, 'c');  s.insert(3, 'd');
    std::cout << "String after inserts: "; s.print();  // Expected: abcd
    // Get a character
    std::cout << "s.get(2) = " << s.get(2) << std::endl;  // Expected: c
    // Insert in the middle
    s.insert(2, 'X');
    std::cout << "After insert X at pos 2: "; s.print();  // Expected: abXcd
    // Remove a character
    s.remove(3);
    std::cout << "After remove at pos 3: "; s.print();   // Expected: abXd
    // Remove first and last
    s.remove(0);   s.remove(s.size() - 1);
    std::cout << "After removing first and last: "; s.print();   // Expected: bX
}
