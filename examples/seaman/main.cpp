#include <thread>
#include <mutex>
#include <iostream>
#include <string>

class SeaMan {
public:
	constexpr static int RoadSize = 20;
	SeaMan()
		: position{RoadSize / 2}, stop{false} {
		thrLeft = std::thread(&SeaMan::changePosition, this, -1);
		thrRight = std::thread(&SeaMan::changePosition, this, 1);
	}
	~SeaMan() {
		stop = true; //  ???
		thrRight.join();
		thrLeft.join();
	}

private:
	void showRoad() const {
		// mtx ??
		std::cout << "|" << std::string(position, '-') << "*" << std::string(RoadSize - position, '-') << "|\n";
	}

	void changePosition(int delta) {
		while(not stop) {
			if ((position == 0) or (position >= RoadSize)) {
				stop = true;
			}
			{
				// mtx?
				position += delta;
			}
			std::this_thread::sleep_for(std::milliseconds(20));
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
	SeaMan sm;
}
