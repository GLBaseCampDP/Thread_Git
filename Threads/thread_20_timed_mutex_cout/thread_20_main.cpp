#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <sstream>
using namespace std;
// для контролю доступу до  cout
mutex cout_m;
timed_mutex timed_m;
void task(int id) {
    using Ms = chrono::milliseconds;
    ostringstream stream;
    for (int i = 0; i < 3; ++i) {
        if (timed_m.try_lock_for(Ms(100))) {
            stream << "success ";
            this_thread::sleep_for(Ms(100));
            timed_m.unlock();

       } else {
            stream << "failed ";
        }
        this_thread::sleep_for(Ms(100));
    }
    lock_guard<mutex> lock(cout_m);
    cout << "[" << id << "] " << stream.str() << "\n";
}
int main() {
    vector<thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(task, i);
    }
    for (auto& i: threads) {
        i.join();
    }
    return 0; }
