#include <mutex>
#include <thread>
#include <iostream>
using namespace std;
struct x {
  x() {
    cout << this_thread::get_id() <<
    endl;
  }
};
x* instance;
void create_x() {
  instance = new x();
}
once_flag instance_flag;


void f() {
  call_once(instance_flag, create_x);
}


int main() {
  thread t1(f);
  thread t2(f);
  t1.join();
  t2.join();
  return 0;
}
