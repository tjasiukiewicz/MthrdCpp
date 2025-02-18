#include <thread>
#include <mutex>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class SeaMan {
public:
	constexpr static int RoadSize = 20;
	SeaMan()
		: position{RoadSize / 2}, stop{false} {
		thrLeft = std::thread(&SeaMan::changePosition, this, -1);
		thrRight = std::thread(&SeaMan::changePosition, this, 1);
	}
	~SeaMan() {
		thrRight.join();
		thrLeft.join();
	}

private:
	void showRoad() const {
		{
			std::lock_guard<std::mutex> _(mtx);
			std::cout << "|" << std::string(position, '-') << "*" << std::string(RoadSize - position, '-') << "|\n";
		}
	}

	void changePosition(int delta) {
		while(not stop) {
			if ((position == 0) or (position >= RoadSize)) {
				stop = true;
				break;
			}
			{
				std::lock_guard<std::mutex> _(mtx);
				position += delta;
			}
			//std::this_thread::sleep_for(std::chrono::milliseconds(50 - delta * 10 ));
			//std::this_thread::sleep_for(std::chrono::milliseconds(50 + delta * 10 ));
			auto tme = rand() % 50;
			std::this_thread::sleep_for(std::chrono::milliseconds(tme));
			showRoad();
		}
	}
	int position;
	std::thread thrLeft;
	std::thread thrRight;
	mutable std::mutex mtx;
	bool stop;
};

int main() {
	srand(time(NULL));
	SeaMan sm;
}
