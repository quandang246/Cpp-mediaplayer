#ifndef FOLDERLIST_HPP
#define FOLDERLIST_HPP

#include <vector>
#include <filesystem>
#include <iostream>
#include "File.hpp"

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

    // display
    void display();

};

FolderList::FolderList()
{

}

FolderList::~FolderList()
{
}

FolderList::FolderList(const fs::path &directory)
{
    file_count = 0;
    std::cout << "Audio/Video file in folder/subfolder: " << std::endl;
    for (const auto &entry : fs::recursive_directory_iterator(directory))
    {
        if (fs::is_regular_file(entry.path()))
        {
            File *new_file = nullptr;
            if (File::isAudioFile(entry.path()))
            {
                new_file = new VideoFile(entry.path(), 30);
                Files.push_back(new_file);
                file_count++;
            }
            else if (File::isVideoFile(entry.path()))
            {
                new_file = new AudioFile(entry.path(), 30);
                Files.push_back(new_file);
                file_count++;
            }
        }
    }
}

int FolderList::get_file_count(){
    return  file_count;
}

void FolderList::display()
{
    std::cout << "Media files in that folder and all sub-folder (audio and video): " << std::endl;
    for (int i = 0; i < file_count; i++) {
        std::cout << "Index: " << i << std::endl;
        std::cout << "File: " << Files[i]->get_filePath() << std::endl;
    }
    std::cout << "Total: " << file_count << std::endl;
}

#endif
