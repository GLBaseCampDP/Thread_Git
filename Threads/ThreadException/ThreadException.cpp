// ThreadException.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <future>
#include <thread>

std::promise<int> promise;

void thread_func1() {
	promise.set_exception(std::make_exception_ptr
	(std::runtime_error("fatalerror")));
}

void thread_func2() {
	try {
		std::cout << promise.get_future().get() <<
			std::endl;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

int main() {
	std::thread th1(thread_func1);
	std::thread th2(thread_func2);
	th1.join();
	th2.join();
	return 0;
}
