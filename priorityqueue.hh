/*============================================================================*/
/*                  JNP Grupa 7 - Zadanie 5 - Priority Queue                  */
/*                        Katarzyna Herba  - kh359525                         */
/*                        Artur Myszkowski - am347189                         */
/*============================================================================*/
/* Implementacja kolejki priorytetowej opiera się na strukturach              */
/* przechowujących smart pointer'y - shared_ptr. Każda para (Key, Value) jest */
/* tworzona raz, a opearcje wykonywane są na wskaźnikach. Użyte kontenery to  */
/* map<shared_ptr<K>, multiset<shared_ptr<V>>> oraz                           */
/* map<shared_ptr<V>, multiset<shared_ptr<K>>> z odpowiednio zdefiniowanym    */
/* komparatorem.                                                              */
/*============================================================================*/

#ifndef __PRIORITYQUEUE_HH__
#define __PRIORITYQUEUE_HH__

#include <memory>
#include <map>
#include <set>
#include <algorithm>
#include <cassert>
#include <utility>

/*============================================================================*/
/*                                 Wyjątki.                                   */
/*============================================================================*/

class PriorityQueueEmptyException: public std::exception {

public:

   virtual const char* what() const noexcept {
      return "PriorityQueueEmptyException";
   }
};

class PriorityQueueNotFoundException: public std::exception {

public:

   virtual const char* what() const noexcept {
      return "PriorityQueueNotFoundException";
   }
};

/*============================================================================*/
/*                                Interfejs.                                  */
/*============================================================================*/

template<typename K, typename V>
class PriorityQueue {

public:
   
   using size_type = size_t;
   using key_type = K;
   using value_type = V;

   /**
    * Konstruktor bezparametrowy tworzący pustą kolejkę. [O(1)]
    */
   PriorityQueue() {}

   /**
    * Konstruktor kopiujący. [O(queue.size())]
    */
   PriorityQueue(const PriorityQueue<K, V>& queue);

   /**
    * Konstruktor przenoszący. [O(1)]
    */
   PriorityQueue(PriorityQueue<K, V>&& queue);

   /**
    * Operator przypisania. 
    * [O(queue.size()) dla użycia P = Q, a O(1) dla użycia P = move(Q)]
    */
   PriorityQueue<K, V>& operator=(PriorityQueue<K, V> queue);

   /**
    * Metoda zwracająca true wtedy i tylko wtedy, gdy kolejka jest pusta. [O(1)]
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
    * par o tym samym kluczu).
    */
   void insert(const K& key, const V& value);

   /**
    * Metody zwracające odpowiednio najmniejszą i największą wartość 
    * przechowywaną w kolejce [O(1)]; w przypadku wywołania którejś z tych metod
    * na pustej strukturze powinien zostać zgłoszony wyjątek 
    * PriorityQueueEmptyException.
    */
   const V& minValue() const;
   
   const V& maxValue() const;

   /**
    * Metody zwracające klucz o przypisanej odpowiednio najmniejszej lub
    * największej wartości [O(1)]; w przypadku wywołania którejś z tych metod
    * na pustej strukturze powinien zostać zgłoszony wyjątek
    * PriorityQueueEmptyException.
    */
   const K& minKey() const;

   const K& maxKey() const;

   /**
    * Metody usuwające z kolejki jedną parę o odpowiednio najmniejszej lub
    * największej wartości. [O(log size())]
    */
   void deleteMin();
   
   void deleteMax();

   /**
    * Metoda zmieniająca dotychczasową wartość przypisaną kluczowi key na nową
    * wartość value [O(log size())]; w przypadku gdy w kolejce nie ma pary
    * o kluczu key, powinien zostać zgłoszony wyjątek
    * PriorityQueueNotFoundException(); w przypadku kiedy w kolejce jest kilka 
    * par o kluczu key, zmienia wartość w dowolnie wybranej parze o podanym 
    * kluczu.
    */
   void changeValue(const K& key, const V& value);

   /**
    * Metoda scalająca zawartość kolejki z podaną kolejką queue; ta operacja 
    * usuwa wszystkie elementy z kolejki queue i wstawia je do kolejki *this.
    * [O(size() + queue.size() * log (queue.size() + size()))]
    */
   void merge(PriorityQueue<K, V>& queue);

   /**
    * Metoda zamieniającą zawartość kolejki z podaną kolejką queue (tak jak
    * większość kontenerów w bibliotece standardowej). [O(1)]
    */
   void swap(PriorityQueue<K, V>& queue);
  
   bool operator==(const PriorityQueue<K, V>& queue) const;
   
   bool operator<(const PriorityQueue<K, V>& queue) const;
   
   bool operator!=(const PriorityQueue<K, V>& queue) const;
   
   bool operator<=(const PriorityQueue<K, V>& queue) const;
   
   bool operator>(const PriorityQueue<K, V>& queue) const;
   
   bool operator>=(const PriorityQueue<K, V>& queue) const;
   
private:

   // Komparator porównujący zdereferowane wskaźniki.
   template<typename T>
   struct LessPtr {
      bool operator() (const T& lhs, const T& rhs) const {
         return *lhs < *rhs;
      }
   };
   
   using ptr_key_t = std::shared_ptr<K>;
   using ptr_value_t = std::shared_ptr<V>;
   using set_key_t = std::multiset<ptr_key_t, LessPtr<ptr_key_t>>;
   using set_value_t = std::multiset<ptr_value_t, LessPtr<ptr_value_t>>;
   using map_key_t = std::map<ptr_key_t, set_value_t, LessPtr<ptr_key_t>>;
   using map_value_t = std::map<ptr_value_t, set_key_t, LessPtr<ptr_value_t>>;

   map_key_t map_key;
   map_value_t map_value;
   size_type counter = 0;
};

/*============================================================================*/
/*                             Implementacja.                                 */
/*============================================================================*/

template<typename K, typename V>
PriorityQueue<K, V>::PriorityQueue(const PriorityQueue<K, V>& queue) {
   map_key_t tmp_key(queue.map_key); // O(queue.size())
   map_value_t tmp_value(queue.map_value); // O(queue.size()
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
   auto it = map_key.find(tmp_k); // O(log size()))
   typename set_value_t::const_iterator set_it;
   bool first = false;
   if (it == map_key.end()) {
      first = true;
      set_value_t s;
      s.insert(tmp_v);
      auto it_tmp = map_key.insert(std::make_pair(tmp_k,s));
      it = it_tmp.first;
   } else {
      set_it = map_key[tmp_k].insert(tmp_v); // O(log size()))
   }
   try {
      map_value[tmp_v].insert(tmp_k);
   } catch (...) {
      if (first) 
         map_key.erase(it); // O(1)
      else 
         it->second.erase(set_it); // O(1)
      throw;
   }
   ++counter;
}

template<typename K, typename V>
const V& PriorityQueue<K, V>::minValue() const {
   if (empty())
      throw PriorityQueueEmptyException();
   return *map_value.cbegin()->first;
}

template<typename K, typename V>
const V& PriorityQueue<K, V>::maxValue() const {
   if (empty())
      throw PriorityQueueEmptyException();
   return *map_value.crbegin()->first;
}

template<typename K, typename V>
const K& PriorityQueue<K, V>::minKey() const {
   if (empty())
      throw PriorityQueueEmptyException();
   return **map_value.cbegin()->second.begin();
}

template<typename K, typename V>
const K& PriorityQueue<K, V>::maxKey() const {
   if (empty())
      throw PriorityQueueEmptyException();
   return **map_value.crbegin()->second.begin();
}

template<typename K, typename V>
void PriorityQueue<K, V>::deleteMin() {
    if (empty())
      return;

   auto it_k = map_value.cbegin()->second.cbegin();
   ptr_key_t tmp_k = *it_k;
   ptr_value_t tmp_v = map_value.cbegin()->first;

   auto it_map_key = map_key.find(tmp_k); // O(log size()))
   assert(it_map_key != map_key.end());
   auto it_map_key_set = it_map_key->second.find(tmp_v); // O(log size()))
   assert(it_map_key_set != it_map_key->second.end());

   // Usunięcie klucza spod min wartości.
   map_value.begin()->second.erase(it_k); // O(1)
   if (map_value.begin()->second.empty()) 
      map_value.erase(map_value.cbegin()); // O(1)

   // Usunięcie tej wartości spod klucza.
   it_map_key->second.erase(it_map_key_set); // O(1)
   if (it_map_key->second.empty())
      map_key.erase(it_map_key); // O(1)
 
   --counter;
}

template<typename K, typename V>
void PriorityQueue<K, V>::deleteMax() {
   if (empty())
      return;

   auto it_k = map_value.crbegin()->second.cbegin();
   ptr_key_t tmp_k = *it_k;
   ptr_value_t tmp_v = map_value.crbegin()->first;

   auto it_map_key = map_key.find(tmp_k); // O(log size()))
   assert(it_map_key != map_key.end());
   auto it_map_key_set = it_map_key->second.find(tmp_v); // O(log size()))
   assert(it_map_key_set != it_map_key->second.end());

   // Usunięcie klucza spod max wartości.
   map_value.rbegin()->second.erase(it_k); // O(1)
   if (map_value.rbegin()->second.empty()) 
      map_value.erase(--map_value.crbegin().base()); // O(1)

   // Usunięcie tej wartości spod klucza.
   it_map_key->second.erase(it_map_key_set); // O(1)
   if (it_map_key->second.empty())
      map_key.erase(it_map_key); // O(1)
 
   --counter;
}

template<typename K, typename V>
void PriorityQueue<K, V>::changeValue(const K& key, const V& value) { 
   ptr_key_t tmp_k = std::make_shared<K>(key);

   // Znajdowanie klucza.
   auto it_k = map_key.find(tmp_k); // O(log size())
   if (it_k == map_key.end())
      throw PriorityQueueNotFoundException();

   // Uzyskanie iteratorow do elementow, ktore będą usuwane
   // przy pomyślnym insercie nowego elementu.
   ptr_value_t tmp_v = *it_k->second.begin();
   auto map_value_it = map_value.find(tmp_v); // O(log size())
   auto set_key_it = it_k->second.begin();
   typename set_key_t::const_iterator set_it;
   bool single = (map_value_it->second.size() == 1) ? true : false;
   if (!single)
      set_it = map_value_it->second.find(tmp_k); // O(log size())
   
   insert(key, value);
   --counter;
   
   // Usunięcie elementów przy zakończonym sukcesem insercie,
   // ponieważ begin() oraz erase() dla iteratorów są
   // no-throw, tu wyjątek nie może się pojawić.
   it_k->second.erase(set_key_it); // O(1)
   if (single)
      map_value.erase(map_value_it); // O(1)
   else
      map_value_it->second.erase(set_it); // O(1)
}

template<typename K, typename V>
void PriorityQueue<K, V>::merge(PriorityQueue<K, V>& queue) {
   // Jeśli merge do samego siebie.
   if (this == &queue)
      return;

   // Merge z queue.
   PriorityQueue<K, V> tmp(*this);

   // Obie pętle O(queue.size() * log (queue.size() + size()))
   for (auto it = queue.map_key.begin(); it != queue.map_key.end(); ++it)
      tmp.map_key[it->first].insert(it->second.begin(), it->second.end());

   for (auto it = queue.map_value.begin(); it != queue.map_value.end(); ++it)
      tmp.map_value[it->first].insert(it->second.begin(), it->second.end());

   tmp.counter += queue.counter;
   tmp.swap(*this);

   // Czyszczenie queue. clear() jest no-throw.
   queue.map_key.clear(); // O(queue.size())
   queue.map_value.clear(); //  O(queue.size())
   queue.counter = 0;
}

template<typename K, typename V>
void PriorityQueue<K, V>::swap(PriorityQueue<K, V>& queue) {
   std::swap(map_key, queue.map_key);
   std::swap(map_value, queue.map_value);
   std::swap(counter, queue.counter);
}

// Globalna metoda swap.
template<typename K, typename V>
void swap(PriorityQueue<K, V>& lhs, PriorityQueue<K, V>& rhs) {
   lhs.swap(rhs);
}

template<typename K, typename V>
bool PriorityQueue<K, V>::operator==(const PriorityQueue<K, V>& queue) const {
   if (size() != queue.size())
      return false;
   if (map_key.size() != queue.map_key.size()) {
      return false;
   }
   auto lhs_it = map_key.begin();
   auto rhs_it = queue.map_key.begin();
   while (lhs_it != map_key.end()) {
      if (!(*(lhs_it->first) == *(rhs_it->first))) {
         return false;
      } else {
         if (lhs_it->second.size() != rhs_it->second.size()) {
            return false;
         } else {
            auto lhs_set_it = lhs_it->second.begin();
            auto rhs_set_it = rhs_it->second.begin();
            while (lhs_set_it != lhs_it->second.end()) {
               if (!(**lhs_set_it == **rhs_set_it)) {
                  return false;
               } else {
                  ++lhs_set_it;
                  ++rhs_set_it;
               }
            }
         }
      }
      ++lhs_it;
      ++rhs_it;
   }
   return true;
}

template<typename K, typename V>
bool PriorityQueue<K, V>::operator!=(const PriorityQueue<K, V>& queue) const {
   return !(*this == queue);
}

template<typename K, typename V>
bool PriorityQueue<K, V>::operator<(const PriorityQueue<K, V>& queue) const {
   auto lhs_it = map_key.begin();
   auto rhs_it = queue.map_key.begin();
   while (lhs_it != map_key.end() && rhs_it != queue.map_key.end()) {
      if (*lhs_it->first == *rhs_it->first) {
         if (lhs_it->second.size() == rhs_it->second.size()) {
            auto lhs_set_it = lhs_it->second.begin();
            auto rhs_set_it = rhs_it->second.begin();
            while (lhs_set_it != lhs_it->second.end()) {
               if (**lhs_set_it == **rhs_set_it) {
                  ++lhs_set_it;
                  ++rhs_set_it;
               } else {
                  return **lhs_set_it < **rhs_set_it;
               }
            }
         } else {
            return lhs_it->second.size() > rhs_it->second.size();
         }
      } else {
         return *lhs_it->first < *rhs_it->first;
      }
      ++lhs_it;
      ++rhs_it;
   }
   return (lhs_it == map_key.end() && rhs_it != queue.map_key.end());
}

template<typename K, typename V>
bool PriorityQueue<K, V>::operator>(const PriorityQueue<K, V>& queue) const {
   return queue < *this;
}

template<typename K, typename V>
bool PriorityQueue<K, V>::operator>=(const PriorityQueue<K, V>& queue) const {
   return !(*this < queue);
}

template<typename K, typename V>
bool PriorityQueue<K, V>::operator<=(const PriorityQueue<K, V>& queue) const {
   return !(*this > queue);
}

#endif /* __PRIORITYQUEUE_HH__ */
