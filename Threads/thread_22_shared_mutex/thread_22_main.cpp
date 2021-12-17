#include <iostream>
#include <mutex>  
#include <shared_mutex>
#include <thread>
using namespace std;
struct A {
  A() = default;
  // Декілька потоків/рідерів 
  // можуть одночасно читати спільні дані 
  unsigned int get() const { shared_lock lock(m);
    return data;
  }
  // Тільки один потік/райтер може змінювати дані
  void increment() {  unique_lock lock(m);
    data++;
  }
// Тільки один потік/райтер може занулювати дані
  
  void reset() {  unique_lock lock(m);
    data = 0;
  }
  mutable shared_mutex m;
  unsigned int data = 0;
};
int main() {
  A a;
  auto f = [&a]() {
    for (int i = 0; i < 3; i++) {
      a.increment();
      cout << this_thread::get_id() << 
           ' ' << a.get() << '\n';
    }
  };
  thread t1(f);  thread t2(f);
  t1.join();     t2.join();}
