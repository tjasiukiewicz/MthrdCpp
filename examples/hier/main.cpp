#include <iostream>
#include <exception>
#include <mutex>
#include <limits>

class hierarchical_mutex {
public:
    explicit hierarchical_mutex(unsigned value):
        hierarchy_value{value}, previous_hierarchy_value{} {}

    void lock() {
        check_hierarchy_volation();
        internal_mutex.lock();
        update_hierarchy_value();
    }

    void unlock() {
        this_thread_value = previous_hierarchy_value;
        internal_mutex.unlock();
    }

    bool try_lock() {
        check_hierarchy_volation();
        if(!internal_mutex.try_lock()) {
            return false;
        }
        update_hierarchy_value();
        return true;
    }
private:
    void check_hierarchy_volation() {
        if(this_thread_value <= hierarchy_value) {
            throw std::logic_error("Mutex hierarchy volation");
        }
    }

    void update_hierarchy_value() {
        previous_hierarchy_value = this_thread_value;
        this_thread_value = hierarchy_value;
    }

    std::mutex internal_mutex;
    unsigned const hierarchy_value;
    unsigned previous_hierarchy_value;
    static thread_local unsigned this_thread_value;
};

thread_local unsigned hierarchical_mutex::this_thread_value{
    std::numeric_limits<unsigned>::max()
};

hierarchical_mutex high_level_mutex(10000);
hierarchical_mutex low_level_mutex(5000);
hierarchical_mutex other_mutex(100);

int low_level_work() {
    return 42; 
}

int high_level_work(int value) {
    return value + 100;
}

void other_work() {
    ;
}

int low_level_function() {
    std::lock_guard<hierarchical_mutex> l(low_level_mutex);
    return low_level_work();
}

int high_level_function() {
    std::lock_guard<hierarchical_mutex> l(high_level_mutex);
    return high_level_work(low_level_function());
}

void other_function() {
    high_level_function();
    other_work();
}

void in_thread_a() {
    high_level_function();
}

void in_thread_b() {
    std::lock_guard<hierarchical_mutex> l(other_mutex);
    other_function();
}

int main() {
    in_thread_a();
    //in_thread_b(); // illegal use... 
}
