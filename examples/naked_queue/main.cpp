#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <condition_variable>
#include <thread>

std::mutex mtx;
std::queue<int> data_queue;
std::condition_variable cv;
bool doStop = false;

void sender(int data) {
	std::lock_guard<std::mutex> _(mtx);
	data_queue.push(data);
	cv.notify_one();
}

void receiver(const std::string& name) {
	for (;;) {
		std::unique_lock<std::mutex> lk(mtx);
		cv.wait(lk, [] { return (not data_queue.empty()) or doStop; });
		if (doStop and data_queue.empty()) {
			break;
		}
		auto data = data_queue.front();
		data_queue.pop();
		lk.unlock();
		std::cout << "Worker " << name << " data = " << data << std::endl;
	}
}

void shutdown() {
	doStop = true;
	cv.notify_all();
}

int main() {
	std::thread t1(receiver, "First");
	std::thread t2(receiver, "Second");
	for (auto i = 0U; i < 10; ++i) {
		sender(i * 100);
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	//std::this_thread::sleep_for(std::chrono::milliseconds(20));
	shutdown();

	t2.join();
	t1.join();
}
