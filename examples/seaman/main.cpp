#include <thread>
#include <mutex>
#include <iostream>
#include <string>

class SeaMan {
public:
	constexpr static int RoadSize = 20;
	SeaMan()
		: position{RoadSize / 2} {
	}

	void showRoad() const {
		std::cout << "|" << std::string(position, "*") << "|\n";
	}

private:
	int position;
	std::thread thrLeft;
	std::thread thrRight;
	std::mutex mtx;
};

int main() {
	SeaMan sm;
}
