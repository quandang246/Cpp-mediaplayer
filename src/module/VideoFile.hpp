#ifndef VIDEOFILE_HPP
#define VIDEOFILE_HPP

#include "File.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>

class VideoFile : public File
{
private:
    TagLib::String Name;
    std::string Codec;
    std::streamsize Size;
    int Bitrate;
    int Duration;

public:
    // Default constructor and destructor
    VideoFile();
    ~VideoFile();

    // Parameter constructor
    VideoFile(fs::path path);

    //Size 
    std::streamsize file_size(const std::string &file_name);
    
    // getter
    TagLib::String getName();
    std::string getCodec();
    std::streamsize getSize();
    int getBitrate();
    int getDuration();

    // Update function
    void update();
};

#endif
