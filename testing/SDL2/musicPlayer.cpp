#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

bool isValidExtension(const std::string& filename) {
    std::string extension = filename.substr(filename.find_last_of(".") + 1);
    return extension == "mp3" || extension == "wav" || extension == "ogg" || extension == "flac";
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <audio_file> <duration_in_seconds>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    if (!isValidExtension(filename)) {
        std::cerr << "Unsupported file format!" << std::endl;
        return 1;
    }

    int duration = std::stoi(argv[2]);
    if (duration <= 0) {
        std::cerr << "Invalid duration!" << std::endl;
        return 1;
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return 1;
    }

    // Load audio file
    Mix_Music *music = Mix_LoadMUS(filename.c_str());
    if (!music) {
        std::cerr << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return 1;
    }

    // Play the music
    if (Mix_PlayMusic(music, -1) == -1) {
        std::cerr << "Failed to play music! SDL_mixer Error: " << Mix_GetError() << std::endl;
    } else {
        std::cout << "Playing music..." << std::endl;
    }

    // Wait for specified duration
    SDL_Delay(duration * 1000);

    // Free resources and quit SDL
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
