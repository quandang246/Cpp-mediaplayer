#ifndef VIDEOFILE_HPP
#define VIDEOFILE_HPP

#include "File.hpp"

class VideoFile : public File
{
private:
    int metadata;
public:
    // Default constructor and destructor
    VideoFile();
    ~VideoFile();

    // Parameter constructor
    VideoFile(fs::path path, int m);

    // play function
    void play ();

    // pause function
    void pause ();

    // displayTimeDuration function
    void displayTimeDuration();
};

#endif
