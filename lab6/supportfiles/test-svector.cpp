#include "Svector.h"
int main() {
    Svector v1, v2;

    v1.set(1, 3.0);  v1.set(3, 4.0);  v1.set(10, 5.0);
    std::cout << "v1 = "; v1.print();          // Expected: {(1,3), (3,4), (10,5)}

    v2.set(1, 2.0);  v2.set(2, 7.0);  v2.set(3, 1.0);
    std::cout << "v2 = "; v2.print();          // Expected: {(1,2), (2,7), (3,1)}

    std::cout << "v1.get(2) = " << v1.get(2) << "\n";   // Expected: 0
    std::cout << "v1 . v2 = " << v1.dot(v2) << "\n";     // Expected: 10
    std::cout << "||v1|| = " << v1.norm() << "\n";       // Expected: 7.07107

    Svector v3 = v1.add(v2);   std::cout << "v1 + v2 = "; v3.print();  // Expected: {(1,5), (2,7), (3,5), (10,5)}
    v1.scale(2.0);             std::cout << "2 * v1 = ";  v1.print();  // Expected: {(1,6), (3,8), (10,10)}

    // test removing entry by setting to 0
    v1.set(3, 0.0);    std::cout << "After setting v1[3] = 0: "; v1.print();  // Expected: {(1,6), (10,10)}
}
