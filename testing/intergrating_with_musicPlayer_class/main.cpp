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

class musicPlayer
{
private:
    ActiveObject obj;
    bool running;
    std::thread time_thread;
    int Time;
    int pause_sum;
    int duration;
    int end_time;

public:
    musicPlayer() : Time(0), running(false), end_time(0), pause_sum(0)
    {
        time_thread = std::thread(&musicPlayer::time_process, this);
        time_thread.detach();
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
            // std::cout << "Playing music..." << std::endl;
        }

        // Wait for specified duration
        for (int i = 0; i < durationInSeconds; i++)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        // Free resources and quit SDL
        Mix_FreeMusic(music);
        Mix_CloseAudio();
        SDL_Quit();
    }

    void time_process()
    {
        while (true)
        {
            if (running)
            {
                // Sleep 1 sec to get the right time
                std::this_thread::sleep_for(std::chrono::seconds(1));
                Time++;
                // std::cout << Time << " - " << end_time << std::endl;
                if (Time == end_time)
                {
                    obj.terminateMusic();
                    running = false;
                    Time = 0;
                    pause_sum = 0;
                }
            }
        }
    }

    void play()
    {
        if (running == false)
        {
            std::string filePath;
            std::cout << "Please enter a file path: ";
            std::getline(std::cin, filePath);
            int temp;
            std::cout << "Please enter duration: ";
            std::cin >> duration;
            end_time = duration;

            // Add tasks to play music
            obj.runFunction([this, filePath]()
                            { playMusic(filePath, end_time); });

            running = true;
        }
        // Clearing the input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    void play_action()
    {
        if (running == true)
        {

            std::cout << "Enter controlling play mode!" << std::endl;

            int paused_time;

            while (running)
            {
                std::cout << "Enter 0 to exit. " << std::endl;
                std::cout << "Enter 1 to pause/resume music. " << std::endl;
                std::cout << "Enter 2 to view Time/Duration." << std::endl;
                std::cout << "Enter 3 to terminate." << std::endl;

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
                        end_time += 100000;
                    }
                    else
                    {
                        end_time = end_time + Time - paused_time - 100000;
                        pause_sum = pause_sum + Time - paused_time;
                    }
                    break;
                case 2:
                    std::cout << "Time/Duration: " << (obj.isPaused() ? paused_time - pause_sum : Time - pause_sum) << "/" << duration << std::endl;
                    break;
                case 3:
                    obj.terminateMusic();
                    end_time = 0;
                    running = false;
                    Time = 0;
                    pause_sum = 0;
                    return;
                default:
                    std::cout << "Invalid choice!" << std::endl;
                    break;
                }
            }
        }
        else
        {
            std::cout << "Nothing is playing!" << std::endl;
        }
    }
};

int main()
{
    musicPlayer A;

    A.play();

    A.play_action();

    return 0;
}
