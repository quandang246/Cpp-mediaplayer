#ifndef MEDIAMANAGEMENT_HPP
#define MEDIAMANAGEMENT_HPP

#include <filesystem>
#include <iostream>
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

MediaManagement::MediaManagement()
{
    std::string dirStr;
    std::cout << "Please enter directory: ";
    std::getline(std::cin, dirStr); // Read entire line as string
    // Example input: ...\mock_prj\testing
    fs::path dir(dirStr); // Convert string to fs::path
    folderList = FolderList(dir);
}

MediaManagement::~MediaManagement()
{
}

void MediaManagement::view_folder_list()
{
    folderList.display();
}

void MediaManagement::createPL()
{
    PlayList new_PL;
    PlayLists.push_back(new_PL);
}

void MediaManagement::deletePL()
{
    int index;
    std::cout << "Please enter index: ";
    std::cin >> index;
    if (index > PlayLists.size() || index < 0)
    {
        std::cout << "Invalid index, please try again!" << std::endl;
    }
    else
    {
        PlayLists.erase(PlayLists.begin() + index);
    }
}

void MediaManagement::view_all_PL()
{
    if (PlayLists.size() == 0)
    {
        std::cout << "You don't have any playlist!" << std::endl;
    }
    else
    {
        std::cout << "All playlist: " << std::endl;
        for (int i = 0; i < PlayLists.size(); i++)
        {
            std::cout << "Index: " << i << std::endl;
            std::cout << "Playlist's name: " << PlayLists[i].get_PL_name() << std::endl;
        }
        std::cout << "Total: " << PlayLists.size() << " playlists." << std::endl;
    }
}

void MediaManagement::update_PL()
{
    int PL_id;
    std::cout << "Please enter playlist_id: ";
    std::cin >> PL_id;
    if (PL_id >= 0 && PL_id < PlayLists.size())
    {
        PlayList* edit_PL = &PlayLists[PL_id];

        std::cout << "Editing " << PL_id << " - " << edit_PL->get_PL_name() << std::endl;

        while (true)
        {
            std::cout << "0 - Exit." << std::endl;
            std::cout << "1 - View Media files in playlist." << std::endl;
            std::cout << "2 - Add new file." << std::endl;
            std::cout << "3 - Remove file." << std::endl;

            int choice;
            std::cout << "Please enter your's choice: ";
            std::cin >> choice;

            // Clearing the input buffer
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (choice)
            {
            case 0:
                std::cout << "Exiting update playlist mode." << std::endl;
                return;
            case 1:
                edit_PL->display();
                break;
            case 2:
                edit_PL->addFile();
                break;
            case 3:
                edit_PL->removeFile();
                break;
            default:
                std::cout << "Invalid input, please try again!" << std::endl;
                break;
            }
        }
    } else {
        std::cout << "Invalid playlist index!" << std::endl;
    }
}

#endif
