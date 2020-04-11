#include <iostream>
#include <thread>
#include <atomic>
#include <string>
#include <stdio.h>
#include <system_error>
using namespace std;
void say(std::string& s) {
 while (getchar() != 'c')
 std::cout << "It’s my first " << s << endl ;
}

void say_all() {
 std::cout << "It’s my second THREAD" << endl ;
}

void say_one(int i, double d, const std::string s) {
 std::cout << "It’s my third " << s << endl ;
}

void say_error(int& i) {
 std::cout << "It’s my error THREAD " << i << endl;
}
int main() {
 try {
   std::thread thr0;
   string mes("THREAD");
   std::thread thr1(say, std::ref(mes));
   std::thread thr2(say_all);
   std::thread thr3(say_one, 100, 3.14, "THREAD");
   int n = -1;
   std::thread thr4(say_error, std::ref(n));
   std::thread thr5(std::move(thr4));
   thr1.join();
   thr2.join();
   thr3.join();
   //thr4.join();
   thr5.join();
 }
 catch (const std::system_error e) {}
}
