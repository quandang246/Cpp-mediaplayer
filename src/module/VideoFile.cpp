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
    isAV = true;

    // Codec
    Codec = File::getCodec_init(path);

    // Size
    const char *filePathStr = filePath.c_str();
    Size = file_size(filePathStr);

    // Name
    if (!File_ref.isNull() && File_ref.tag())
    {
        TagLib::Tag *tag = File_ref.tag();
        Name = tag->title();
    }

    // Bitrate and duration
    if (!File_ref.isNull() && File_ref.audioProperties())
    {
        TagLib::AudioProperties *properties = File_ref.audioProperties();
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
