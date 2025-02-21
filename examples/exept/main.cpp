#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <stdexcept>

void foo(std::promise<int>& prm) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    try {
        //throw std::runtime_error("Fake except!");
        prm.set_value(42);
    } catch(...) {
        prm.set_exception(std::current_exception());
    }
}

int main() {
    std::promise<int> prm;
    std::thread thr1(foo, std::ref(prm));
    thr1.detach();
    auto ftr = prm.get_future();
    try {
        std::cout << ftr.get() << '\n';
    } catch(std::runtime_error) {
        std::cout << "Wystąpił wyjątek w wątku\n";
    }
}
