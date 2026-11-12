#include <fstream>
#include <iostream>
#include "HashTable.h"  // test-hashtable.cpp
using std::cout, std::string;

// Print the number of keys n and the number of chains m.
void show(const HashTable& h) {
    cout << "n = " << h.size() << ", m = " << h.tableSize() << "\n";
}

int main() {
    HashTable t(5);  // 5 chains
    for (string w : {"pax", "sod", "fad", "tee", "ace"})
        t.insert(w);
    t.insert("sod");  // already present: ignored
    show(t);                                                 // Expected: n = 5, m = 5
    cout << "Contains fad? " << t.contains("fad") << "\n";   // Expected: 1 (true)
    cout << "Contains dog? " << t.contains("dog") << "\n";   // Expected: 0 (false)

    t.insert("eft");  // full: resize to nextPrime(10) = 11 chains, then insert
    show(t);                                                 // Expected: n = 6, m = 11
    cout << "Load factor = " << t.loadFactor() << "\n";      // Expected: 0.545455
    int hits = 0;
    for (string w : {"pax", "sod", "fad", "tee", "ace", "eft"})
        hits += t.contains(w);
    cout << "Found " << hits << " of 6 keys\n";              // Expected: Found 6 of 6 keys

    HashTable dict;  // a large dictionary: words.txt has 25143 distinct words
    std::ifstream fin("words.txt");
    for (string word; std::getline(fin, word); )
        dict.insert(word);
    show(dict);                                              // Expected: n = 25143, m = 27803
    cout << "Contains table? " << dict.contains("table") << "\n";  // Expected: 1 (true)
    cout << "Contains tabel? " << dict.contains("tabel") << "\n";  // Expected: 0 (false)
}
