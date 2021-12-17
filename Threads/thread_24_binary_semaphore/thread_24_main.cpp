#include <iostream>
#include <thread>
#include <chrono>
#include <semaphore>
using namespace std;
// глобальні інстанси семафорів в захопленому режимі
binary_semaphore sm_main2thread(0), 
                 sm_thread2main(0);
void f(){    
  // очікування сигналу від main для декременту семафора
  sm_main2thread.acquire();
 
  using namespace literals;
  this_thread::sleep_for(3s);
  // сигнал для main 
  sm_thread2main.release();
}  

  int main() {
    thread t(f);
 
    // інкрементом лічильника 
    // посилається сигнал в потік
    sm_main2thread.release();
 
    // очікування поки відпрацює потік і 
    //надішле сигнал
    sm_thread2main.acquire();


     t.join();
}
