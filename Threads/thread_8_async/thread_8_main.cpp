#include <iostream>
#include <future>
#include <thread>
using namespace std;

int calculate() {
  return 2 * 2;
}

int main() {
  future<int> result =
       async(calculate);
  cout << result.get() << endl;
}
