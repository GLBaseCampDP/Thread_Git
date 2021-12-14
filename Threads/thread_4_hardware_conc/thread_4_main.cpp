#include <thread>
#include <vector>
#include <iostream>
using namespace std;
void report( int i ) {  cout << "Thread " << i << " was here\n"; }
int main() {
 unsigned n = thread::hardware_concurrency();
 vector<thread> threads;
 for( unsigned i=0; i < n; ++i )
   threads.push_back( thread(report, i) );
for( auto& t: threads )
  t.join();
 return 0;
}



