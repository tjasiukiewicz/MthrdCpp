#include <iostream>
#include <thread>
#include <chrono>
#include <cassert>

int counter = 65535;


void worker(int delta) {
	for (auto i = 0U; i < 100; ++i) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		counter += delta;
	}
}

int main() {
	auto thr1 = std::thread(worker, 1);
	auto thr2 = std::thread(worker, -1);

	thr2.join();
	thr1.join();

	assert(counter == 65535);
}
