// Create Thread.cpp: определ€ет точку входа дл€ консольного приложени€.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <atomic>
#include <string>
#include <stdio.h>
#include <system_error>

using namespace std;

void say(string& s) {
	while (getchar() != 'c')
		cout << "ItТs my first " << s << endl ;
}

void say_all() {
		cout << "ItТs my second THREAD" << endl ;
}

void say_one(int i, double d, const std::string s) {
	cout << "ItТs my third " << s << endl ;
}

void say_error(int& i) {
	cout << "ItТs my error THREAD " << i << endl;
}

void main() {
	try 	{
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


