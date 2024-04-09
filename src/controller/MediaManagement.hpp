#ifndef MEDIAMANAGEMENT_HPP
#define MEDIAMANAGEMENT_HPP

#include <string>
#include <iostream>
#include <limits.h>
#include <unistd.h>
#include <cstring> // Include for strrchr
#include <filesystem> // Include for std::filesystem::path
#include "../module/PlayList.hpp"
#include "../module/FolderList.hpp"
#include "musicPlayer.hpp"

namespace fs = std::filesystem;

class MediaManagement
{
private:
    musicPlayer MP;
    FolderList folderList;
    std::vector<PlayList> PlayLists;
    std::thread queue_play;
    std::queue<File*> song_queue;
    
public:
    MediaManagement();
    ~MediaManagement();

    MediaManagement(std::string path);
    
    // Run program function
    void run();

    // Playlist function
    // Create new playlist
    void createPL();
    // Delete a playlist
    void deletePL();
    // view all playlist
    void view_all_PL();
    // Update playlist
    void update_PL();
    // Play playlist
    void play_PL(int index);


    //Folder function
    // view all folderlist
    void view_all_FL();

    
    // File function
    void view_file_MD();
    void update_file_MD();
    void control();
    void playingMusic();
    
    // queue function
    void playing_queue();
};

#endif
