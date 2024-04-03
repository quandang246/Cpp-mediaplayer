#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>

class MusicPlayer {
public:
    MusicPlayer() : music(nullptr) {}

    ~MusicPlayer() {
        if (music) {
            Mix_FreeMusic(music);
            music = nullptr;
        }
        Mix_CloseAudio();
        SDL_Quit();
    }

    bool initialize() {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_AUDIO) < 0) {
            std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
            return false;
        }

        // Initialize SDL_mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            std::cerr << "SDL_mixer initialization failed: " << Mix_GetError() << std::endl;
            return false;
        }

        return true;
    }

    bool play(const std::string& filePath) {
        music = Mix_LoadMUS(filePath.c_str());
        if (!music) {
            std::cerr << "Failed to load music: " << Mix_GetError() << std::endl;
            return false;
        }

        if (Mix_PlayMusic(music, -1) < 0) {
            std::cerr << "Failed to play music: " << Mix_GetError() << std::endl;
            return false;
        }

        return true;
    }

    void PauseOrResume() {
        if (Mix_PausedMusic() == 1) {
            std::cout << "Resuming music..." << std::endl;
            Mix_ResumeMusic();
        } else {
            std::cout << "Music is playing. Pausing..." << std::endl;
            Mix_PauseMusic();
        }
    }

    bool playWithDuration(const std::string& filePath, Uint32 duration) {
        if (!initialize())
            return false;

        if (!play(filePath))
            return false;

        SDL_Delay(duration);

        return true;
    }

private:
    Mix_Music* music;
};

int main() {
    MusicPlayer player;

    if (player.playWithDuration("/home/quan246/projects/src/mock_prj/file_sample/10 second intro music.mp3", 2000)) {
        player.PauseOrResume();
        player.playWithDuration("/home/quan246/projects/src/mock_prj/file_sample/10 second intro music.mp3", 5000);
        player.PauseOrResume();
        player.playWithDuration("/home/quan246/projects/src/mock_prj/file_sample/10 second intro music.mp3", 5000);
    }

    return 0;
}
