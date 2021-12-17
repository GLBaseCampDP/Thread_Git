#include <mutex>
#include <thread>
#include <condition_variable>
#include <cassert>
#include <string>
using namespace std;
mutex m;
condition_variable cv;
bool ready = false;
string s = "24"; 
 
void f(){
  thread_local string thread_local_data = "42";
  unique_lock<mutex> lk(m);
  // присвоєння значення s 
  // з використання thread_local_data
  s = thread_local_data;
ready = true;
  notify_all_at_thread_exit(cv, move(lk));
}   // 1. знищення thread_locals
    // 2. unlock mutex
    // 3. notify cv
 
int main(){
    thread t(f);
    t.detach();
    ...
    // очікування на detached потік
    unique_lock<mutex> lk(m);
    cv.wait(lk, []{ return ready; });
    // sмодифікована і коректно знищений потік 
    assert(s== "42");
    retrun 0;
}


