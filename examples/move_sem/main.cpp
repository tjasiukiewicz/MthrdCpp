#include <iostream>
#include <string>

struct X {
	X()
		: name{new std::string("empty")} {}
	//X(const X&) = delete;
	X(const X& o)
		: name{new std::string(*(o.name))} {
		std::cout << "copy constructor\n";
	}
	X(X&& o)
		: name{o.name} {
		std::cout << "move construct\n";
		o.name = nullptr;
	}
	//X operator=(const X&) = delete;
	X operator=(const X& o) {
		std::cout << "assign operator\n";
		if (o.name != name) {
			delete name;
			name = new std::string(*(o.name));
		} else {
			std::cerr << "?!\n";
		}
		return *this;
	}
	X operator=(X&& o) {
		std::cout << "assign move\n";
		if (o.name != name) {
			delete name;
			name = o.name;
			o.name = nullptr;
		} else {
			std::cerr << "?!\n";
		}
		return *this;
	}
	~X() {
		delete name;
	}
private:
	std::string * name;
};

int main() {

	//X x1;
	//X x2(x1);
	//x2 = x1;
	//X x2 = std::move(x1); // move construct
	
	// assign move
	/*
	X x2;
	x2 = std::move(x1);
	*/
	X x1;
	X x2;
	x2 = std::move(x2);
	/*
	X& x3 = x2;
	x3 = std::move(x2);
	*/


}
