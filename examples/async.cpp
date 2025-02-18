#include <iostream>
#include <future>

void foo(int i) {
	std::cout << "I'm foo() i = " << i << '\n';
}

int main() {
	for(auto i = 0U; i < 32; ++i) {
		std::async(std::launch::async, foo, i);
	}

}
