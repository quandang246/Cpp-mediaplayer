#ifndef DISPATCHQUEUE_HPP
#define DISPATCHQUEUE_HPP

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <atomic>

class DispatchQueue
{
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
    DispatchQueue();
    ~DispatchQueue();

    void add(std::function<void()> task);
    std::function<void()> take();
    void exit();
};

#endif
