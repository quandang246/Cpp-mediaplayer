#include "AudioFile.hpp"

AudioFile::AudioFile()
{
}

AudioFile::~AudioFile()
{
}

AudioFile::AudioFile(fs::path path)
{
    // File path
    filePath = path;

    // Is audio/video
    isAV = true;

    const char *filePathStr = filePath.c_str();
    TagLib::FileRef f(filePathStr);
    if (!f.isNull() && f.tag())
    {
        TagLib::Tag *tag = f.tag();
        // Track_name
        Track_name = tag->title();
        // Artist
        Artist = tag->artist();
        // Album
        Album = tag->album();
        // Publish_Year
        Publish_Year = tag->year();
        // Genre
        Genre = tag->genre();
    }

    if (!f.isNull() && f.audioProperties())
    {
        TagLib::AudioProperties *properties = f.audioProperties();
        // Duration
        Duration = properties->lengthInSeconds();
    }
}

TagLib::String AudioFile::getName()
{
    return Track_name;
}
TagLib::String AudioFile::getAlbum()
{
    return Album;
}
TagLib::String AudioFile::getArtist()
{
    return Artist;
}
TagLib::String AudioFile::getGenre()
{
    return Genre;
}
unsigned int AudioFile::getPublish_Year()
{
    return Publish_Year;
}
int AudioFile::getDuration()
{
    return Duration;
}
