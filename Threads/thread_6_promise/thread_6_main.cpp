#include <iostream>
#include <future>
#include <thread>
using namespace std;
promise<int> p;


void f1() { p.set_value(10); }
void f2() {  cout << p.get_future().get() << endl; }


int main() {
  thread t1(f1);
  thread t2(f2);
  t1.join();
  t2.join();
}
