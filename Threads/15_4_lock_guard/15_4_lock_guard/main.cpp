#include <vector>
#include <mutex>
#include <thread>

std::vector<int> x;
std::mutex mutex;

void thread_func1() {
  std::lock_guard<std::mutex> lock(mutex);
  x.push_back(0);
}

void thread_func2() {
  std::lock_guard<std::mutex> lock(mutex);
  x.pop_back();
}

int main() {

std::thread th1(thread_func1);
std::thread th2(thread_func2);

th1.join();
th2.join();

}
