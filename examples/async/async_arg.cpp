#include <iostream>
#include <future>

void foo(int & c) {
}

class X {
public:
	void operator()() {
		std::cout << "X operator()\n";
	}
	void go(double a) {
		std::cout << "X go() a = " << a << '\n';
	}
};

int main() {
	int a = 12;
	X x;
	auto ftr = std::async(std::launch::async, foo, std::ref(a));
	ftr.get();

	ftr = std::async(std::launch::async, x);
	ftr.get();

	ftr = std::async(std::launch::async, &X::go, &x, 12.3);
	ftr.get();

	ftr = std::async(std::launch::async, [](int a) { std::cout << a << '\n'; }, 378);
	ftr.get();

	// 
	ftr = std::async(std::launch::deferred, [](int a) { std::cout << a << '\n'; }, 378); // NIE URUCHAMIA ASYNCHRONICZNIE!!!
	ftr.get(); // DOPIERO TU URUCHOAMIA POPRZENIĄ LINIĘ!!!
}
