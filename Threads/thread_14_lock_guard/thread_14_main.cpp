#include <vector>
#include <mutex>
#include <thread>
using namespace std;
vector<int> x;
mutex m;
#include <chrono>


void f1() {
  this_thread::sleep_for(chrono::seconds(10));
  lock_guard<mutex> lock(m);
  x.push_back(0);
}
void f2() {
  lock_guard<mutex>
    lock(m);
  x.pop_back();
}
int main() {
  thread t1(f1);
  thread t2(f2);
  t1.join();
  t2.join();
  return 0;
}


