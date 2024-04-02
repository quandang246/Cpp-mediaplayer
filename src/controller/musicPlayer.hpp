#ifndef MUSICPLAYER_HPP
#define MUSICPLAYER_HPP

#include "../module/File.hpp"
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class musicPlayer
{
private:
    
public:
    musicPlayer(/* args */);
    ~musicPlayer();

    bool isValidExtension(const std::string& filename);

    void playMusic(const std::string& filePath, int durationInSeconds);
};

#endif
