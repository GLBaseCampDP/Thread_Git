// DataExchange.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <future>
#include <thread>

std::promise<int> promise;

void thread_func1() { promise.set_value(10); }
void thread_func2()
{
	std::cout << promise.get_future().get() << std::endl;
}

int main() {
	std::thread th1(thread_func1);
	std::thread th2(thread_func2);
	th1.join();
	th2.join();
	return 0;
}
