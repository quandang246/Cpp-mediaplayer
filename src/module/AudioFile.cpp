#include "AudioFile.hpp"

AudioFile::AudioFile()
{
}

AudioFile::~AudioFile()
{
}

AudioFile::AudioFile(fs::path path, int m) {
    filePath = path;
    metadata = m;
    isAV = false;
}

