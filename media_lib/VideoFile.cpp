#include "VideoFile.hpp"

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
