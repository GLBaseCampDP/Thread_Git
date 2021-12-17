#include <vector>
#include <mutex>
#include <thread>
using namespace std;


vector<int> x;
mutex m;


void f1() {
  m.lock();
  x.push_back(0);
  m.unlock();
}
void f2() {
  m.lock();
  x.pop_back();
  m.unlock();
}




int main() {
  thread t1(f1);
  thread t2(f2);
  t1.join();
  t2.join();
  return 0;
}
