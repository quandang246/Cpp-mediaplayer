#include <iostream>
#include <string>
#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

class File {
public:
    static std::string getCodec(const fs::path &filePath) {
        static const std::unordered_map<std::string, std::string> audioCodecs = {
            { ".mp3", "MPEG Audio Layer III" },
            { ".wav", "Waveform Audio File Format" },
            { ".ogg", "Ogg Vorbis" },
            { ".flac", "Free Lossless Audio Codec" }
        };

        static const std::unordered_map<std::string, std::string> videoCodecs = {
            { ".mp4", "MPEG-4 Part 14" },
            { ".avi", "Audio Video Interleave" },
            { ".mkv", "Matroska" },
            { ".mov", "QuickTime File Format" }
        };

        std::string extension = filePath.extension().string();

        if (audioCodecs.find(extension) != audioCodecs.end()) {
            return audioCodecs.at(extension);
        } else if (videoCodecs.find(extension) != videoCodecs.end()) {
            return videoCodecs.at(extension);
        } else {
            return "Unknown Codec";
        }
    }
};

int main() {
    fs::path audioFilePath = "/home/quan246/projects/src/mock_prj/file_sample/10 second intro music.mp3";
    fs::path videoFilePath = "/home/quan246/projects/src/mock_prj/file_sample/10 second intro music.mp4";

    std::cout << "Audio Codec: " << File::getCodec(audioFilePath) << std::endl;
    std::cout << "Video Codec: " << File::getCodec(videoFilePath) << std::endl;

    return 0;
}
