#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

struct Barier {
	explicit Barier(unsigned count) {}
	void wait() {}
private:
	const unsigned max_counter;
	unsigned current_counter;
	mutable std::mutex mtx;
	std::condition_variable vc;

};

int main() {
	Barier bar(3);
	std::thread thr1([](Barier& bar) { bar.wait(); std::cout << "thr1\n"; }, std::ref(bar));
	std::thread thr2([](Barier& bar) { bar.wait(); std::cout << "thr2\n"; }, std::ref(bar));    
	std::thread thr3([](Barier& bar) { bar.wait(); std::cout << "thr3\n"; }, std::ref(bar));    
    
	thr3.join();    
	thr2.join();    
	thr1.join();
}
