#include <iostream>
#include <chrono>
#include <thread>
#include <future>

struct Executor {
	template<typename Duration, typename Function, typename... Args>
	static void periodic(Duration duration, Function && func, Args... args) {
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		while(not Executor::stop) {
			auto next_point = now + duration;
			func(std::forward<Args>(args)...);
			std::this_thread::sleep_until(next_point);
			now = next_point;
		}
	}
	static void doStop() {
		Executor::stop = true;
	}
private:
	static bool stop;
};

bool Executor::stop = false;


void ping() {
	std::cout << "Ping!\n";
}

int main() {
	auto ftr = std::async(std::launch::async, [] {
			Executor::periodic(std::chrono::seconds(1), ping);
	});

	for (auto i = 0U; i < 10; ++i) {
		std::cout << "Work in main()\n";
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	Executor::doStop();
	ftr.get();
}
