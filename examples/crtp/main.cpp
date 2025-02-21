#include <iostream>
#include <vector>
#include <string>

// CRTP

template<typename T>
class InstancesRegister {
public:
	InstancesRegister(T * t) {
		InstancesRegister<T>::instances.emplace_back(t);
	}

	static std::vector<T*>& getInstances() {
		return InstancesRegister::instances;
	}
private:
	static std::vector<T*> instances;
};

template<typename T>
std::vector<T*> InstancesRegister<T>::instances;

class Airplane: public InstancesRegister<Airplane> { /// <--- CRTP: class X: public Y<X> { ... 
public:
	explicit Airplane(const std::string& name_)
		: InstancesRegister(this), name{name_} {
	}
	void info() const {
		std::cout << "Airplane: " << name << '\n';
	}
private:
	std::string name;
};

int main() {
	Airplane a1("F35");
	{
		Airplane a2("F15");
	}

	/*
	for (auto a: {&a1, &a2}) {
		a->info();
	}
	*/
	for (auto a: Airplane::getInstances()) {
		a->info();
	}
}
