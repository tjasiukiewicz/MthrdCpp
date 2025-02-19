#include <iostream>

template<typename ...Args>
void foo(Args... args) {
	std::cout << "elements: " << sizeof...(args) << '\n';
}

template<typename T>
void show_args(T a) {
	std::cout << a << '\n';
}

template<typename T, typename... Args>
void show_args(T a, Args... args) {
	std::cout << a << ' ';
	show_args(args...);
}

template<typename Func, typename... Args> 
void executor(Func func, Args... args) {
	std::cout << "Exec func\n";
	func(std::forward<Args>(args)...);
}

void greet(int && a, const char * msg) {
	std::cout << a << ' ' << msg << '\n';
}

/*
template<typename... Parents>
class X: public Parents... {
};
*/


int main() {
	int var = 42;
	/*
	foo(1, 2, 3.14, "ala");
	foo("ble", 'a', 43, 34, 434, 434);
	*/

	//show_args(1, 3, "Adam", 12.434, 656.34F);
	
	executor(greet, std::move(var), "word");

}
