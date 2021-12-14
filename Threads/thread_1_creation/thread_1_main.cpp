#include <iostream>

#include <thread>

#include <atomic>
#include <string>
#include <stdio.h>
#include <system_error>
using namespace std;
void say(string& s) {
 while (getchar() != 'c')
 cout << "It’s my first " << s << endl ;
}

void say_all() {
 cout << "It’s my second THREAD" << endl ;
}

void say_one(int i, double d, const string s) {
 cout << "It’s my third " << s << endl ;
}

void say_error(int& i) {
 cout << "It’s my error THREAD " << i << endl;
}
int main() {
 try {
   thread thr0;
   string mes("THREAD");
   thread thr1(say, ref(mes));
   thread thr2(say_all);
   thread thr3(say_one, 100, 3.14, "THREAD");
   int n = -1;
   thread thr4(say_error, ref(n));
   thread thr5(move(thr4));
   thr1.join();
   thr2.join();
   thr3.join();
   //thr4.join();
   thr5.join();
 }
 catch (const system_error e) {}
}
