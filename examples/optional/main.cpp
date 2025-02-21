#include <iostream>
#include <optional>

std::optional<int> myDiv(int a, int b) {
	if (b == 0) {
		return {};
	}
	return {a / b};
}

int main() {
	auto opt = myDiv(12, 2);
	if (opt.has_value()) {
		//std::cout << "result = " << opt.value() << '\n';
		std::cout << "result = " << *opt << '\n';
	} else {
		std::cout << "result = not exsist!\n";
	}
}
