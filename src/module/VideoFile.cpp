#include "VideoFile.hpp"

VideoFile::VideoFile()
{
}

VideoFile::~VideoFile()
{
}

VideoFile::VideoFile(fs::path path)
{
    // filePath
    filePath = path;

    // Is audio/video
    isAV = false;

    // Codec
    Codec = File::getCodec_init(path);

    // Size
    const char *filePathStr = filePath.c_str();
    Size = file_size(filePathStr);

    TagLib::FileRef f(filePathStr);
    if (!f.isNull() && f.tag())
    {
        TagLib::Tag *tag = f.tag();
        // Track_name
        Name = tag->title();
    }

    // Bitrate and duration
    if (!f.isNull() && f.audioProperties())
    {
        TagLib::AudioProperties *properties = f.audioProperties();
        Bitrate = properties->bitrate();
        Duration = properties->lengthInSeconds();
    }
}

std::streamsize VideoFile::file_size(const std::string &file_name)
{
    std::streamsize _size = 0;
    std::fstream file(file_name.c_str(), std::ios_base::in | std::ios_base::binary);
    if (file.is_open())
    {
        file.seekg(0, std::ios_base::end);
        _size = file.tellg();
        file.close();
        return _size;
    }
    else
        return 0;
}

// getter
TagLib::String VideoFile::getName()
{
    return Name;
}
std::string VideoFile::getCodec()
{
    return Codec;
}
std::streamsize VideoFile::getSize()
{
    return Size;
}
int VideoFile::getBitrate()
{
    return Bitrate;
}
int VideoFile::getDuration()
{
    return Duration;
}
