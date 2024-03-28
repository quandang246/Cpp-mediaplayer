#include "VideoFile.hpp"

VideoFile::VideoFile()
{
}

VideoFile::~VideoFile()
{
}

VideoFile::VideoFile(fs::path path, int m) {
    filePath = path;
    metadata = m;
    isAV = true;
}

