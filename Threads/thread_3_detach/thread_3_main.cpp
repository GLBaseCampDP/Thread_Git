#include <iostream>
#include <thread>
using namespace std;
void f () {   cout << "Hello" << endl; }

/*int main() {
    thread t(f);
    t.detach();
    t.join(); // CRASH !!!
    return 0;
}*/

int main() {
  thread t(f);
  t.detach();
  if (t.joinable())  {
    t.join();
  }
  return 0;
}


