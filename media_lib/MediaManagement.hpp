#ifndef MEDIAMANAGEMENT_HPP
#define MEDIAMANAGEMENT_HPP

#include <string>
#include <iostream>
#include <limits.h>
#include <unistd.h>
#include <cstring> // Include for strrchr
#include <filesystem> // Include for std::filesystem::path
#include "PlayList.hpp"
#include "FolderList.hpp"

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
    // Folder function
    // Media files in that folder and all sub-folder (audio and video)
    void view_folder_list();

    // Playlist function
    // Create new playlist
    void createPL();
    // Delete a playlist
    void deletePL();
    // view all playlist
    void view_all_PL();
    // Update playlist
    void update_PL();

};

#endif
