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
    PriorityQueue<int, int> AA = f(PriorityQueue<int, int>());
    TT.insert(1, 1);
    TT.insert(2, 2);
    TT.insert(3, 3);
    AA.insert(1, 1);
    AA.insert(2, 2);
    AA.insert(3, 3);
    assert(AA == TT);
    TT.insert(1, 1);
    TT.insert(1, 1); 
    TT.insert(1, 1);
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
    
    assert(Q.empty());

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
    
    std::cout << "here\n";

    S = R;
    swap(R, T);

    assert(T == S);
    assert(T != R);
    
    std::cout << "yoho\n";

    R = std::move(S);
    
    std:: cout << "hue\n";
    
    std:: cout << S.size() << std::endl;
    //S.insert(2, 3);
    assert(T != S);
    
    std:: cout << "ho\n";
    
    assert(T == R);
    
    std::cout << "there\n";
    
{
    PriorityQueue<int, int> PP;
    PriorityQueue<int, int> QQ;
    PriorityQueue<int, int> SS;
    PP.insert(1, 42);
    PP.insert(2, 13);
    QQ.insert(1, 41);
    QQ.insert(3, 12);
    SS.insert(1, 42);
    assert(QQ < SS);
    assert(SS < PP);
    printf("%zu %zu\n", PP.size(), SS.size());
    
    printf("%d\n", PP < SS);
    assert(QQ < PP);
    assert(QQ <= SS);
    assert(SS <= PP);
    assert(QQ <= PP);
    assert(SS > QQ);
    assert(PP > SS);
    assert(PP > QQ);
    assert(SS >= QQ);
    assert(PP >= SS);
    assert(PP >= QQ);


}

    std::cout << "ALL OK!" << std::endl;
    return 0;
}
