#include <thread>
#include <iostream>
using namespace std;
void thread_func() {   cout << this_thread::get_id()  << endl;  }


int main() {
 thread th(thread_func);
 thread::id th_id = th.get_id();
 th.join();
 cout << th_id << endl;
 return 0;
}
