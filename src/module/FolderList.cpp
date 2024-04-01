#include "FolderList.hpp"

FolderList::FolderList()
{
}

FolderList::~FolderList()
{
}

FolderList::FolderList(const fs::path &directory)
{
    file_count = 0;
    for (const auto &entry : fs::recursive_directory_iterator(directory))
    {
        if (fs::is_regular_file(entry.path()))
        {
            File *new_file = nullptr;
            if (File::isAudioFile(entry.path()))
            {
                new_file = new AudioFile(entry.path());
                Files.push_back(new_file);
                file_count++;
            }
            else if (File::isVideoFile(entry.path()))
            {
                new_file = new VideoFile(entry.path());
                Files.push_back(new_file);
                file_count++;
            }
        }
    }
}

int FolderList::get_file_count(){
    return  file_count;
}

File* FolderList::get_file(int i)
{
    return Files[i];
}
