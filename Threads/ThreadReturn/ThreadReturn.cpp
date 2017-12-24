// ThreadReturn.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <iostream>
#include <future>
#include <thread>

int calculate() {
	return 2 * 2;
}

int main() {
	std::future<int> result = std::async(calculate);
	std::cout << result.get() << std::endl;
}
