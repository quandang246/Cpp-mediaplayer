#ifndef AUDIOFILE_HPP
#define AUDIOFILE_HPP

#include "File.hpp"

class AudioFile : public File
{
private:
    int metadata;
public:
    // Default constructor and destructor
    AudioFile();
    ~AudioFile();

    // Parameter constructor
    AudioFile(fs::path path, int m);

    // play function
    void play ();

    // pause function
    void pause ();

    // displayTimeDuration function
    void displayTimeDuration();
};

#endif

