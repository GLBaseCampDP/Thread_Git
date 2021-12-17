#include <iostream>
#include <thread>
#include <mutex>
using namespace std; 
struct A {
  recursive_mutex m;
  string data;
  void f1() {
    lock_guard<recursive_mutex> ulk(m);
    data = "f1";
    cout << "in f1: " << data << '\n';
  }
  void f2() {
    lock_guard<recursive_mutex> ulk(m);
    data = "f2";

    cout << "in f2: " << data <<'\n';
    f1(); // використання рекурсивного м'ютекса
      cout << "in f2: " << data << '\n';
    };
};


int main() {
    A a;
    thread t1(&A::f1, &a);
    thread t2(&A::f2, &a);
    t1.join();
    t2.join();
    return 0;
}
