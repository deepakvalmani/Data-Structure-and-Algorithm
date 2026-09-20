#include <vector>
#include <iostream>
#include <random>
#include "stopwatch.hpp"

using std::cout, std::cerr, std::vector;

int count(const vector<int> &a)
{
    int n = a.size();

    int count = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            for (int k = j + 1; k < n; k++)
                if (a[i] + a[j] + a[k] == 0)
                    count++;

    return count;
}

int main(int argc, char *argv[])
{
    int n;
    if (argc >= 2)
        n = std::stoi(argv[1]);
    else
    {
        cerr << "Expected n as 1st command line argument";
        return 1;
    }

    constexpr int R = 1000; // range of random numbers
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> intDist(-R, R);

    vector<int> a(n);
    for (int &x : a)
        x = intDist(rng);

    Stopwatch sw;
    cout << "Count: " << count(a) << "\n"
         << "Time: " << sw.elapsedTime() << "\n";
}
