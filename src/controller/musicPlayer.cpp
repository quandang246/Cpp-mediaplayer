#include "musicPlayer.hpp"

musicPlayer::musicPlayer() : Time(0), running(false), end_time(0), pause_sum(0)
{
    time_thread = std::thread(&musicPlayer::time_process, this);
    time_thread.detach();
}
musicPlayer::~musicPlayer()
{
}

bool musicPlayer::isValidExtension(const std::string &filename)
{
    std::string extension = filename.substr(filename.find_last_of(".") + 1);
    return extension == "mp3" || extension == "wav" || extension == "ogg" || extension == "flac";
}

void musicPlayer::playMusic(const std::string &filePath, int &durationInSeconds)
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
        running = true;
        // std::cout << "Playing music..." << std::endl;
    }

    // Wait for specified duration
    for (int i = 0; i < durationInSeconds; i++)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Reset timer
    obj.terminateMusic();
    running = false;

    // Free resources and quit SDL
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();
}

void musicPlayer::time_process()
{
    while (true)
    {
        if (running)
        {
            // Sleep 1 sec to get the right time
            std::this_thread::sleep_for(std::chrono::seconds(1));
            Time++;
            // std::cout << "Time: " << Time << " - " << end_time << std::endl;
        }
        else
        {
            Time = 0;
            pause_sum = 0;
        }
    }
}

void musicPlayer::play(std::string FP, int d)
{
    std::string filePath = FP;
    duration = d;
    end_time = duration;

    // Add tasks to play music
    obj.runFunction([this, filePath]()
                    { playMusic(filePath, end_time); });

    return;
}

void musicPlayer::play_action()
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
                running = false;
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

bool musicPlayer::getRunning()
{
    return running;
}

void musicPlayer::terminate()
{
    obj.terminateMusic();
    running = false;
}

