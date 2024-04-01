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

namespace fs = std::filesystem;

class MediaManagement
{
private:
    FolderList folderList;
    std::vector<PlayList> PlayLists;

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


    //Folder function
    // view all folderlist
    void view_all_FL();

    
    // File function
    void view_file_MD();
};

#endif
