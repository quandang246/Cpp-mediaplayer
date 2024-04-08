#include <iostream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

bool isAudioFile(const fs::path &filePath)
{
    std::string extension = filePath.extension().string();
    return extension == ".mp3" || extension == ".wav" || extension == ".ogg" || extension == ".flac";
}

bool isVideoFile(const fs::path &filePath)
{
    std::string extension = filePath.extension().string();
    return extension == ".mp4" || extension == ".avi" || extension == ".mkv" || extension == ".mov";
}

void listFiles(const fs::path &directory, std::vector<fs::path> &Folderlist)
{
    std::cout << "Audio/Video file in folder/subfolder: "<< std::endl;
    for (const auto &entry : fs::recursive_directory_iterator(directory))
    {
        if (fs::is_regular_file(entry.path()))
        {
            if (isAudioFile(entry.path()) || isVideoFile(entry.path()))
            {
                Folderlist.push_back(entry.path());
                std::cout << entry.path() << std::endl;
            }
        }
    }
}

int main()
{
    std::vector<fs::path> Folderlist; 
    
    fs::path directory_path = "/home/quan246/projects/src/mock_prj/testing/file_sample";
    listFiles(directory_path, Folderlist);
    return 0;
}
