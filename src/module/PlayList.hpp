#ifndef PLAYLIST_HPP
#define PLAYLIST_HPP

#include <vector>
#include <filesystem>
#include "File.hpp"
#include "AudioFile.hpp"
#include "VideoFile.hpp"

namespace fs = std::filesystem;

class PlayList
{
private:
    std::string PL_name;
    std::vector<File *> Files;
    int current_index; // index of playing file

public:
    // Default constructor and destructor
    PlayList();
    ~PlayList();

    // Playlist's file function
    // add file to playlist
    void addFile();
    // remove file from playlist
    void removeFile();
    // display list
    void display();
    
    // get PL_name;
    std::string get_PL_name();
    // get Files pointer
    File* files_ptr(int i);
    // getCount
    int getCount();
};

#endif
