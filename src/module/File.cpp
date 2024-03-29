#include "File.hpp"

File::File()
{
}

File::~File()
{
}

File::File(fs::path path)
{
    filePath = path;
    const char *filePathStr = filePath.c_str();
    TagLib::FileRef File_ref(filePathStr);

    if (isAudioFile(filePath))
    {
        isAV = true;
    }
    else if (isVideoFile(filePath))
    {
        isAV = false;
    }
}

bool File::isAudioFile(const fs::path &filePath)
{
    std::string extension = filePath.extension().string();
    return extension == ".mp3" || extension == ".wav" || extension == ".ogg" || extension == ".flac";
}

bool File::isVideoFile(const fs::path &filePath)
{
    std::string extension = filePath.extension().string();
    return extension == ".mp4" || extension == ".avi" || extension == ".mkv" || extension == ".mov";
}

fs::path File::get_filePath()
{
    return filePath;
}

std::string File::getCodec_init(const fs::path &filePath)
{
    static const std::unordered_map<std::string, std::string> audioCodecs = {
        {".mp3", "MPEG Audio Layer III"},
        {".wav", "Waveform Audio File Format"},
        {".ogg", "Ogg Vorbis"},
        {".flac", "Free Lossless Audio Codec"}};

    static const std::unordered_map<std::string, std::string> videoCodecs = {
        {".mp4", "MPEG-4 Part 14"},
        {".avi", "Audio Video Interleave"},
        {".mkv", "Matroska"},
        {".mov", "QuickTime File Format"}};

    std::string extension = filePath.extension().string();

    if (audioCodecs.find(extension) != audioCodecs.end())
    {
        return audioCodecs.at(extension);
    }
    else if (videoCodecs.find(extension) != videoCodecs.end())
    {
        return videoCodecs.at(extension);
    }
    else
    {
        return "Unknown Codec";
    }
}

bool File::get_isAV()
{
    return isAV;
}


// Audio getter
TagLib::String File::getAlbum()
{
    return TagLib::String();
}
TagLib::String File::getArtist()
{
    return TagLib::String();
}
TagLib::String File::getGenre()
{
    return TagLib::String();
}
unsigned int File::getPublish_Year()
{
    return int();
}
int File::getDuration()
{
    return int();
}

// Video getter
// getter
TagLib::String File::getName()
{
    return TagLib::String();
}
std::string File::getCodec()
{
    return std::string();
}
std::streamsize File::getSize()
{
    return std::streamsize();
}
int File::getBitrate()
{
    return int();
}
