#include <iostream>
#include <future>

std::packaged_task<int(void)> choice_algs(int a) {
	if (a % 2) {
		return std::packaged_task<int(void)>([]() { return 10; } );
	}
	return std::packaged_task<int(void)>([]() { return 20; } );
}

int main() {
	int v = 1213;
	std::packaged_task<int(int)> t1([=](int a) {
		std::cout << "in task\n";
		return v * a * 3.14F;
	});

	auto ftr = t1.get_future();

	/* (1) 
	t1(12);
	std::cout << "result = " << ftr.get() << '\n';
	*/

	/* (2)
	auto thr1 = std::thread(std::move(t1), 12);
	std::cout << "result = " << ftr.get() << '\n';

	thr1.join();
	*/

	// (3)
	t1(23);
	std::cout << ftr.get() << '\n';

	t1.reset();
	ftr = t1.get_future();
	t1(67876);
	std::cout << ftr.get() << '\n';

	auto pt = choice_algs(2);
	auto ftr2 = pt.get_future();
	//std::async(std::launch::async, std::move(pt));
	pt();
	std::cout << ftr2.get() << '\n';

}
