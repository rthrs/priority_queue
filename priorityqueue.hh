#ifndef __PRIORITYQUEUE_HH__
#define __PRIORITYQUEUE_HH__

// TODO Stworzyć wyjątki.

template<typename K, typename V>
class PriorityQueue {

private:
   
   using ptr_key_t = std::shared_ptr<K>;
   using ptr_value_t = std::shared_ptr<V>;
   // TODO stworzyc i dodac tutaj komparator (zeby zrobic dereferencje pointera)
   using map_key_t = std::map<ptr_key_t, std::set<ptr_value_t>>;
   using map_value_t = std::map<ptr_value_t, std::set<ptr_key_t>>;

   map_key_t map_key;
   map_value_t map_value;
   size_type counter;


public:
   
   using size_type = size_t;
   using key_type = K;
   using value_type = V;

   /**
    * Konstruktor bezparametrowy tworzący pustą kolejkę.
    * [O(1)]
    */
   PriorityQueue() {
      counter = 0;
   }

   /**
    * Konstruktor kopiujący. 
    * [O(queue.size())]
    */
   PriorityQueue(const PriorityQueue<K, V>& queue) {
   // TODO czy blok try catch jest potrzebny i czy wgl tak moze byc ?
      map_key_t tmp_key(queue.map_key);
      map_value_t tmp_value(queue.map_value);
      map_key.swap(tmp_key);
      map_value.swap(tmp_value);
   }

   /**
    * Konstruktor przenoszący. 
    * [O(1)]
    */
   PriorityQueue(PriorityQueue<K, V>&& queue) {
      map_key = std::move(queue.map_key); 
      map_value = std::move(queue.map_value);
      counter = queue.counter; 
   }

   /**
    * Operator przypisania. 
    * [O(queue.size()) dla użycia P = Q, a O(1) dla użycia P = move(Q)]
    */
   PriorityQueue<K, V>& operator=(PriorityQueue<K, V> queue) {
      queue.swap(*this);
      return *this;
   }

   /**
    * Metoda zwracająca true wtedy i tylko wtedy, gdy kolejka jest pusta. 
    * [O(1)]
    */
   bool empty() const {
      return counter == 0;
   }

   /**
    * Metoda zwracająca liczbę par (klucz, wartość) przechowywanych w kolejce.
    * [O(1)]
    */
   size_type size() const {
      return counter;
   }

   /**
    * Metoda wstawiająca do kolejki parę o kluczu key i wartości value
    * [O(log size())] (dopuszczamy możliwość występowania w kolejce wielu
    * par o tym samym kluczu)
    */
   void insert(const K& key, const V& value) {

   }

   /**
    * Metody zwracające odpowiednio najmniejszą i największą wartość 
    * przechowywaną w kolejce [O(1)]; w przypadku wywołania którejś z tych metod
    * na pustej strukturze powinien zostać zgłoszony wyjątek 
    * PriorityQueueEmptyException
    */
   const V& minValue() const {
      return *map_value.cbegin()->first;
   }
   
   const V& maxValue() const {
      return *map_value.crbegin()->first;
   }

   /**
    * Metody zwracające klucz o przypisanej odpowiednio najmniejszej lub
    * największej wartości [O(1)]; w przypadku wywołania którejś z tych metod
    * na pustej strukturze powinien zostać zgłoszony wyjątek
    * PriorityQueueEmptyException
    */
   // TODO chyba jesli jest kilka takich kluczy to moze byc dowolny right?
   // TODO teraz zawsze zwracany klucz o najmniejszej wartosci, change that?
   const K& minKey() const {
      return *map_value.cbegin()->second.begin();
   }
   

   const K& maxKey() const {
      return *map_value.crbegin()->second.begin();
   }

   /**
    * Metody usuwające z kolejki jedną parę o odpowiednio najmniejszej lub
    * największej wartości [O(log size())]
    */
   void deleteMin() {

   }
   
   void deleteMax() {

   }

   /**
    * Metoda zmieniająca dotychczasową wartość przypisaną kluczowi key na nową
    * wartość value [O(log size())]; w przypadku gdy w kolejce nie ma pary
    * o kluczu key, powinien zostać zgłoszony wyjątek
    * PriorityQueueNotFoundException(); w przypadku kiedy w kolejce jest kilka 
    * par o kluczu key, zmienia wartość w dowolnie wybranej parze o podanym 
    * kluczu
    */
   void changeValue(const K& key, const V& value) {
   
   }

   /**
    * Metoda scalająca zawartość kolejki z podaną kolejką queue; ta operacja 
    * usuwa wszystkie elementy z kolejki queue i wstawia je do kolejki *this
    * [O(size() + queue.size() * log (queue.size() + size()))]
    */
   void merge(PriorityQueue<K, V>& queue) {

   }

   /**
    * Metoda zamieniającą zawartość kolejki z podaną kolejką queue (tak jak
    * większość kontenerów w bibliotece standardowej) [O(1)]
    */
   void swap(PriorityQueue<K, V>& queue) {
      map_key.swap(queue.map_key);
      map_value.swap(queue.map_value);
      std::swap(counter, queue.map_counter);
   }

}

#endif /* __PRIORITYQUEUE_HH__ */

