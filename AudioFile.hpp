#ifndef AUDIOFILE_HPP
#define AUDIOFILE_HPP

#include "File.hpp"

class AudioFile : public File
{
private:
    int metadata;
public:
    // Default constructor and destructor
    AudioFile();
    ~AudioFile();

    // Parameter constructor
    AudioFile(fs::path path, int m);

    // play function
    void play ();

    // pause function
    void pause ();

    // displayTimeDuration function
    void displayTimeDuration();
};

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

#endif

