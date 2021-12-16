#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <functional>
using namespace std;
int f(int x, int y) { return x + y; }
int main(){
  // job - lambda
  packaged_task<int(int,int)> 
       job_lambda([](int a, int b) {
        return a + b;
  });
  future<int> res_lambda = job_lambda.get_future();
  job_lambda(1, 1);
  cout << " job_lambda:\t" << res_lambda.get() << '\n';
  // job - bind
  packaged_task<int()> job_bind(bind(f, 2, 2));
  future<int> res_bind = job_bind.get_future();
  job_bind();
  cout << "job_bind:\t" << res_bind.get() << '\n';
  // job - thread
  packaged_task<int(int,int)> job_thread(f);
  future<int> res_thread = job_thread.get_future();
  thread t1(std::move(job_thread), 3, 3);
  t1.join();
  cout << " job_thread:\t" << res_thread.get() << '\n';
 // job - after_reset
  job_lambda.reset();
  res_lambda = job_lambda.get_future();
  thread t2(move(job_lambda),4,4);
  t2.join();
  cout << " after reset:\t" << res_lambda.get() << '\n';
  return 0;}

