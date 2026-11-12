// Lab 7, Part C: how good is a hash function?
// Hashes every word of a dictionary into a table with m chains, and prints
// statistics of the chain lengths for several hash functions.
// Usage: hashstats <dictionary_file> <m>

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using std::cout, std::string, std::vector;

// The 31x+y rule: s[0]*31^(k-1) + s[1]*31^(k-2) + ... + s[k-1]. (Provided, as in Part A.)
unsigned int hash31(const string& s) {
    unsigned int h = 0;
    for (char c : s)
        h = 31 * h + (unsigned char) c;
    return h;
}

// The 32x+y rule: s[0]*32^(k-1) + s[1]*32^(k-2) + ... + s[k-1].
unsigned int hash32(const string& s) {
    unsigned int h = 0;
    for (char c : s)
        h = 32 * h + (unsigned char) c;
    return h;
}

// The sum of the letters: s[0] + s[1] + ... + s[k-1].
unsigned int hashSum(const string& s) {
    unsigned int h = 0;
    for (char c : s)
        h += (unsigned char) c;
    return h;
}

// The first two letters only: s[0]*256 + s[1] (just s[0]*256 for a one-letter word).
unsigned int hashFirst2(const string& s) {
    if (s.empty())
        return 0;
    unsigned int h = (unsigned char) s[0] * 256u;
    if (s.size() >= 2)
        h += (unsigned char) s[1];
    return h;
}

// FNV-1a: start with h = 2166136261; for each letter c, h = (h XOR c) * 16777619.
unsigned int hashFNV(const string& s) {
    unsigned int h = 2166136261u;
    for (char c : s) {
        h ^= (unsigned char) c;
        h *= 16777619u;
    }
    return h;
}

// len[i] is the length of chain i, and n is the total number of keys.
// Print the number of empty chains, the length of the longest chain, and the
// average number of compares for a search hit: a key in position j of its chain
// (j = 1, 2, ...) takes j compares, so a chain of length L takes
// 1 + 2 + ... + L = L(L+1)/2 compares to find each of its keys once.
void printStats(const string& name, const vector<int>& len, int n) {
    int empty = 0, longest = 0;
    double compares = 0;
    for (int L : len) {
        if (L == 0)
            ++empty;
        longest = std::max(longest, L);
        compares += L * (L + 1) / 2.0;
    }
    compares /= n;
    cout << std::left << std::setw(20) << name << "empty = " << std::setw(8) << empty
         << "longest = " << std::setw(7) << longest << "compares = " << compares << "\n";
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <dictionary_file> <m>\n";
        return 1;
    }
    std::ifstream fin(argv[1]);
    if (!fin.is_open()) {
        std::cerr << "Cannot read dictionary file " << argv[1] << "\n";
        return 1;
    }
    vector<string> words;   // the dictionary files have no duplicates
    for (string word; std::getline(fin, word); )
        if (!word.empty())
            words.push_back(word);
    int n = words.size(), m = std::stoi(argv[2]);
    double alpha = double(n) / m;

    cout << "n = " << n << ", m = " << m << ", alpha = " << alpha << "\n";
    cout << std::left << std::setw(20) << "uniform hashing" << "empty = " << std::setw(8)
         << std::lround(m * std::exp(-alpha)) << std::setw(17) << "" << "compares = " << 1 + alpha / 2 << "\n";

    struct { string name; unsigned int (*hash)(const string&); } hashes[] = {
        {"31x+y", hash31}, {"32x+y", hash32}, {"sum of letters", hashSum}, {"first two letters", hashFirst2},
        {"FNV-1a", hashFNV}};
    for (auto& [name, hash] : hashes) {
        vector<int> len(m, 0);
        for (const string& w : words)
            len[hash(w) % m]++;
        printStats(name, len, n);
    }
}