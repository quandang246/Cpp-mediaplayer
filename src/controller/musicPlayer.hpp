#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include "../module/File.hpp"
#include "MultiThreading/ActiveObject.hpp"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

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
    musicPlayer();
    ~musicPlayer();

    bool getRunning();

    bool isValidExtension(const std::string &filename);
    void playMusic(const std::string &filePath, int &durationInSeconds);

    void time_process();
    void play(std::string FP, int d);
    void play_action();
    
    void terminate();
};

#endif
