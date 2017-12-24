// Trhead ID.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <thread>
#include <iostream>

void thread_func()
{
	std::cout << std::this_thread::get_id() << std::endl;
}

int main(int argc, char * argv[])
{
	std::thread th(thread_func);
	std::thread::id th_id = th.get_id();
	th.join();
	std::cout << th_id << std::endl;
	return 0;
}

