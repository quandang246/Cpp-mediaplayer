#ifndef VIDEOFILE_HPP
#define VIDEOFILE_HPP

#include "File.hpp"

class VideoFile : public File
{
private:
    int metadata;
public:
    // Default constructor and destructor
    VideoFile();
    ~VideoFile();

    // Parameter constructor
    VideoFile(fs::path path, int m);

    // play function
    void play ();

    // pause function
    void pause ();

    // displayTimeDuration function
    void displayTimeDuration();
};

VideoFile::VideoFile()
{
}

VideoFile::~VideoFile()
{
}

VideoFile::VideoFile(fs::path path, int m) {
    filePath = path;
    metadata = m;
    isAV = true;
}

void VideoFile::play() {
    std::cout << "Video file: " << File::filePath << " playing!" << std::endl;
}

void VideoFile::pause() {
    std::cout << "Video file: " << File::filePath << " paused!" << std::endl;
}

void VideoFile::displayTimeDuration() {
    std::cout << "Displaying Time and duration!" << std::endl;
}

#endif
