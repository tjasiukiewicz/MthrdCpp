#include <future>
#include <thread>
#include <chrono>
#include <iostream>

void work() {
	int count = 5;
	while(count--) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::cout << "work" << std::endl;
	}
}

int main() {
	auto ftr = std::async(std::launch::async, work);
	std::future_status status;
	do {
		switch(status = ftr.wait_for(std::chrono::milliseconds(500)); status) {
			case std::future_status::deferred:
				std::cout << "deffered (not run yet?)" << std::endl;
				break;
			case std::future_status::timeout:
				std::cout << "timeout  (still running)" << std::endl;
				break;
			case std::future_status::ready:
				std::cout << "ready    (complete)" << std::endl;
				break;
		}
	} while(status != std::future_status::ready);
	ftr.get();
}
