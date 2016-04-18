#include "priorityqueue.hh"

int main() {
   PriorityQueue<int, int> P;
   P.insert(5, 4);
   P.insert(5, 2);
   P.insert(2, 8);
   P.insert(2, 3);
   
   printf ("%lu\n", P.size()); 
   printf("%d\n", P.minValue());
   printf("%d\n", P.maxValue());
   
   P.deleteMin();
   
   printf("%d\n", P.minValue());
}