#include <iostream>
#include <thread>
#include <chrono>

void foo(int id) {
	std::cout << "foo() id = " << id << '\n';
}

int main() {
	auto thr1 = std::thread(foo, 1);
	std::thread thr2 = std::thread(foo, 2);
	std::thread thr3 = std::thread([](int a) { std::cout << "lam a = " << a << '\n'; }, 3);
	//std::thread thr4 = std::move(thr3);


	//std::this_thread::sleep_for(std::chrono::seconds(3));

	for (auto t: {&thr4, &thr3, &thr2, &thr1}) {
		if (t->joinable()) {
			t->join();
		}
	}
}
