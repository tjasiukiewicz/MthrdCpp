#include <iostream>
#include <future>
#include <thread>
#include <chrono>


int foo(int i) {
	std::cout << "I'm foo() i = " << i << '\n';
	std::this_thread::sleep_for(std::chrono::milliseconds(200));
	return i * 2;
}

int main() {
	std::future<int> ftr = std::async(std::launch::async, foo, 21); // Tu jest 2 wątek...
	std::cout << "In main()\n";
	std::cout << ftr.get() << '\n';
}
