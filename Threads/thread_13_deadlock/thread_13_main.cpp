#include <iostream>
#include <mutex>
#include <thread>
#include <mutex>
using namespace std;
mutex m1, m2;
void f1 () {
   lock_guard<mutex> lg1(m1);
   this_thread::sleep_for(chrono::milliseconds(10));
   lock_guard<mutex> lg2(m2);
};
void f2() {
    lock_guard<mutex> lg1(m2);
    this_thread::sleep_for(chrono::milliseconds(10));
    lock_guard<mutex> lg2(m1);
};

void f2n() {
    lock_guard<mutex> lg1(m1);
    this_thread::sleep_for(
      chrono::milliseconds(10));
    lock_guard<mutex> lg2(m2);
};


int main() {
 thread t1([&]() {f1();});
 // deadlock
 thread t2([&]() {f2();});
 // no deadlock
 thread t3([&]() {f2n();});
 t1.join();  t2.join();   t3.join();
 return 0;
}
