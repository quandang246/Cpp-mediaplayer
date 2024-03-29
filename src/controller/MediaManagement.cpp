#include "MediaManagement.hpp"

MediaManagement::MediaManagement(std::string path)
{
    std::filesystem::path programPath(path);

    folderList = FolderList(programPath);
    std::cout << "Current working directory : " << programPath << std::endl;
}

MediaManagement::MediaManagement()
{
}

MediaManagement::~MediaManagement()
{
}

void MediaManagement::run()
{
    while (true)
    {
        std::cout << "0 - Exit." << std::endl;
        std::cout << "1 - View Media files in that folder and all sub-folder (audio and video)" << std::endl;
        std::cout << "2 - Create new playlist" << std::endl;
        std::cout << "3 - Delete a playlist" << std::endl;
        std::cout << "4 - view all playlist" << std::endl;
        std::cout << "5 - Update playlist" << std::endl;

        int choice;
        std::cout << "Please enter your's choice: ";
        std::cin >> choice;

        // Clearing the input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice)
        {
        case 0:
            return;
        case 1:
            view_all_FL();
            break;
        case 2:
            createPL();
            break;
        case 3:
            deletePL();
            break;
        case 4:
            view_all_PL();
            break;
        case 5:
            update_PL();
            break;
        default:
            std::cout << "Invalid input, please try again!" << std::endl;
            break;
        }
    }
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
        PlayList *edit_PL = &PlayLists[PL_id];

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
    }
    else
    {
        std::cout << "Invalid playlist index!" << std::endl;
    }
}

void MediaManagement::view_all_FL()
{
    if (folderList.get_file_count() <= 0)
    {
        std::cout << "Current working folder does not have any audio/video files. Please try again!" << std::endl;
    }
    else
    {
        std::cout << "Media files in that folder and all sub-folder (audio and video): " << std::endl;
        for (int i = 0; i < folderList.get_file_count(); i++)
        {
            if (folderList.get_file(i)->get_isAV())
            {
                std::cout   << "Index: " << i << std::endl;
                std::cout   << "Audio " << " - "  
                            << "Track_name: " << folderList.get_file(i)->getName() << " - " 
                            << "Album: " << folderList.get_file(i)->getAlbum() << " - " 
                            << "Artist: " << folderList.get_file(i)->getArtist() << " - " 
                            << "Genre: " << folderList.get_file(i)->getGenre() << " - " 
                            << "Publish_Year: " << folderList.get_file(i)->getPublish_Year() << " - " 
                            << "Duration: " << folderList.get_file(i)->getDuration() << " - " 
                            << std::endl;
                            
                std::cout << "File_path: " << folderList.get_file(i)->get_filePath() << std::endl;
            }
            else if (!folderList.get_file(i)->get_isAV())
            {
                std::cout   << "Index: " << i << std::endl;
                std::cout   << "Video " << " - "  
                            << "Name: " << folderList.get_file(i)->getName() << " - " 
                            << "Codec: " << folderList.get_file(i)->getCodec() << " - " 
                            << "Size: " << folderList.get_file(i)->getSize() << " - " 
                            << "Bitrate: " << folderList.get_file(i)->getBitrate() << " - " 
                            << "Duration: " << folderList.get_file(i)->getDuration() << " - " 
                            << std::endl;
                            
                std::cout << "File_path: " << folderList.get_file(i)->get_filePath() << std::endl;
            }
        }
        std::cout << "Total: " << folderList.get_file_count() << std::endl;
    }
}

/*
std::filesystem::path MediaManagement::getexepath() {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count != -1) {
        result[count] = '\0'; // Null-terminate the string
        // Find the last occurrence of '/' in the path
        char *lastSlash = strrchr(result, '/');
        if (lastSlash != nullptr) {
            *(lastSlash + 1) = '\0'; // Null-terminate at the position of the last '/'
            return std::filesystem::path(result);
        }
    }
    return ""; // Return an empty path if there's an error or no '/'
}
*/
