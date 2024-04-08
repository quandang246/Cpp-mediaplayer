#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <atomic>

class DispatchQueue {
private:
    // a queue that each element in this queue is a callable object (void function) 
    std::queue<std::function<void()>> tasks;
    // mutex (mutual exclusion) - synchronize access to shared resources (in this case, the tasks queue) among multiple threads. 
    std::mutex mutex;
    // condition variable -  It's used in conjunction with the mutex to block a thread until a certain condition is met.
    // In this context, the condition represents the availability of tasks in the tasks queue. 
    std::condition_variable cv;
    // This is an atomic boolean variable. 
    // In this case, the should_exit flag is used to signal to the threads that they should exit their processing loop and terminate gracefully. When should_exit is set to true, threads should stop waiting for tasks and exit.
    std::atomic<bool> should_exit;

public:
    DispatchQueue() : should_exit(false) {}

    void add(std::function<void()> task) {
        // Lock mutex and  mutex is properly released when lock goes out of scope, even if an exception is thrown.
        std::unique_lock<std::mutex> lock(mutex);
        // adds the task to the end of the tasks queue
        // tasks queue is protected by mutex -> only one thread can modify the queue at a time.
        tasks.push(task);
        // Notifies one waiting thread (if any) that a task has been added to the queue. 
        cv.notify_one();
    }

    std::function<void()> take() {
        std::unique_lock<std::mutex> lock(mutex);
        // Ensures that the thread waits for tasks to become available in the queue or for the should_exit flag to be set before proceeding.
        cv.wait(lock, [this] { return !tasks.empty() || should_exit.load(); });
        if (tasks.empty() && should_exit.load()) {
            return nullptr; // Return nullptr to signal should_exit
        }
        auto task = tasks.front();
        tasks.pop();
        return task;
    }

    void exit() {
        should_exit.store(true);
        cv.notify_all(); // Wake up waiting threads to check should_exit
    }
};

class ActiveObject {
private:
    int count;
    DispatchQueue dispatch_queue;
    std::thread worker_thread;

public:
    ActiveObject() : count(0) {
        worker_thread = std::thread(&ActiveObject::run_tasks, this);
    }

    ~ActiveObject() {
        dispatch_queue.exit(); // Signal the dispatch queue to exit
        worker_thread.join(); // Wait for the detached thread to finish
    }

    void run_tasks() {
        while (true) {
            auto task = dispatch_queue.take();
            if (!task) {
                break; // Exit the loop if should_exit is true
            }
            task();
        }
    }

    void increment_count() {
        dispatch_queue.add([this]() {
            count++;
            std::cout << "Incremented count. New value: " << count << std::endl;
        });
    }

    void decrement_count() {
        dispatch_queue.add([this]() {
            count--;
            std::cout << "Decremented count. New value: " << count << std::endl;
        });
    }
};

int main() {
    ActiveObject obj;
    obj.increment_count();
    obj.decrement_count();

    // Wait for the worker thread to finish before exiting
    // If the thread does not finish, it means there's an issue
    obj.increment_count();
    obj.decrement_count();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
}
