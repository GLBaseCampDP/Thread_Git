# include <mutex>
# include <thread>
# include <chrono>
using namespace std;
struct A {
    explicit A(int j): i {j} {}
    int i;
    mutex m;
};
void f(A& a1, A& a2, int j){
   // відтерміноване захоплення
    unique_lock<mutex> 
       lock1(a1.m, defer_lock);
    unique_lock<mutex> 
       lock2(a2.m, defer_lock);

    // блокування  обох м'тексів без deadlock
    lock(lock1, lock2);
    a1.i -= j;
    a2.i += j;
    // деблокування  обох м'ютексів у dtor 'unique_lock'
}
int main() {
    A a(100);
    A b(50);
    thread t1(f, ref(a), ref(b), 10);
    thread t2(f, ref(b), ref(a), 5);
    t1.join();
    t2.join();
    return 0;
}
