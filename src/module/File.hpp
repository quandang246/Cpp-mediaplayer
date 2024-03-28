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

    static bool isAudioFile(const fs::path &filePath);
    static bool isVideoFile(const fs::path &filePath);

    // get filePath
    fs::path get_filePath();
};

#endif
