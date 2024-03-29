#include "src/controller/MediaManagement.hpp"
#include "mediaConfig.h"

int main(int argc, char* argv[])
{
    std::cout << "Welcome to QuanDang's Mediaplayer program!" << std::endl;
    std::cout << argv[0] << "Version " << MEDIA_VERSION_MAJOR << "." << MEDIA_VERSION_MINOR << std::endl; 
    
    std::filesystem::path cwd = std::filesystem::current_path();
    MediaManagement A(cwd);
    
    A.run();

    return 0;
}
