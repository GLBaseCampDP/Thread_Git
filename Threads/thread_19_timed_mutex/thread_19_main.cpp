#include <thread>
#include <iostream>
#include <chrono>
#include <mutex>
using namespace std; 
timed_mutex m;
 
void f() {
    auto now=chrono::steady_clock::now();
    m.try_lock_until(now + chrono::seconds(10));
    cout << "hello world\n";
}
int main() {
    lock_guard<timed_mutex> lq(m);
    thread t(f);
    t.join();
}

