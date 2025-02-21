#include <iostream>
#include <vector>
#include <string>

template<typename T>
class InstancesRegister {
protected:
	InstancesRegister() {
		InstancesRegister<T>::instances.emplace_back(static_cast<T*>(this));
	}

public:
	static std::vector<T*>& getInstances() {
		return InstancesRegister::instances;
	}

	~InstancesRegister() {
		std::vector<T*> & inst = InstancesRegister<T>::instances;
		inst.erase(std::remove(inst.begin(), inst.end(), this), inst.end());
	}
private:
	static std::vector<T*> instances;
};

template<typename T>
std::vector<T*> InstancesRegister<T>::instances;

class Airplane: public InstancesRegister<Airplane> { /// <--- CRTP: class X: public Y<X> {
public:
	explicit Airplane(const std::string& name_)
		: name{name_} {
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
