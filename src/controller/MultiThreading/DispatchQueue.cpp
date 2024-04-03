#include "DispatchQueue.hpp"

DispatchQueue::DispatchQueue() : should_exit(false) {}
DispatchQueue::~DispatchQueue(){}

void DispatchQueue::add(std::function<void()> task)
{
    // Lock mutex and  mutex is properly released when lock goes out of scope, even if an exception is thrown.
    std::unique_lock<std::mutex> lock(mutex);
    // adds the task to the end of the tasks queue
    // tasks queue is protected by mutex -> only one thread can modify the queue at a time.
    tasks.push(task);
    // Notifies one waiting thread (if any) that a task has been added to the queue.
    cv.notify_one();
}

std::function<void()> DispatchQueue::take()
{
    std::unique_lock<std::mutex> lock(mutex);
    // Ensures that the thread waits for tasks to become available in the queue or for the should_exit flag to be set before proceeding.
    cv.wait(lock, [this]
            { return !tasks.empty() || should_exit.load(); });
    if (tasks.empty() && should_exit.load())
    {
        return nullptr; // Return nullptr to signal should_exit
    }
    auto task = tasks.front();
    tasks.pop();
    return task;
}

void DispatchQueue::exit()
{
    should_exit.store(true);
    cv.notify_all(); // Wake up waiting threads to check should_exit
}
