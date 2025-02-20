#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <condition_variable>
#include <thread>

std::mutex mtx;
std::queue<int> data_queue;
std::condition_variable cv;

void sender(int data) {
	// TODO: Push data to data_queue
}

void receiver(const std::string& name) {
	for (;;) {
		// TODO : Get front data from data_queue
	}
}

int main() {
	std::thread t1(worker, "First");
	std::thread t2(worker, "Second");
	for (auto i = 0U; i < 10; ++i) {
		sender(i * 100);
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
