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

PlayList::PlayList()
{
    std::cout << "Please enter playlist name: ";
    std::getline(std::cin, PL_name);
    current_index = 0;
}

PlayList::~PlayList()
{
}

void PlayList::addFile()
{
    std::string pathStr;
    std::cout << "Please enter file path: ";
    std::getline(std::cin, pathStr); // Read entire line as string
    // Example input: ...\mock_prj\testing
    fs::path path(pathStr); // Convert string to fs::path

    if (fs::is_regular_file(path))
    {
        File *new_file = nullptr;
        if (File::isAudioFile(path))
        {
            new_file = new VideoFile(path, 30);
            Files.push_back(new_file);
            
        }
        else if (File::isVideoFile(path))
        {
            new_file = new AudioFile(path, 30);
            Files.push_back(new_file);
        }
        else
        {
            std::cout << "The file is not an audio file or video file!" << std::endl;
        }
    }
}

void PlayList::removeFile()
{
    int index;
    std::cout << "Enter index of file that want to delete: ";
    std::cin >> index;
    if (index > Files.size() || index < 0)
    {
        std::cout << "Invalid index, please try again!" << std::endl;
    }
    else
    {
        Files.erase(Files.begin() + index);
    }
}

void PlayList::display()
{
    if (Files.size() == 0)
    {
        std::cout << "Playlist doesn't have any files." << std::endl;
    }
    else
    {
        for (int i = 0; i < Files.size(); i++)
        {
            std::cout << "Index: " << i << std::endl;
            std::cout << "File: " << Files[i]->get_filePath() << std::endl;
        }
        std::cout << "Total: " << Files.size() << std::endl;
    }
}

void PlayList::playPL()
{
    int PLsize = Files.size();
    for (int i = current_index; i < PLsize; i++)
    {
        Files[current_index]->play();
    }
}

void PlayList::pausePL()
{
    Files[current_index]->pause();
}

void PlayList::next()
{
    Files[current_index]->pause();
    current_index++;
    Files[current_index]->play();
}

void PlayList::previous()
{
    Files[current_index]->pause();
    current_index--;
    Files[current_index]->play();
}

void PlayList::displayTimeDuration()
{
    std::cout << "Time: " << std::endl;
    std::cout << "Duration: " << std::endl;
}

std::string PlayList::get_PL_name()
{
    return PL_name;
}

#endif
