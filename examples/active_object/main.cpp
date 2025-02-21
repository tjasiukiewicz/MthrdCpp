#include <thread>
#include <future>
#include <vector>
#include <functional>
#include <queue>
#include <chrono>
#include <mutex>
#include <string>
#include <iostream>

class ActiveObject {
public:
    using submit_work_t = void (ActiveObject::*)(std::string);

    ActiveObject(): stop{false} {
        work_thread = std::thread(&ActiveObject::worker, this);
    }

    ~ActiveObject() {
        doStop();
        work_thread.join();
    }

    void process(submit_work_t mthd, std::string msg) {
        std::cout << "Task submited" << std::endl;
        if(!stop) {
            std::lock_guard<std::mutex> _(work_mutex);
            work_queue.push(
                    std::packaged_task<void()>(std::bind(mthd, this, msg)));
        }
    }

    void work1(std::string msg) {
        using namespace std::chrono_literals;
        {
            std::lock_guard<std::mutex> _(cout_mutex);
            std::cout << "start work1() " << msg << std::endl;
        }
        std::this_thread::sleep_for(1s);
        {
            std::lock_guard<std::mutex> _(cout_mutex);
            std::cout << "end work1()   " << msg << std::endl;
        }
    }

    void work2(std::string msg) {
        using namespace std::chrono_literals;
        {
            std::lock_guard<std::mutex> _(cout_mutex);
            std::cout << "start work2() " << msg << std::endl;
        }
        std::this_thread::sleep_for(2s);
        {
            std::lock_guard<std::mutex> _(cout_mutex);
            std::cout << "end work2()   " << msg << std::endl;
        }
    }

    void doStop() {
        stop = true;
    }
private:
    void worker() {
        // Immediate stopping work with even if full queue.
        while(!stop) {
            std::unique_lock<std::mutex> l(work_mutex);
            if(!work_queue.empty()) {
                auto task = std::move(work_queue.front());
                work_queue.pop();
                l.unlock();
                auto ftr = task.get_future();
                task();
                ftr.get();
            }
        } 
    }

    std::queue<std::packaged_task<void()>> work_queue;
    std::thread work_thread;
    std::mutex work_mutex;
    bool stop;
    std::mutex cout_mutex;
};

int main() {

    ActiveObject ac;
    ac.process(&ActiveObject::work1, "first");
    ac.process(&ActiveObject::work2, "second");
    std::this_thread::sleep_for(std::chrono::seconds(7));
    ac.doStop();
    ac.process(&ActiveObject::work1, "thrid");
    ac.process(&ActiveObject::work2, "forth");
    ac.process(&ActiveObject::work2, "fifth");

    std::this_thread::sleep_for(std::chrono::seconds(7));
}
