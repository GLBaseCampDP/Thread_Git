#include <mutex>
#include <thread>
#include <iostream>
#include <ostream>
#include <vector>
#include <functional>
#include <chrono>
#include <string>
using namespace std;
struct A {
    A(string idx) : id(idx) {}
    string id;
    vector<string> friends;
    mutex m;
};
ostream& operator<<(ostream& stream, A& a ){
    string ret = a.id +" friends " +  ": ";
    for( const auto& fr : a.friends )
            ret += fr + " ";
    stream << ret; return stream; }


void meet(A &, A &) {
    this_thread::sleep_for(chrono::seconds(1));
}


void add_friend(A &e1, A &e2) {
    static mutex io_mtx;
    cout << e1.id << " & " << e2.id << ": waiting for locks " << endl;
    lock(e1.m, e2.m);
    lock_guard<mutex> lg1(e1.m, adopt_lock);
    lock_guard<mutex> lg2(e2.m, adopt_lock);
    cout << e1.id << " & " << e2.id << ": got locks " << endl;
    e1.friends.push_back(e2.id);
    e2.friends.push_back(e1.id);
    meet(e1, e2);
}


int main() {
    A a("a"), b("b"), c("c"), d("d");
    vector<thread> threads;
    threads.emplace_back(add_friend, ref(a), ref(b));
    threads.emplace_back(add_friend, ref(c), ref(b));
    threads.emplace_back(add_friend, ref(c), ref(a));
    threads.emplace_back(add_friend, ref(d), ref(b));
    for (auto &thread : threads)
        thread.join();
    cout << a << '\n'  << b << '\n'
         << c << '\n' << d << '\n';
    return 0;
}

