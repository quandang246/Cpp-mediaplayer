#include "musicPlayer.hpp"

musicPlayer::musicPlayer(/* args */)
{
}

musicPlayer::~musicPlayer()
{
}

bool musicPlayer::isValidExtension(const std::string& filename) {
    std::string extension = filename.substr(filename.find_last_of(".") + 1);
    return extension == "mp3" || extension == "wav" || extension == "ogg" || extension == "flac";
}

void musicPlayer::playMusic(const std::string& filePath, int durationInSeconds) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    if (!musicPlayer::isValidExtension(filePath)) {
        std::cerr << "Unsupported file format!" << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return;
    }

    // Load audio file
    Mix_Music *music = Mix_LoadMUS(filePath.c_str());
    if (!music) {
        std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return;
    }

    // Play the music
    if (Mix_PlayMusic(music, -1) == -1) {
        std::cerr << "Failed to play music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    } else {
        std::cout << "Playing music: " << filePath << std::endl;
    }

    // Wait for specified duration
    SDL_Delay(durationInSeconds * 1000);

    // Free resources and quit SDL
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();
}
