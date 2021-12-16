#include <iostream>
#include <future>
#include <chrono>
using namespace std;
int main(){
    promise<void> ready_prm, t1_ready_prm, t2_ready_prm;
    shared_future<void> ready_future(ready_prm.get_future());
    chrono::time_point<chrono::high_resolution_clock> start;
    auto f1 = [&, ready_future]() -> chrono::duration<double, milli>{
        t1_ready_prm.set_value();
        ready_future.wait(); // очікування сигналу від main()
        return chrono::high_resolution_clock::now() - start;
    };
    auto f2 = [&, ready_future]() -> chrono::duration<double, milli>{
        t2_ready_prm.set_value();
        ready_future.wait(); // очікування сигналу від main()
        return chrono::high_resolution_clock::now() - start;
    };

    auto fut1 = t1_ready_prm.get_future();
    auto fut2 = t2_ready_prm.get_future();
    auto res1 = async(launch::async, f1);
    auto res2 = async(launch::async, f2);
    // очікування поки потоки стануть ready
    fut1.wait();
    fut2.wait();
    // потоки ready, запуск годинника
    start = chrono::high_resolution_clock::now();
    // сигнал для потоків виконуватись
    ready_prm.set_value();


    cout << "Thread 1 received the signal "
              << res1.get().count() << " ms after start\n"
              << "Thread 2 received the signal "
              << res2.get().count() << " ms after start\n";
}

