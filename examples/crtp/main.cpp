#include <iostream>
#include <vector>
#include <string>

class Airplane {
public:
	explicit Airplane(const std::string& name_)
		: name{name_} {}
	void info() const {
		std::cout << "Airplane: " << name << '\n';
	}
private:
	std::string name;
};

int main() {
	Airplane a1("F35");
	Airplane a2("F15");

	for (auto a: {&a1, &a2}) {
		a->info();
	}
}
