#include <iostream>
#include <stack>
#include <mutex>
#include <thread>
#include <memory>
#include <chrono>

template<typename T>
class ThStack {
public:
	ThStack()
		: data{}, stop{false} {}

	~ThStack() {
		doStop();
	}

	void doStop() {
		std::lock_guard<std::mutex> _(mtx);
		stop = true;
	}

	bool push(T val) {
		{
			std::lock_guard<std::mutex> _(mtx);
			if (stop) {
				return false;
			}
			data.push(val);
		}
		return true;
	}

	bool pop(T & val) {
		if (std::lock_guard<std::mutex> _(mtx); (not stop) or (not data.empty())) {
			val = data.top();
			data.pop();
			return true;
		}
		return false;

	}

	std::shared_ptr<T> pop() {
		if (std::lock_guard<std::mutex> _(mtx); not data.empty()) { // !!!
			auto val = std::make_shared<T>(data.top());
			data.pop();
			return val;
		}
		return {};
	}

	std::size_t size() const {
		std::lock_guard<std::mutex> _(mtx);
		return data.size();
	}

private:
	std::stack<T> data;
	mutable std::mutex mtx;
	bool stop;
};

void producer(ThStack<int>& th) {
	for (auto i = 0; i < 10; ++i) {
		th.push(i);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void consumer(ThStack<int>& th) {
	for (auto i = 0; i < 10; ++i) {
		std::shared_ptr<int> sp;
		sp = th.pop();
		std::cout << "consumer: ";
		if (sp) {
			std::cout << *sp << '\n';
		} else {
			std::cout << "empty" << '\n';
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}

int main() {
	ThStack<int> th;
	auto pth1 = std::thread(producer, std::ref(th));
	auto cth1 = std::thread(consumer, std::ref(th));
	auto cth2 = std::thread(consumer, std::ref(th));

	std::this_thread::sleep_for(std::chrono::milliseconds(700));
	th.doStop();

	cth2.join();
	cth1.join();
	pth1.join();
}
