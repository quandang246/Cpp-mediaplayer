#ifndef FILE_HPP
#define FILE_HPP

#include <iostream>
#include <filesystem>
#include <iomanip>
#include <cstdio>
#include "tpropertymap.h"
#include "tstringlist.h"
#include "tvariant.h"
#include "fileref.h"
#include "tag.h"

namespace fs = std::filesystem;

class File
{
protected:
    fs::path filePath;
    TagLib::FileRef File_ref;
    bool isAV;

public:
    // Default Constructor and destructor
    File();
    virtual ~File();

    // Parameter constructor
    File(fs::path directory);

    static bool isAudioFile(const fs::path &filePath);
    static bool isVideoFile(const fs::path &filePath);

    // getter
    fs::path get_filePath();
    std::string getCodec_init(const fs::path &filePath);
    bool get_isAV();
    
    // Audio getter
    virtual TagLib::String getAlbum();
    virtual TagLib::String getArtist();
    virtual TagLib::String getGenre(); 
    virtual unsigned int getPublish_Year();
    virtual int getDuration();

    // Video getter
    // getter
    virtual TagLib::String getName();
    virtual std::string getCodec();
    virtual std::streamsize getSize();
    virtual int getBitrate();
    
    // update function
    virtual void update()=0;
};

#endif
