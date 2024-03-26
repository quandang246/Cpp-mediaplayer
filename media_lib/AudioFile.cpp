#include "AudioFile.hpp"

AudioFile::AudioFile()
{
}

AudioFile::~AudioFile()
{
}

AudioFile::AudioFile(fs::path path, int m) {
    filePath = path;
    metadata = m;
    isAV = false;
}

void AudioFile::play() {
    std::cout << "Video file: " << File::filePath << " playing!" << std::endl;
}

void AudioFile::pause() {
    std::cout << "Video file: " << File::filePath << " paused!" << std::endl;
}

void AudioFile::displayTimeDuration() {
    std::cout << "Displaying Time and duration!" << std::endl;
}
