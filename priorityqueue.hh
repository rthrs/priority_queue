#ifndef __PRIORITYQUEUE_HH__
#define __PRIORITYQUEUE_HH__

#include <memory>
#include <map>
#include <set>

// TODO Stworzyć wyjątki.

template<typename K, typename V>
class PriorityQueue {

public:
   
   using size_type = size_t;
   using key_type = K;
   using value_type = V;

   /**
    * Konstruktor bezparametrowy tworzący pustą kolejkę.
    * [O(1)]
    */
   PriorityQueue() {}

   /**
    * Konstruktor kopiujący. 
    * [O(queue.size())]
    */
   PriorityQueue(const PriorityQueue<K, V>& queue);

   /**
    * Konstruktor przenoszący. 
    * [O(1)]
    */
   PriorityQueue(PriorityQueue<K, V>&& queue);

   /**
    * Operator przypisania. 
    * [O(queue.size()) dla użycia P = Q, a O(1) dla użycia P = move(Q)]
    */
   PriorityQueue<K, V>& operator=(PriorityQueue<K, V> queue);

   /**
    * Metoda zwracająca true wtedy i tylko wtedy, gdy kolejka jest pusta. 
    * [O(1)]
    */
   bool empty() const;

   /**
    * Metoda zwracająca liczbę par (klucz, wartość) przechowywanych w kolejce.
    * [O(1)]
    */
   size_type size() const;

   /**
    * Metoda wstawiająca do kolejki parę o kluczu key i wartości value
    * [O(log size())] (dopuszczamy możliwość występowania w kolejce wielu
    * par o tym samym kluczu)
    */
   void insert(const K& key, const V& value);

   /**
    * Metody zwracające odpowiednio najmniejszą i największą wartość 
    * przechowywaną w kolejce [O(1)]; w przypadku wywołania którejś z tych metod
    * na pustej strukturze powinien zostać zgłoszony wyjątek 
    * PriorityQueueEmptyException
    */
   const V& minValue() const;
   
   const V& maxValue() const;

   /**
    * Metody zwracające klucz o przypisanej odpowiednio najmniejszej lub
    * największej wartości [O(1)]; w przypadku wywołania którejś z tych metod
    * na pustej strukturze powinien zostać zgłoszony wyjątek
    * PriorityQueueEmptyException
    */
   const K& minKey() const;

   const K& maxKey() const;

   /**
    * Metody usuwające z kolejki jedną parę o odpowiednio najmniejszej lub
    * największej wartości [O(log size())]
    */
   void deleteMin();
   
   void deleteMax();

   /**
    * Metoda zmieniająca dotychczasową wartość przypisaną kluczowi key na nową
    * wartość value [O(log size())]; w przypadku gdy w kolejce nie ma pary
    * o kluczu key, powinien zostać zgłoszony wyjątek
    * PriorityQueueNotFoundException(); w przypadku kiedy w kolejce jest kilka 
    * par o kluczu key, zmienia wartość w dowolnie wybranej parze o podanym 
    * kluczu
    */
   void changeValue(const K& key, const V& value);

   /**
    * Metoda scalająca zawartość kolejki z podaną kolejką queue; ta operacja 
    * usuwa wszystkie elementy z kolejki queue i wstawia je do kolejki *this
    * [O(size() + queue.size() * log (queue.size() + size()))]
    */
   void merge(PriorityQueue<K, V>& queue);

   /**
    * Metoda zamieniającą zawartość kolejki z podaną kolejką queue (tak jak
    * większość kontenerów w bibliotece standardowej) [O(1)]
    */
   void swap(PriorityQueue<K, V>& queue);

private:

   template<typename T>
   struct LessPQ {
      bool operator() (const T& lhs, const T& rhs) const {
         return *lhs < *rhs;
      }
   };
   
   using ptr_key_t = std::shared_ptr<K>;
   using ptr_value_t = std::shared_ptr<V>;
   using set_key_t = std::set<ptr_key_t, LessPQ<ptr_key_t>>;
   using set_value_t = std::set<ptr_value_t, LessPQ<ptr_value_t>>;
   using map_key_t = std::map<ptr_key_t, set_value_t, LessPQ<ptr_key_t>>;
   using map_value_t = std::map<ptr_value_t, set_key_t, LessPQ<ptr_value_t>>;

   map_key_t map_key;
   map_value_t map_value;
   size_type counter = 0;
};

template<typename K, typename V>
PriorityQueue<K, V>::PriorityQueue(const PriorityQueue<K, V>& queue) {
// TODO czy blok try catch jest potrzebny i czy wgl tak moze byc ?
   map_key_t tmp_key(queue.map_key);
   map_value_t tmp_value(queue.map_value);
   map_key.swap(tmp_key);
   map_value.swap(tmp_value);
   counter = queue.counter; 
}

template<typename K, typename V>
PriorityQueue<K, V>::PriorityQueue(PriorityQueue<K, V>&& queue) {
   map_key = std::move(queue.map_key); 
   map_value = std::move(queue.map_value);
   counter = queue.counter; 
}

template<typename K, typename V>
PriorityQueue<K, V>& PriorityQueue<K, V>::operator=(PriorityQueue<K, V> queue) {
   queue.swap(*this);
   return *this;
}

template<typename K, typename V>
bool PriorityQueue<K, V>::empty() const {
   return counter == 0;
}

template<typename K, typename V>
typename PriorityQueue<K, V>::size_type PriorityQueue<K, V>::size() const {
   return counter;
}



template<typename K, typename V>
void PriorityQueue<K, V>::insert(const K& key, const V& value) {
   ptr_key_t tmp_k = std::make_shared<K>(key);
   ptr_value_t tmp_v = std::make_shared<V>(value);

   map_key[tmp_k].insert(tmp_v);
   map_value[tmp_v].insert(tmp_k);
/*
#include <iostream>
std::cout << map_key.size() << std::endl;
std::cout << map_value.size() << std::endl;
*/
   ++counter;
}

template<typename K, typename V> // K?
const V& PriorityQueue<K, V>::minValue() const {
   return *map_value.cbegin()->first;
}

template<typename K, typename V> // K?
const V& PriorityQueue<K, V>::maxValue() const {
   return *map_value.crbegin()->first;
}

// TODO chyba jesli jest kilka takich kluczy to moze byc dowolny right?
// TODO teraz zawsze zwracany klucz o najmniejszej wartosci, change that?
template<typename K, typename V> // V?
const K& PriorityQueue<K, V>::minKey() const {
   return **map_value.cbegin()->second.begin();
}

template<typename K, typename V> // V?
const K& PriorityQueue<K, V>::maxKey() const {
   return **map_value.crbegin()->second.begin();
}

template<typename K, typename V>
void PriorityQueue<K, V>::deleteMin() {
    if (empty())
      return;
   auto it_k = map_value.cbegin()->second.cbegin();
   ptr_key_t tmp_k = *it_k;
   ptr_value_t tmp_v = map_value.cbegin()->first;
   map_value.begin()->second.erase(it_k);
   if (map_value.begin()->second.empty())
      map_value.erase(map_value.cbegin());
   // TODO kilka razy logarytmiczen operacje, moze da sie raz na iteratorze
   map_key[tmp_k].erase(tmp_v);
   if (map_key[tmp_k].empty())
      map_key.erase(tmp_k);
   --counter;
}

template<typename K, typename V>
void PriorityQueue<K, V>::deleteMax() {
   if (empty())
      return;
   // TODO copy paste
   auto it_k = map_value.crbegin()->second.cbegin();
   ptr_key_t tmp_k = *it_k;
   ptr_value_t tmp_v = map_value.crbegin()->first;
   map_value.rbegin()->second.erase(it_k);
   if (map_value.crbegin()->second.empty())
      map_value.erase(--map_value.crbegin().base());
   // TODO kilka razy logarytmiczen operacje, moze da sie raz na iteratorze
   map_key[tmp_k].erase(tmp_v);
   if (map_key[tmp_k].empty())
      map_key.erase(tmp_k);
   --counter;
}

template<typename K, typename V>
void PriorityQueue<K, V>::changeValue(const K& key, const V& value) {

}

template<typename K, typename V>
void PriorityQueue<K, V>::merge(PriorityQueue<K, V>& queue) {

}

template<typename K, typename V>
void PriorityQueue<K, V>::swap(PriorityQueue<K, V>& queue) {
   map_key.swap(queue.map_key);
   map_value.swap(queue.map_value);
   std::swap(counter, queue.counter);
}

// TODO operatory porównania... 

#endif /* __PRIORITYQUEUE_HH__ */

