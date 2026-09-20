#include <iostream>
#include "set.hpp"

using std::cout;

class ExamRoom
{
private:
    int n_;
    Set<int> occupied_;

public:
    ExamRoom(int n) : n_(n) {}

    int seat()
    {
        // TODO: if the room is empty, seat the student at 0.
        // TODO: otherwise, consider every gap between consecutive
        // occupied seats, plus the gap from seat 0 to the first
        // occupied seat and the gap from the last occupied seat to
        // seat n_ - 1. For each gap, compute the distance from the
        // best seat in that gap to the nearest occupied seat, and
        // pick the gap/seat that maximizes that distance (breaking
        // ties by the smallest seat number).
        // Remember to insert the chosen seat into occupied_ before
        // returning it.
        if (occupied_.size() == 0)
        {
            occupied_.add(0);
            return 0;
        };
        int max_distance = -1;
        int idx;
        int first = occupied_.select(occupied_.size()-1);
        int distance = first;

        if(distance> max_distance){
            max_distance = distance;
            idx = 0;
        }

        for (int i = occupied_.size()-1; i> 0; i--)
        {
            int left = occupied_.select(i);
            int right = occupied_.select(i-1);

            int candidate = (right - left) / 2;
            distance = candidate - left;

            if (distance > max_distance || distance == max_distance && candidate < idx)
            {
                
                max_distance = distance;
                idx = candidate;
            }
        }
        occupied_.add(idx);

        return idx;
    }

    void leave(int p)
    {
        // TODO: remove p from occupied_.
        occupied_.remove(p);
    }
};

int main()
{
    ExamRoom examRoom(10);
    cout << examRoom.seat() << "\n"; // expected: 0
    cout << examRoom.seat() << "\n"; // expected: 9
    cout << examRoom.seat() << "\n"; // expected: 4
    cout << examRoom.seat() << "\n"; // expected: 2
    examRoom.leave(4);
    cout << examRoom.seat() << "\n"; // expected: 5
}
