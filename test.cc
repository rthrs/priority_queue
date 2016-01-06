#include <iostream>
#include <exception>
#include <cassert>

#include "priorityqueue.hh"

PriorityQueue<int, int> f(PriorityQueue<int, int> q)
{
    return q;
}

int main() {

{

    PriorityQueue<int, int> TT = f(PriorityQueue<int, int>());
    TT.insert(1, 1);
    TT.insert(1, 2);
    TT.insert(1, 3);
    TT.insert(1, 4);
}
    PriorityQueue<int, int> P = f(PriorityQueue<int, int>());
    assert(P.empty());

    P.insert(1, 42);
    P.insert(2, 13);

    assert(P.size() == 2);
    assert(P.maxKey() == 1);
    assert(P.maxValue() == 42);
    assert(P.minKey() == 2);
    assert(P.minValue() == 13);
/*{
    P.insert(1, 42);

    assert(P.size() == 3);

    P.insert(1, 100);
    P.insert(2, 2);

    assert(P.maxKey() == 1);
    assert(P.maxValue() == 100);
    assert(P.minKey() == 2);
    assert(P.minValue() == 2);
}*/

    PriorityQueue<int, int> Q(f(P));

    assert(Q.size() == 2);
    assert(Q.maxKey() == 1);
    assert(Q.maxValue() == 42);
    assert(Q.minKey() == 2);
    assert(Q.minValue() == 13);

    Q.deleteMax();
    Q.deleteMin();
    Q.deleteMin();

    assert(Q.empty());

    PriorityQueue<int, int> R(Q);

    R.insert(1, 100);
    R.insert(2, 100);
    R.insert(3, 300);

    PriorityQueue<int, int> S;
    S = R;

    try
    {
        S.changeValue(4, 400);
    }
    catch (const PriorityQueueNotFoundException& pqnfex)
    {
        std::cout << pqnfex.what() << std::endl;
    }
    catch (...)
    {
        assert(!"exception missing!");
    }

    S.changeValue(2, 200);

    try
    {
        while (true)
        {
            std::cout << S.minKey()<< " " << S.minValue() << std::endl;
            S.deleteMin();
        }
        assert(!"S.minValue() on empty S did not throw!");
    }
    catch (const PriorityQueueEmptyException& pqeex)
    {
        std::cout << pqeex.what() << std::endl;
    }
    catch (...)
    {
        assert(!"exception missing!");
    }

    try
    {
        S.minKey();
        assert(!"S.minKey() on empty S did not throw!");
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (...)
    {
        assert(!"exception missing!");
    }

    PriorityQueue<int, int> T;
    T.insert(1, 1);
    T.insert(2, 4);
    S.insert(3, 9);
    S.insert(4, 16); 
    S.merge(T);
    assert(S.size() == 4);
    assert(S.minValue() == 1);
    assert(S.maxValue() == 16);
    assert(T.empty());

    S = R;
    std::swap(R, T);

    assert(T == S);
    assert(T != R);

    R = std::move(S);
    assert(T != S);
    assert(T == R);

    std::cout << "ALL OK!" << std::endl;

    return 0;
}
