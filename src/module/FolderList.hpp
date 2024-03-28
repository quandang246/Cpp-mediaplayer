#ifndef FOLDERLIST_HPP
#define FOLDERLIST_HPP

#include <vector>
#include <filesystem>
#include <iostream>
#include "File.hpp"
#include "AudioFile.hpp"
#include "VideoFile.hpp"

namespace fs = std::filesystem;

class FolderList
{
private:
    std::vector<File *> Files;
    int file_count;

public:
    // Default destructor
    FolderList();
    ~FolderList();

    // Parameter constructor
    FolderList(const fs::path &directory);

    // get file_count
    int get_file_count();
    
    // get file
    File* get_file (int i);
};

#endif
