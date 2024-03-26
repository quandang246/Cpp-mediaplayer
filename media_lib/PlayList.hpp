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

    // play function
    void playPL();

    // pause function
    void pausePL();

    // next function
    void next();

    // previous function
    void previous();

    // display time and duration function
    void displayTimeDuration();

    // get PL_name;
    std::string get_PL_name();
};

#endif
