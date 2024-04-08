#include "ActiveObject.hpp"

ActiveObject::ActiveObject() : count(0), paused(false)
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

void ActiveObject::pauseOrResume()
{
    if (paused == true)
    {
        Mix_ResumeMusic();
    }
    else
    {
        Mix_PauseMusic();
    }
    paused = !paused;
}

bool ActiveObject::isPaused()
{
    return paused;
}

void ActiveObject::terminateMusic()
{
    Mix_HaltMusic(); // Stop music playback
}
