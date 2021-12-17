#include <vector>
#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>
using namespace std;


vector<int> d;
condition_variable data_cond;
mutex m;
void f1() {
  unique_lock<mutex> lock(m);
  d.push_back(10);
  data_cond.notify_one();
}
void f2() {
  unique_lock<mutex> lock(m);
  data_cond.wait(lock,
    [] { return !d.empty(); });
  cout << d.back() << endl;
}


int main() {
  thread t1(f1);
  thread t2(f2);
  t1.join();
  t2.join();
  return 0;
}
