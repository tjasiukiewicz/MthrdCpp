#include <condition_variable>
#include <mutex>

// PSEUDO CODE!!!

std::mutex mtx;
std::condition_variable cv;

int main() {
	{
		std::unique_lock<std::mutex> lk(mtx);
		cv.wait(lk, []() { return x > 1200; });
		//
		// Diałanie po cv, na ZABLOKOWANYM mtx.
	}

	cv.notify_one();
	cv.notify_all();


}
