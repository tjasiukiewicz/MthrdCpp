#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>

void work(int i ) {
	std::cout << "I'm work() i = " << i << '\n';
	auto val = rand() % 100;
	std::this_thread::sleep_for(std::chrono::milliseconds(200 + val));
}

int main() {
	srand(time(NULL));

	std::vector<std::future<void>> jobs;
	for(auto i = 0U; i < 8; ++i) {
		auto ftr = std::async(std::launch::async, work, i);
		jobs.emplace_back(std::move(ftr));
	}
	std::cout << "I'm main()\n";

	/*
	for(auto & ftr: jobs) {
		ftr.get();
	}
	*/
}

