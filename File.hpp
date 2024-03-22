#ifndef FILE_HPP
#define FILE_HPP

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

class File
{
protected:
    fs::path filePath;
    bool isAV;

public:
    // Default Constructor and destructor
    File();
    virtual ~File();

    // Parameter constructor
    File(fs::path directory);

    // play function
    void play();

    // pause function
    void pause();

    // displayTimeDuration function
    void displayTimeDuration();

    static bool isAudioFile(const fs::path &filePath);
    static bool isVideoFile(const fs::path &filePath);

    // get filePath
    fs::path get_filePath();
};

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

#endif
