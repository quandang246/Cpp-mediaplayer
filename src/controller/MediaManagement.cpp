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
        std::cout << "6 - View File's metadate" << std::endl;
        std::cout << "7 - Update File's metadata" << std::endl;
        std::cout << "8 - Play music from a file path" << std::endl;

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
        case 6:
            view_file_MD();
            break;
        case 7:
            update_file_MD();
            break;
        case 8:
            playMusic();
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
            File *file_ptr = folderList.get_file(i);
            if (file_ptr->get_isAV())
            {
                file_ptr->update();
                std::cout << "Index: " << i << std::endl;
                std::cout << "File_path: " << file_ptr->get_filePath() << std::endl;
                std::cout << "Audio "
                          << " - "
                          << "Track_name: " << file_ptr->getName() << " - "
                          << "Album: " << file_ptr->getAlbum() << " - "
                          << "Artist: " << file_ptr->getArtist() << " - "
                          << "Genre: " << file_ptr->getGenre() << " - "
                          << "Publish_Year: " << file_ptr->getPublish_Year() << " - "
                          << "Duration: " << file_ptr->getDuration()
                          << std::endl;
            }
            else if (!file_ptr->get_isAV())
            {
                file_ptr->update();
                std::cout << "Index: " << i << std::endl;
                std::cout << "File_path: " << file_ptr->get_filePath() << std::endl;
                std::cout << "Video "
                          << " - "
                          << "Name: " << file_ptr->getName() << " - "
                          << "Codec: " << file_ptr->getCodec() << " - "
                          << "Size: " << file_ptr->getSize() << " - "
                          << "Bitrate: " << file_ptr->getBitrate() << " - "
                          << "Duration: " << file_ptr->getDuration() << std::endl;
            }
        }
        std::cout << "Total: " << folderList.get_file_count() << std::endl;
    }
}

void MediaManagement::view_file_MD()
{
    std::string pathString;
    std::cout << "Please enter a path: ";
    std::getline(std::cin, pathString);

    fs::path path(pathString);

    File *file_ptr = nullptr;
    if (File::isAudioFile(path))
    {
        file_ptr = new AudioFile(path);
        file_ptr->update();
        std::cout << "File_path: " << file_ptr->get_filePath() << std::endl;
        std::cout << "Audio "
                  << " - "
                  << "Track_name: " << file_ptr->getName() << " - "
                  << "Album: " << file_ptr->getAlbum() << " - "
                  << "Artist: " << file_ptr->getArtist() << " - "
                  << "Genre: " << file_ptr->getGenre() << " - "
                  << "Publish_Year: " << file_ptr->getPublish_Year() << " - "
                  << "Duration: " << file_ptr->getDuration()
                  << std::endl;
    }
    else if (File::isVideoFile(path))
    {
        file_ptr = new VideoFile(path);
        file_ptr->update();
        std::cout << "File_path: " << file_ptr->get_filePath() << std::endl;
        std::cout << "Video "
                  << " - "
                  << "Name: " << file_ptr->getName() << " - "
                  << "Codec: " << file_ptr->getCodec() << " - "
                  << "Size: " << file_ptr->getSize() << " - "
                  << "Bitrate: " << file_ptr->getBitrate() << " - "
                  << "Duration: " << file_ptr->getDuration() << std::endl;
    }
    else
    {
        std::cout << "Your file neither Video file nor Audio file! " << std::endl;
    }
}

void MediaManagement::update_file_MD()
{
    std::string pathString;
    std::cout << "Please enter a path: ";
    std::getline(std::cin, pathString);

    fs::path path(pathString);

    const char *filePathStr = path.c_str();
    TagLib::FileRef f(filePathStr);
    TagLib::Tag *t = f.tag();

    if (File::isAudioFile(path))
    {
        std::string new_Track_nameStr, new_AlbumStr, new_ArtistStr, new_GenreStr;

        // new_Track_name
        std::cout << "Enter new name: ";
        std::getline(std::cin, new_Track_nameStr);
        TagLib::String new_Name = TagLib::String(new_Track_nameStr.c_str());
        t->setTitle(new_Name);

        // new_Album
        std::cout << "Enter album name: ";
        std::getline(std::cin, new_AlbumStr);
        TagLib::String new_Album = TagLib::String(new_AlbumStr.c_str());
        t->setAlbum(new_Album);

        // new_Artist
        std::cout << "Enter Artist name: ";
        std::getline(std::cin, new_ArtistStr);
        TagLib::String new_Artist = TagLib::String(new_ArtistStr.c_str());
        t->setArtist(new_Artist);

        // new_Genre
        std::cout << "Enter Genre: ";
        std::getline(std::cin, new_GenreStr);
        TagLib::String new_Genre = TagLib::String(new_GenreStr.c_str());
        t->setGenre(new_Genre);

        // new_Publish_Year
        int new_Publish_Year;
        std::cout << "Enter Publish Year: ";
        std::cin >> new_Publish_Year;
        t->setYear(new_Publish_Year);

        f.save();
    }
    else if (File::isVideoFile(path))
    {
        std::string newNameString;
        std::cout << "Enter new name: ";
        std::getline(std::cin, newNameString);

        TagLib::String new_Name = TagLib::String(newNameString.c_str());

        t->setTitle(new_Name);

        f.save();
    }
    else
    {
        std::cout << "Your file neither Video file nor Audio file! " << std::endl;
    }
}

void MediaManagement::playMusic()
{
    std::string someFile;
    std::cout << "Please enter a file path: ";
    std::getline(std::cin, someFile);

    ActiveObject obj;
    // Add tasks to play music
    obj.runFunction([this, someFile](){ MP.playMusic(someFile, 5); });
    
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
