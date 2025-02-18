#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

int producer() {
	std::cout << "I'm producer!\n";
	std::this_thread::sleep_for(std::chrono::seconds(3));
	return rand() % 10;
}

void consumer(std::shared_future<int> sf) {
	std::cout << "start consumer!!\n";
	std::cout << "value from sf = " << sf.get() << '\n';
	std::cout << "stop consumer!!\n";
}

int main() {
	srand(time(NULL));
	std::shared_future<int> sftr = std::async(std::launch::async, producer);
	auto cftr1 = std::async(std::launch::async, consumer, sftr);
	auto cftr2 = std::async(std::launch::async, consumer, sftr);

	cftr2.get();
	cftr1.get();
}
