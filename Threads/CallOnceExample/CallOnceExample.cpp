// CallOnceExample.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <mutex>
#include <thread>
#include <iostream>
struct x {
	x() {
		std::cout << std::this_thread::get_id() <<
			std::endl;
	}
};
x* instance;
void create_x()
{
	instance = new x();
}
std::once_flag instance_flag;

void thread_func()
{
	std::call_once(instance_flag, create_x);
}
int main()
{
	std::thread th1(thread_func);
	std::thread th2(thread_func);
	th1.join();
	th2.join();
	return 0;
}
