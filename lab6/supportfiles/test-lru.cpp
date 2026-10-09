#include "LRU.h"
int main() {
    LRU cache(3);  // holds at most 3 items
    cache.access(10);  cache.access(20);  cache.access(30);
    std::cout << "Cache after 10,20,30: "; cache.print(); // Expected: 30 20 10

    cache.access(20); // move 20 to front
    std::cout << "After accessing 20: "; cache.print(); // Expected: 20 30 10

    cache.access(40); // cache is full: evicts 10
    std::cout << "After accessing 40: "; cache.print(); // Expected: 40 20 30
    std::cout << "Contains 10? " << cache.contains(10) << "\n"; // Expected: 0 (false)

    std::cout << "Remove LRU = " << cache.remove() << "\n"; // Expected: 30
    std::cout << "Cache after remove: "; cache.print(); // Expected: 40 20

    std::cout << "Size = " << cache.size() << "\n"; // Expected: Size = 2
    std::cout << "Empty = " << cache.empty() << "\n"; // Expected: Empty = 0 (false)
}
