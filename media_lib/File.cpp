#include "File.hpp"

File::File()
{
}

File::~File()
{
}

File::File(fs::path path)
{
    filePath = path;
    if (isAudioFile(filePath))
    {
        isAV = true;
    }
    else if (isVideoFile(filePath))
    {
        isAV = false;
    }
}

bool File::isAudioFile(const fs::path &filePath)
{
    std::string extension = filePath.extension().string();
    return extension == ".mp3" || extension == ".wav" || extension == ".ogg" || extension == ".flac";
}

bool File::isVideoFile(const fs::path &filePath)
{
    std::string extension = filePath.extension().string();
    return extension == ".mp4" || extension == ".avi" || extension == ".mkv" || extension == ".mov";
}

void File::play()
{
    std::cout << "File is playing!" << std::endl;
}

void File::pause()
{
    std::cout << "File paused!" << std::endl;
}

void File::displayTimeDuration()
{
    std::cout << "File TimeDuration!" << std::endl;
}

fs::path File::get_filePath()
{
    return filePath;
}
