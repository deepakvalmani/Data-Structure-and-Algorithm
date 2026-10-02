#include <iostream>
#include "minpq.hpp"
#include "maxpq.hpp"
#include <vector>

using namespace std;

template <typename Key>

class dynamic_median_finiding
{
    MaxPQ<Key> left;
    MinPQ<Key> right;
    Key v;
    bool empty = true;

public:
    void insert(Key val)
    {
        if (empty)
        {
            v = val;
            empty = false;
            return;
        }
        else
        {
            if (val < v)
                left.insert(val);
            else
                right.insert(val);
            if (left.size() > right.size())
            {
                right.insert(v);
                v = left.delMax();
            }
            else if (right.size() > left.size() + 1)
            {
                left.insert(v);
                v = right.delMin();
            }
        }
    }

    Key median() { return v; }

    Key removeMedian()
    {
        Key median = v;
        if (empty)
        {
            throw "Empty No elements found";
        }
        if (left.size() == 0 && right.size() == 0)
        {
            empty = true;
            return median;
        }
        if (left.size() < right.size())
        {
            v = right.DelMin();
        }
        else
        {
            v = left.DelMax();
        }
        return median;
    }
};

int main()
{

    dynamic_median_finiding<int> dmp;
    dmp.insert(9);
    cout << dmp.median() << endl;

    dmp.insert(12);
    cout << dmp.median() << endl;

    dmp.insert(90);
    cout << dmp.median() << endl;

    dmp.insert(1);
    cout << dmp.median() << endl;

    dmp.insert(65);
    cout << dmp.median() << endl;

    dmp.insert(89);

    cout << dmp.median() << endl;

    dmp.insert(0);

    cout << dmp.median() << endl;
    
    dmp.insert(61);

    cout << dmp.median() << endl;

    return 0;
}