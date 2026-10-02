
#include <iostream>
#include "minpq.hpp"

using namespace std;

struct item
{
    int i, j;
    long long sum;
    item(int a, int b)
    {
        i = a;
        j = b;
        sum = 1LL * a * a * a + 1LL * b * b * b;
    }
    item()
    {
        i = 0;
        j = 0;
        sum = 0;
    }

    void print()
    {
        cout << "i = " << i;
        cout << " j = " << j;
        cout << " i^3 + j^3 = " << sum << endl;
    }
    bool operator>(const item &other) const
    {
        return sum > other.sum;
    }
};

int main()
{
    MinPQ<item> comp_num_theory;
    int n;
    cout << "Enter Value of n: ";
    cin >> n;

    for (int i = 0; i <= n; i++)
    {
        comp_num_theory.insert(item(i, i));
    }
    item previous;
    bool hasPrevious = false;

    while (!comp_num_theory.empty())
    {
        item x = comp_num_theory.delMin();
        x.print();

        if (hasPrevious && x.sum == previous.sum)
        {
            cout << "MATCH FOUND:\n";
        }

        previous = x;
        hasPrevious = true;

        if (x.j < n)
        {
            comp_num_theory.insert(item(x.i, x.j + 1));
        }
    }

    return 0;
}