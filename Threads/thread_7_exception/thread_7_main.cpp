#include <iostream>
#include <future>
#include <thread>
using namespace std;
promise<int> p;


void f1() {
 p.set_exception(make_exception_ptr
  (runtime_error("fatalerror")));
}


void f2() {
  try {
   cout << p.get_future().get() <<
     endl;
  }
  catch (const exception& e) {
  cout << e.what() << endl;
 }
}


int main() {
  thread t1(f1);
  thread t2(f2);
  t1.join();
  t2.join();
}
