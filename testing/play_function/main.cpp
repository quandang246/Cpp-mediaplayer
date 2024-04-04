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
        std::cout << "worker_thread" << std::endl;
        dispatch_queue.exit(); // Signal the dispatch queue to exit
        if (worker_thread.joinable())
        {
            worker_thread.join(); // Wait for the detached thread to finish
        }
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

class musicPlayer
{
private:
    ActiveObject obj;
    int duration;
    int Time;
    int end_time;
    int paused_time;

public:
    musicPlayer();
    musicPlayer(int d)
    {
        duration = d;
        Time = 0;
        end_time = duration;
        paused_time = 0;
    }
    ~musicPlayer()
    {
    }

    bool isValidExtension(const std::string &filename)
    {
        std::string extension = filename.substr(filename.find_last_of(".") + 1);
        return extension == "mp3" || extension == "wav" || extension == "ogg" || extension == "flac";
    }

    void playMusic(const std::string &filePath, int &durationInSeconds)
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

        for (int i = 0; i < durationInSeconds; i++)
        {
            // Wait for specified duration
            SDL_Delay(1000);
        }            
        
        // Free resources and quit SDL
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
    }

    void play()
    {
        std::string filePath;
        std::cout << "Please enter file path: ";
        std::getline(std::cin, filePath);
        
        // Add tasks to play music
        obj.runFunction([this, filePath]()
                        { this->playMusic(filePath, end_time); });

        std::thread time_thread([this]()
                                {
        for (int i = 0; i < end_time; i++) 
        {
            // Sleep 1 sec to get the right time
            std::this_thread::sleep_for(std::chrono::seconds(1));
            Time++;
            std::cout << Time << std::endl;

            if (Time == end_time)
            {
                obj.terminateMusic();
            }
        } });

        bool playing = true;
        while (playing)
        {
            std::cout << "Enter 1 to pause/resume music or 0 to exit: ";
            int choice;
            std::cin >> choice;
            switch (choice)
            {
            case 0:
                std::cout << "time_thread" << std::endl;
                time_thread.detach();
                return;
            case 1:
                obj.pauseOrResume();
                std::cout << "Music " << (obj.isPaused() ? "paused" : "resumed") << std::endl;
                if (obj.isPaused())
                {
                    paused_time = Time;
                    // Adding to make thread alive until end_time is updated
                    end_time += 1000000;
                }
                else
                {
                    end_time += Time - paused_time - 1000000;
                }
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
                break;
            }
        }
    }
};

int main()
{
    musicPlayer MP(10);

    MP.play();

    MP.play();

    return 0;
}
