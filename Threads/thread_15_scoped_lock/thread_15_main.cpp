#include <iostream>
#include <mutex>
#include <thread>
#include <mutex> 
using namespace std;   
mutex m1, m2;  
void f1 () {
   scoped_lock lg(m1, m2);
   this_thread::sleep_for(
      chrono::milliseconds(10));
};
void f2() {
   scoped_lock lg(m1, m2);
   this_thread::sleep_for(
       chrono::milliseconds(10));
};


int main() {
 thread t1([&]() {f1();});
 thread t2([&]() {f2();});
 t1.join();  
 t2.join();
 return 0;
}
