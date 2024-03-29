#ifndef AUDIOFILE_HPP
#define AUDIOFILE_HPP

#include "File.hpp"

class AudioFile : public File
{
private:
    TagLib::String Track_name, Album, Artist, Genre; 
    unsigned int Publish_Year;
    int Duration;
public:
    // Default constructor and destructor
    AudioFile();
    ~AudioFile();

    // Parameter constructor
    AudioFile(fs::path path);

    //getter
    TagLib::String getName();
    TagLib::String getAlbum();
    TagLib::String getArtist();
    TagLib::String getGenre(); 
    unsigned int getPublish_Year();
    int getDuration();
};

#endif

