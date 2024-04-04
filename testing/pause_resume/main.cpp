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
    DispatchQueue() : should_exit(false) {}

    void add(std::function<void()> task)
    {
        // Lock mutex and  mutex is properly released when lock goes out of scope, even if an exception is thrown.
        std::unique_lock<std::mutex> lock(mutex);
        // adds the task to the end of the tasks queue
        // tasks queue is protected by mutex -> only one thread can modify the queue at a time.
        tasks.push(task);
        // Notifies one waiting thread (if any) that a task has been added to the queue.
        cv.notify_one();
    }

    std::function<void()> take()
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

    void exit()
    {
        should_exit.store(true);
        cv.notify_all(); // Wake up waiting threads to check should_exit
    }
};

class ActiveObject
{
private:
    int count;
    DispatchQueue dispatch_queue;
    std::thread worker_thread;
    bool paused;

public:
    ActiveObject() : count(0), paused(false)
    {
        worker_thread = std::thread(&ActiveObject::run_tasks, this);
    }

    ~ActiveObject()
    {
        dispatch_queue.exit(); // Signal the dispatch queue to exit
        worker_thread.join();  // Wait for the detached thread to finish
    }

    void run_tasks()
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

    void runFunction(std::function<void()> func)
    {
        dispatch_queue.add(func);
    }

    void pauseOrResume()
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

    bool isPaused()
    {
        return paused;
    }

    void terminateMusic()
    {
        Mix_HaltMusic(); // Stop music playback
    }
};

bool isValidExtension(const std::string &filename)
{
    std::string extension = filename.substr(filename.find_last_of(".") + 1);
    return extension == "mp3" || extension == "wav" || extension == "ogg" || extension == "flac";
}

void playMusic(const std::string &filePath, int durationInSeconds, ActiveObject &obj)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    if (!isValidExtension(filePath))
    {
        std::cerr << "Unsupported file format!" << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return;
    }

    // Load audio file
    Mix_Music *music = Mix_LoadMUS(filePath.c_str());
    if (!music)
    {
        std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return;
    }

    // Play the music
    if (Mix_PlayMusic(music, -1) == -1)
    {
        std::cerr << "Failed to play music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    }
    else
    {
        std::cout << "Playing music..." << std::endl;
    }

    // Wait for specified duration
    SDL_Delay(durationInSeconds * 1000);

    // Free resources and quit SDL
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();
}

int main()
{
    ActiveObject obj;
    bool running = true;

    int duration = 10;

    // Add tasks to play music
    obj.runFunction([&obj, duration]()
                    { playMusic("/home/quan246/projects/src/mock_prj/file_sample/10 second intro music.mp3", duration * 10, obj); });

    int Time = 0;
    std::thread time_thread([&Time, &duration]()
                            {
        for (int i = 0; i < duration*10; i++) 
        {
            // Sleep 1 sec to get the right time
            std::this_thread::sleep_for(std::chrono::seconds(1));
            Time++;
            std::cout << Time << std::endl;
        } });

    int end_time = duration;
    int paused_time;

    std::thread end_thread([&Time, &end_time, &obj]()
                           {
                                while(true)
                                {
                                    if (Time == end_time)
                                    {
                                        obj.terminateMusic();
                                    }
                                } });

    while (running)
    {
        std::cout << "Enter 1 to pause/resume music or 0 to exit: ";
        int choice;
        std::cin >> choice;
        switch (choice)
        {
        case 0:
            running = false;
            break;
        case 1:
            obj.pauseOrResume();
            std::cout << "Music " << (obj.isPaused() ? "paused" : "resumed") << std::endl;
            if (obj.isPaused())
            {
                paused_time = Time;
            }
            else
            {
                end_time += Time - paused_time;
            }
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
            break;
        }
    }

    return 0;
}
