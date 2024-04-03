#include "ActiveObject.hpp"

ActiveObject::ActiveObject() : count(0)
{
    worker_thread = std::thread(&ActiveObject::run_tasks, this);
}

ActiveObject::~ActiveObject()
{
    dispatch_queue.exit(); // Signal the dispatch queue to exit
    worker_thread.join();  // Wait for the detached thread to finish
}

void ActiveObject::run_tasks()
{
    while (true)
    {
        auto task = dispatch_queue.take();
        if (!task)
        {
            break; // Exit the loop if should_exit is true
        }
        task();
    }
}

void ActiveObject::runFunction(std::function<void()> func)
{
    dispatch_queue.add(func);
}
