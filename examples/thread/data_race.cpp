#include <iostream>
#include <thread>
#include <chrono>
#include <cassert>
#include <mutex>

volatile int counter = 65535; //  0x0000 FFFF + 1 = 0x0001 0000
std::mutex mtx;


void worker(int delta) {
	for (auto i = 0U; i < 100; ++i) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		{
			std::lock_guard<std::mutex> _(mtx);

			//mtx.lock();

			counter += delta;

			//mtx.unlock();
		}
	}
}

int main() {
	auto thr1 = std::thread(worker, 1);
	auto thr2 = std::thread(worker, -1);

	thr2.join();
	thr1.join();

	std::cout << "counter = " << counter << '\n';
	assert(counter == 65535);
}
