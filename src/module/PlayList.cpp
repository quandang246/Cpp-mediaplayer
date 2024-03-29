#include "PlayList.hpp"

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
            new_file = new VideoFile(path);
            Files.push_back(new_file);
            
        }
        else if (File::isVideoFile(path))
        {
            new_file = new AudioFile(path);
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

std::string PlayList::get_PL_name()
{
    return PL_name;
}
