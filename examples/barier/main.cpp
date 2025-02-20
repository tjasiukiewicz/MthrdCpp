#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

struct Barier {
	explicit Barier(unsigned counter)
		: max_counter{counter}, current_counter{counter} {}

	void wait() {
		std::unique_lock<std::mutex> lk(mtx);
		if (current_counter == 0) {
			current_counter = max_counter;
		}
		--current_counter;
		cv.wait(lk, [this]{ return current_counter == 0; });
		lk.unlock();
		cv.notify_all();
	}
private:
	const unsigned max_counter;
	unsigned current_counter;
	mutable std::mutex mtx;
	std::condition_variable cv;

};

int main() {
	Barier bar(3);
	std::thread thr1([](Barier& bar) { bar.wait(); std::cout << "thr1\n"; }, std::ref(bar));
	std::thread thr2([](Barier& bar) { bar.wait(); std::cout << "thr2\n"; }, std::ref(bar));    
	std::thread thr3([](Barier& bar) { bar.wait(); std::cout << "thr3\n"; }, std::ref(bar));    

	std::thread thr4([](Barier& bar) { bar.wait(); std::cout << "thr4\n"; }, std::ref(bar));    
	std::thread thr5([](Barier& bar) { bar.wait(); std::cout << "thr5\n"; }, std::ref(bar));    
	std::thread thr6([](Barier& bar) { bar.wait(); std::cout << "thr6\n"; }, std::ref(bar));    
    
	thr6.join();    
	thr5.join();    
	thr4.join();    

	thr3.join();    
	thr2.join();    
	thr1.join();
}
