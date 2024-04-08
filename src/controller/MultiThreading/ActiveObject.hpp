#ifndef ACTIVEOBJECT_HPP
#define ACTIVEOBJECT_HPP

#include "DispatchQueue.hpp"

class ActiveObject
{
private:
    int count;
    DispatchQueue dispatch_queue;
    std::thread worker_thread;
    bool paused;

public:
    ActiveObject();
    ~ActiveObject();

    void run_tasks();
    void runFunction(std::function<void()> func);

    bool isPaused();

    void pauseOrResume();
    void terminateMusic();
};

#endif
